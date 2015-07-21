/*

负责实现角色和摄像机的动作，比如移动管理、特效、受击等操作。

*/

#pragma once

#include "cocos2d.h"

class Player;
class MapSceneController;
class PlayerController;

class GameMainController:public cocos2d::Ref
{
	GameMainController();
public:
	
	~GameMainController();

	bool init(Player * pPlayer, cocos2d::Layer * pGameLayer);

	static GameMainController* create(Player * pPlayer, cocos2d::Layer * pGameLayer)
	{
		GameMainController *pRet = new(std::nothrow) GameMainController();
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

	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);
	void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event);

	void onAfterDraw(cocos2d::EventCustom * pEvent);

	enum MOVE_MODE
	{
		SCENE = 0,
		PLAYER = 1,
		BOTH_SCENE_AND_PLAYER,
		NONE
	};

	void setMoveMode(MOVE_MODE mode);

private:
	MapSceneController * _pMapSceneController;
	PlayerController * _pPlayerController;
	cocos2d::Layer * _pGameLayer;
	cocos2d::EventListenerCustom * _pEventListenerAfterDraw;
	MOVE_MODE _eMode;
};
