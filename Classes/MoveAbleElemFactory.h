#pragma once
#include "cocos2d.h"
#include "MoveAbleElemBaseFactory.h"
#include <thread>
#include <future>
#include <atomic>
#include <exception>
#include <iostream>
#include "MoveAbleElem.h"

static std::atomic_flag s_lock = ATOMIC_FLAG_INIT;

#define INCREASEMENT 5
#define PRE_CREATE_INCREASEMENT 15
#define PRE_CREATE_BASE 30
#define ELEM_MIN_REMAIN 5

#ifdef STD_VECTOR_ELEM
#define pushBack push_back
#define popBack pop_back
#endif


#define ADD_MOVEABLE_ELEM(CONTAINER,SIZE) \
		for (size_t i = 0; i < SIZE; ++i)\
		{\
			auto p = T::createWithAutoRealse();\
			CONTAINER.pushBack(p); \
			p->release();	\
		}\
		

template<class T>
class MoveAbleElemFactory :public MoveAbleElemBaseFactory
{
	typedef T* T_Ptr;
protected:
	MoveAbleElemFactory()
	{
		ADD_MOVEABLE_ELEM(_vReadyElem, PRE_CREATE_BASE);
	}
public:
	
	virtual ~MoveAbleElemFactory()
	{
	}

	bool init() override
	{
		//ADD_MOVEABLE_ELEM(INCREASEMENT);
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

	virtual T_Ptr getMoveAbleElem()
	{
		if (_vReadyElem.size() <= 0)
		{
			ADD_MOVEABLE_ELEM(_vReadyElem, INCREASEMENT);
		}

		//todo 
		T_Ptr pElem = dynamic_cast<T_Ptr >(_vReadyElem.back());//不用auto 是为了确认返回非const T *
		_vUsedElem.pushBack(pElem);
		pElem->setUsed();
		_vReadyElem.popBack();

		if (_vReadyElem.size() <= ELEM_MIN_REMAIN)
		{
			auto & _lock = s_lock;
			auto & _pPreGenElem = this->_pPreGenElem;
			//新起线程去完成加载，用锁来控制唯一性
			if (_theadPreload.joinable())
			{
				_theadPreload.join();
			}
			_theadPreload = std::thread(
				[&_lock, &_pPreGenElem]()->int
				{
					while (_lock.test_and_set(std::memory_order_acquire))
					{
						//尝试取锁
					}
					ADD_MOVEABLE_ELEM(_pPreGenElem, PRE_CREATE_INCREASEMENT);
					_lock.clear();
					//解锁
					return 0;
				}
			);
			_theadPreload.detach();
		}

		return pElem;
	}

	virtual void recycleElem(MoveAbleElem * pElem)
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
private:
};

#ifdef STD_VECTOR_ELEM
#undef pushBack
#undef popBack pop_back
#endif
