#pragma once
#include "cocos2d.h"

class Player;

class MapSceneController:public cocos2d::Ref
{
	MapSceneController();
public:
	
	~MapSceneController();

	bool init(Player * pPlayer, cocos2d::Layer * pGameLayer);

	static MapSceneController* create(Player * pPlayer, cocos2d::Layer * pGameLayer)
	{
		MapSceneController *pRet = new(std::nothrow) MapSceneController();
		if (pRet && pRet->init(pPlayer, pGameLayer))
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

	void preGenerate(void);

	void afferUpdateCallback(cocos2d::EventCustom * pEventCustom);

	void linkRoads(void);

	void update(float delta);

	//渲染之后移动场景
	void moveScene(const cocos2d::Vec3 &pos);

private:
	Player * _pPlayer;
	cocos2d::Layer * _pGameLayer;
	 
	cocos2d::Vector<cocos2d::Sprite3D *> _vpRoadSprites;

	cocos2d::EventListenerCustom * _pEventListenerAfterUpdate;
	float _fStepLength;
	float _fElapsed;
	float _fPerTime;
};

