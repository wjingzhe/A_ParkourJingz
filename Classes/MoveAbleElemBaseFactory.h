#pragma once
#include "cocos2d.h"
#include "MoveAbleElem.h"

class MoveAbleElemBaseFactory :public cocos2d::Ref
{
	friend class MoveAbleElemManager;

protected:
#ifdef STD_VECTOR_ELEM
	std::vector<MoveAbleElem *> _vUsedElem;
	std::vector<MoveAbleElem *> _vReadyElem;
	std::vector<MoveAbleElem *> _pPreGenElem;
#else
	cocos2d::Vector<MoveAbleElem *> _vUsedElem;
	cocos2d::Vector<MoveAbleElem *> _vReadyElem;
	cocos2d::Vector<MoveAbleElem *> _pPreGenElem;

#endif

protected:
	MoveAbleElemBaseFactory() { ; }
public:

	virtual ~MoveAbleElemBaseFactory()
	{
		

#ifdef STD_VECTOR_ELEM
		for (auto it = _pPreGenElem.begin(); it != _pPreGenElem.end(); ++it)
		{
			delete(*it);
		}
		for (auto it = _vReadyElem.begin(); it != _vReadyElem.end(); ++it)
		{
			delete(*it);
		}
		for (auto it = _vUsedElem.begin(); it != _vUsedElem.end(); ++it)
		{
			delete(*it);
		}
#else
		_pPreGenElem.clear();
		_vUsedElem.clear();
		_vReadyElem.clear();
#endif
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

	virtual void forceToPreCreate()
	{
	}

	virtual void recycleElem(MoveAbleElem * pElem)
	{
	}

	int getReadyElemSize()
	{
		return _vReadyElem.size();
	}

private:
	
};
