#pragma once

#include "cocos2d.h"
#include <map>
#include <functional>
#include <exception>
#include "MoveAbleElemBaseFactory.h"

class MoveAbleElem;


class MoveAbleElemManager:public cocos2d::Ref
{
	typedef std::function<MoveAbleElemBaseFactory*(void)> FactoryCreateFunc;

	MoveAbleElemManager();
public:
	
	~MoveAbleElemManager();

	static MoveAbleElemManager * getInstance(void);

	static void destroyInstance(void);

	void init(void);

	void recycleElem(MoveAbleElem * pMoveAbleElem);

	//jingz 
	// !!!! take care,if caused a out_of_range exception
	MoveAbleElem * GenerateOneElem(unsigned int iTypeId) throw (std::out_of_range);

	void registerElemAndFactory(unsigned int iTypeId, FactoryCreateFunc createFunc);

	MoveAbleElemBaseFactory* getElemFactory(unsigned int iTypeId);

private:
	static MoveAbleElemManager * s_pMoveAbleElemManager;
	
	cocos2d::Map<unsigned int, MoveAbleElemBaseFactory * > _mElemFactories;
	std::map<unsigned int, FactoryCreateFunc> _mFactoryCreatFunc;
};
