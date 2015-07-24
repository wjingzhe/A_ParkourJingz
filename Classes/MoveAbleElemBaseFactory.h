#pragma once
#include "cocos2d.h"
#include "MoveAbleElem.h"

class MoveAbleElemBaseFactory :public cocos2d::Ref
{
protected:
	MoveAbleElemBaseFactory() { ; }
public:

	virtual ~MoveAbleElemBaseFactory()
	{

	}

	virtual bool init()
	{
		return true;
	}

	static MoveAbleElemBaseFactory * create()
	{
		return nullptr;
	}

	virtual MoveAbleElem * getMoveAbleElem()
	{
		return nullptr;
	}

	virtual void recycleElem(MoveAbleElem * pElem)
	{
	}

protected:
	cocos2d::Vector<MoveAbleElem *> _vUsedElem;
	cocos2d::Vector<MoveAbleElem *> _vReadyElem;

private:

};
