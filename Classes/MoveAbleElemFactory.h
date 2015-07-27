#pragma once
#include "cocos2d.h"
#include "MoveAbleElemBaseFactory.h"
#include <thread>
#include <future>
#include <atomic>
#include <exception>
#include <iostream>

static std::atomic_flag s_lock = ATOMIC_FLAG_INIT;

#define INCREASEMENT 5
#define PRE_CREATE_INCREASEMENT 15
#define PRE_CREATE_BASE 30

#define ADD_MOVEABLE_ELEM(CONTAINER,SIZE) \
		for (size_t i = 0; i < SIZE; ++i)\
		{\
			CONTAINER.push_back(MoveAbleElem::create()); \
		}

template<class MoveAbleElem>
class MoveAbleElemFactory :public MoveAbleElemBaseFactory
{
	typedef MoveAbleElem* MoveAbleElemPtr;
protected:
	MoveAbleElemFactory()
	{
		_pPreGenElem.clear();

		auto & _lock = s_lock;
		auto & _pPreGenElem = this->_vReadyElem;
		//新起线程去完成加载，用锁来控制唯一性
		_theadPreload = std::async(
			[&_lock, &_pPreGenElem]()->void
		{
			while (_lock.test_and_set(std::memory_order_acquire))
			{
				//尝试取锁
			}
			ADD_MOVEABLE_ELEM(_pPreGenElem, PRE_CREATE_BASE);
			_lock.clear();
			//解锁
		}
		);
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

	virtual MoveAbleElemPtr getMoveAbleElem()
	{
		try
		{
			_theadPreload.get();
		}
		catch (const std::exception &e)
		{
			std::cout << "Exception: " << e.what() << std::endl;
		}
		

		if (!_pPreGenElem.empty())
		{
			while (s_lock.test_and_set(std::memory_order_acquire))
			{
				//尝试取锁
			}
			for each (auto pMoveAbleElem in _pPreGenElem)
			{
				_vReadyElem.push_back(pMoveAbleElem);
			}
			_pPreGenElem.clear();
			s_lock.clear();
		}

		if (_vReadyElem.size() <= 0)
		{
			ADD_MOVEABLE_ELEM(_vReadyElem, INCREASEMENT);
		}

		//todo 
		MoveAbleElemPtr pElem = dynamic_cast<MoveAbleElemPtr >(_vReadyElem.back());//不用auto 是为了确认返回非const MoveAbleElem *
		_vUsedElem.push_back(pElem);
		pElem->setUsed();
		_vReadyElem.pop_back();

		if (_vReadyElem.size()<=1)
		{
			auto & _lock = s_lock;
			auto & _pPreGenElem = this->_pPreGenElem;
			//新起线程去完成加载，用锁来控制唯一性
			_theadPreload = std::async(
				[&_lock, &_pPreGenElem]()->void
				{
					while (_lock.test_and_set(std::memory_order_acquire))
					{
						//尝试取锁
					}
					ADD_MOVEABLE_ELEM(_pPreGenElem, PRE_CREATE_INCREASEMENT);
					_lock.clear();
					//解锁
				}
			);
		}

		return pElem;
	}

	virtual void recycleElem(MoveAbleElemPtr pElem)
	{
		_vReadyElem.push_back(pElem);
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

private:
	std::future<void> _theadPreload;
};

