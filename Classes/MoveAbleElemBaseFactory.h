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
		_pPreGenElem.clear();

		for (auto it = _vReadyElem.begin(); it != _vReadyElem.end(); ++it)
		{
			delete(*it);
		}
		for (auto it = _vUsedElem.begin(); it != _vUsedElem.end(); ++it)
		{
			delete(*it);
		}
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

	virtual void preLoadElem()
	{

	}

protected:
	std::vector<MoveAbleElem *> _vUsedElem;
	std::vector<MoveAbleElem *> _vReadyElem;
	std::vector<MoveAbleElem *> _pPreGenElem;

private:
	
};
