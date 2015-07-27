#include "ElemsPreloadManager.h"

#include "Coin.h"
#include "Obstacle.h"
//#include "Player.h"

#include "MoveAbleElemManager.h"
#include "MoveAbleElemFactory.h"

bool ElemsPreloadManager::s_bRegisterd = false;

ElemsPreloadManager::ElemsPreloadManager()
{
}

ElemsPreloadManager::~ElemsPreloadManager()
{
}


void ElemsPreloadManager::registerMoveAbleElemTypes(void)
{
	//MoveAbleElemManager::getInstance()->registerElemAndFactory(4, MoveAbleElemFactory<Player>::create);

	MoveAbleElemManager::getInstance()->registerElemAndFactory(1, MoveAbleElemFactory<Obstacle>::create);
	MoveAbleElemManager::getInstance()->registerElemAndFactory(2, MoveAbleElemFactory<Coin>::create);
	s_bRegisterd = true;
}

void ElemsPreloadManager::preCreateMoveAbleElems(void)
{
	if (!s_bRegisterd)
	{
		ElemsPreloadManager::registerMoveAbleElemTypes();
	}
	MoveAbleElemManager::getInstance()->GenerateOneElem(1);
	MoveAbleElemManager::getInstance()->GenerateOneElem(2);
}