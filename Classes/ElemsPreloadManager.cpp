#include "ElemsPreloadManager.h"

#include "Coin.h"
#include "Obstacle.h"
//#include "Player.h"

#include "MoveAbleElemManager.h"
#include "MoveAbleElemFactory.h"

#include "MoveAbleElemTypeDefines.h"

bool ElemsPreloadManager::s_bRegisterd = false;

ElemsPreloadManager::ElemsPreloadManager()
{
}

ElemsPreloadManager::~ElemsPreloadManager()
{
}


void ElemsPreloadManager::registerMoveAbleElemTypes(void)
{
	//MoveAbleElemManager::getInstance()->registerElemAndFactory(PLAYER_TYPE_ID, MoveAbleElemFactory<Player>::create);

	MoveAbleElemManager::getInstance()->registerElemAndFactory(OBSTACLE__ID, MoveAbleElemFactory<Obstacle>::create);
	MoveAbleElemManager::getInstance()->registerElemAndFactory(COIN_TYPE_ID, MoveAbleElemFactory<Coin>::create);
	s_bRegisterd = true;
}

void ElemsPreloadManager::forceCreateMoveAbleElems(void)
{
	if (!s_bRegisterd)
	{
		ElemsPreloadManager::registerMoveAbleElemTypes();
	}
	MoveAbleElemManager::getInstance()->GenerateOneElem(OBSTACLE__ID)->recycleSelf();
	MoveAbleElemManager::getInstance()->GenerateOneElem(COIN_TYPE_ID)->recycleSelf();
}