/***************************************************
实现的生产者和消费者模型。
生产者线程一直在后台执行。当有作业需求时则执行，没有作业需求时直接放弃当前cpu时间片
在消费者数量低于ELEM_MIN_REMAIN是激活生产者流水线作业，生产PRE_CREATE_BASE；
生产过程中，主线程如果有消费需求则自己生产（如果触发，说明后台的生产者线程拥挤或被注销了）。
因为确认AutoReleasePool是不支持多线程清理，所以使用了手动release，同时将elem的create函数改名为createWithAutoRealse

整个游戏逻辑的主要性能瓶颈在于：
1、短时间生成大量的elem并初始化精灵，虽然我已经把elem的生成拆成多线程了，但是Sprite3D的初始化中使用了AutoRelease相关的
机制导致无法在非主线程中生成。目前为使用前初始化，这点是性能瓶颈之一
2、碰撞检测逻辑没有进行AOI处理
3、大量的使用了虚函数，这个将是一个性能问题，之后考虑将无关的虚函数抽至父类为非虚函数









***************************************************/
#pragma once
#include "cocos2d.h"
#include "MoveAbleElemBaseFactory.h"
#include <thread>
#include <future>
#include <atomic>
#include <exception>
#include <mutex>

#include "MoveAbleElem.h"

#define INCREASEMENT 40
#define PRE_CREATE_INCREASEMENT_TIMES 1
#define PRE_CREATE_BASE 30
#define ELEM_MIN_REMAIN 15
#define ELEM_MAX_REMAIN 80
//应该根据配置去读取实际可能最多数量
#define ELEM_MAX_NEED 100

#ifdef STD_VECTOR_ELEM
#define pushBack push_back
#define popBack pop_back
#define RELSASE_TARTGET(TAR) 
#else
#define RELSASE_TARTGET(TAR) TAR->release()
#endif

//todo bug STD_VECTOR_ELEM
#define ADD_MOVEABLE_ELEM(CONTAINER,SIZE) \
		for (size_t i = 0; i < SIZE; ++i)\
		{\
			auto p = T::createWithAutoRealse();\
			CONTAINER.pushBack(p); \
			RELSASE_TARTGET(p);	\
		}\

		

template<class T>
class MoveAbleElemFactory :public MoveAbleElemBaseFactory
{
	typedef T* T_Ptr;
protected:
	MoveAbleElemFactory() :_bPreCreateFinshed(false), _bThreedNeedToExit(false), _iCount(0)
	{
		auto & _locked = _mutexLock;
		auto & _pPreGenElem = this->_pPreGenElem;
		auto & _bPreCreateFinshed = this->_bPreCreateFinshed;
		auto & _bThreedNeedToExit = this->_bThreedNeedToExit;
		auto & curStep = this->_iCount;
		auto totalStep = PRE_CREATE_INCREASEMENT_TIMES; //todo
		//新起线程去完成加载，用锁来控制唯一性
		_theadPreload = std::thread(
			[&_locked, &_pPreGenElem, &_bPreCreateFinshed, &_bThreedNeedToExit, &curStep,&totalStep]()->void
		{
			while (true)
			{
				if (_bPreCreateFinshed)
				{
					std::this_thread::yield();
				}
				else
				{
					while (!_locked.try_lock())
					{
						//尝试取锁
						std::this_thread::sleep_for(std::chrono::milliseconds(200));
					}
					ADD_MOVEABLE_ELEM(_pPreGenElem, INCREASEMENT);//切换线程的时间和创建INCREASEMENT对象的计算量最好得相近
					++curStep;
					if (curStep >= totalStep)
					{
						_bPreCreateFinshed = true;
						curStep = 0;
					}
					//解锁
					_locked.unlock();
					std::this_thread::yield();
					
				}

				if (_bThreedNeedToExit)
				{
					return;
				}
				
			}
			
		}
		);
		_theadPreload.detach();
	}
public:
	
	virtual ~MoveAbleElemFactory()
	{
		while (!_mutexLock.try_lock())
		{

		}
		_bThreedNeedToExit.store(true);
		_mutexLock.unlock();
		if (_theadPreload.joinable())
		{
			_theadPreload.join();
		}
	}

	bool init() override
	{
		return true;
	}

	static MoveAbleElemBaseFactory * create()
	{
		MoveAbleElemFactory *pRet = new(std::nothrow) MoveAbleElemFactory();
		if (pRet && pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
	}

	T_Ptr getMoveAbleElem()
	{
		if (_vReadyElem.size() <= ELEM_MIN_REMAIN && _bPreCreateFinshed)
		{
			_mutexLock.lock();
			if (_vReadyElem.size() <= ELEM_MAX_REMAIN)
			{
				_bPreCreateFinshed = false;
			}
			for (auto it = _pPreGenElem.begin(); it != _pPreGenElem.end(); ++it)
			{
				_vReadyElem.pushBack(*it);
			}
			_pPreGenElem.clear();
			_iCount = 0;
			_mutexLock.unlock();
		}

		if (_vReadyElem.empty())
		{		
			ADD_MOVEABLE_ELEM(_vReadyElem, 1);
		}
		//已够用，销毁工厂线程
		else if (_vReadyElem.size() >= ELEM_MAX_NEED)
		{
			int i = 0;
			while (!_mutexLock.try_lock() && i < 5)
			{
				++i;
				//尝试取锁
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
			}
			if (i < 5)
			{
				_bThreedNeedToExit.store(true);
				_mutexLock.unlock();
			}
		}
		

		//todo 
		T_Ptr pElem = dynamic_cast<T_Ptr >(_vReadyElem.back());//不用auto 是为了确认返回非const T *
		_vUsedElem.pushBack(pElem);
		pElem->setUsed();
		_vReadyElem.popBack();

		return pElem;
	}

	void forceToPreCreate()
	{
		_mutexLock.lock();
		for (auto it = _pPreGenElem.begin(); it != _pPreGenElem.end(); ++it)
		{
			_vReadyElem.pushBack(*it);
		}
		_pPreGenElem.clear();
		_bPreCreateFinshed = false;
		_iCount = 0;
		_mutexLock.unlock();
	}

	void recycleElem(MoveAbleElem * pElem)
	{
		_vReadyElem.pushBack(pElem);
		for (auto it = _vUsedElem.begin(); it != _vUsedElem.end(); ++it)
		{
			if (*it == pElem)
			{
				_vUsedElem.erase(it);
				break;
			}
		}
		pElem->recycleSelf();
	}

	
protected:
	std::thread _theadPreload;
	std::atomic<bool> _bPreCreateFinshed;
	std::atomic<bool> _bThreedNeedToExit;
	std::atomic<int> _iCount;
	std::mutex _mutexLock;
private:
};

#ifdef STD_VECTOR_ELEM
#undef pushBack
#undef popBack pop_back
#endif

#undef RELSASE_TARTGET(TAR)