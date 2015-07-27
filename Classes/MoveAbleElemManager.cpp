#include "MoveAbleElemManager.h"
#include "cocos2d.h"
#include "MoveAbleElem.h"
#include "Obstacle.h"
#include "Coin.h"
#include "Player.h"


using namespace std;
USING_NS_CC;


MoveAbleElemManager * MoveAbleElemManager::s_pMoveAbleElemManager = nullptr;

MoveAbleElemManager::MoveAbleElemManager() :_mElemFactories({})
{
}

MoveAbleElemManager::~MoveAbleElemManager()
{
}

MoveAbleElemManager * MoveAbleElemManager::getInstance(void)
{
	if (s_pMoveAbleElemManager == nullptr)
	{
		s_pMoveAbleElemManager = new MoveAbleElemManager();
		s_pMoveAbleElemManager->init();
	}
	return s_pMoveAbleElemManager;
}

void MoveAbleElemManager::destroyInstance(void)
{
	if (s_pMoveAbleElemManager != nullptr)
	{
		s_pMoveAbleElemManager->release();
		s_pMoveAbleElemManager = nullptr;
	}
	
}

void MoveAbleElemManager::init(void)
{
	//todo here should try load something
}

void MoveAbleElemManager::recycleElem(MoveAbleElem * pMoveAbleElem)
{
	CCASSERT(_mElemFactories.at(pMoveAbleElem->getElemType()), "MoveAbleElemFactory don't include this types");
	_mElemFactories.at(pMoveAbleElem->getElemType())->recycleElem(pMoveAbleElem);
}

MoveAbleElem * MoveAbleElemManager::GenerateOneElem(unsigned short iTypeId) throw (std::out_of_range)
{
	try
	{

		if (_mElemFactories.at(iTypeId) == nullptr)
		{
			try
			{
				auto pFactory = _mFactoryCreatFunc.at(iTypeId)();

				_mElemFactories.insert(iTypeId, pFactory);
				return pFactory->getMoveAbleElem();
			}
			catch (std::out_of_range e)
			{
				CCLOG("MoveAbleElem Type:%ud 's factory creatFunc is null", iTypeId);
				throw e;
			}

		}

		return _mElemFactories.at(iTypeId)->getMoveAbleElem();
	}
	catch (std::out_of_range e)
	{
		try
		{
			auto pFactory = _mFactoryCreatFunc.at(iTypeId)();
			_mElemFactories.insert(iTypeId, pFactory);
			return pFactory->getMoveAbleElem();
		}
		catch (std::out_of_range e)
		{
			CCLOG("You should call registerSelf(void) in you new MoveAbleElem's init function", iTypeId);
			throw e;
		}
	}

}

void MoveAbleElemManager::registerElemAndFactory(unsigned short iTypeId, FactoryCreateFunc createFunc)
{
	_mFactoryCreatFunc.insert(make_pair(iTypeId, createFunc));
}