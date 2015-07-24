#pragma once
#include "cocos2d.h"
#include "MoveAbleElemBaseFactory.h"
#define INCREASEMENT 20

#define ADD_MOVEABLE_ELEM(SIZE) \
		for (size_t i = 0; i < SIZE; ++i)\
		{\
			_vUsedElem.pushBack(MoveAbleElem::create()); \
		}

template<class MoveAbleElem>
class MoveAbleElemFactory :public MoveAbleElemBaseFactory
{
	typedef MoveAbleElem* MoveAbleElemPtr;
protected:
	MoveAbleElemFactory() { ; }
public:
	
	virtual ~MoveAbleElemFactory()
	{

	}

	bool init() override
	{
		ADD_MOVEABLE_ELEM(INCREASEMENT);
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
		if (_vUsedElem.size() <= 0)
		{
			ADD_MOVEABLE_ELEM(INCREASEMENT);
		}

		//todo 
		MoveAbleElemPtr pElem = dynamic_cast<MoveAbleElemPtr >(_vUsedElem.back());//不用auto 是为了确认返回非const MoveAbleElem *
		_vReadyElem.pushBack(pElem);
		pElem->setUsed();
		_vUsedElem.popBack();
		return pElem;
	}

	virtual void recycleElem(MoveAbleElemPtr pElem)
	{
		_vUsedElem.pushBack(pElem);
		_vReadyElem.eraseObject(pElem);
		pElem->recycleSelf();
	}

protected:

private:

};
