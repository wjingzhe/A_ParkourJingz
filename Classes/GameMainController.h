/*

负责实现角色和摄像机的动作，比如移动管理、特效、受击等操作。

*/

#pragma once

#include "cocos2d.h"

class Player;
class MapSceneController;
class PlayerController;
class NpcController;

class GameMainController:public cocos2d::Ref
{
	GameMainController();
public:
	
	~GameMainController();

	bool init(Player * pPlayer, cocos2d::Layer * pGameLayer, cocos2d::Layer * pMainMenuLayer);

	static GameMainController* create(Player * pPlayer, cocos2d::Layer * pGameLayer, cocos2d::Layer * pMainMenuLayer)
	{
		GameMainController *pRet = new(std::nothrow) GameMainController();
		if (pRet && pRet->init(pPlayer, pGameLayer,pMainMenuLayer))
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

	void onStop(cocos2d::EventCustom * pEvent);
	void onStart(cocos2d::EventCustom * pEvent);
	void onRestart(cocos2d::EventCustom * pEvent);
	void onShowRestart(cocos2d::EventCustom * pEvent);

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
	NpcController * _pNpcController;


	cocos2d::Layer * _pGameLayer;
	cocos2d::Layer * _pMainMenuLayer;

	cocos2d::EventListenerCustom * _pEventListenerStopGame;
	cocos2d::EventListenerCustom * _pEventListenerStartGame;
	cocos2d::EventListenerCustom * _pEventListenerRestartGame;
	cocos2d::EventListenerCustom * _pEventListenerShowRestartButton;

	MOVE_MODE _eMode;
};
