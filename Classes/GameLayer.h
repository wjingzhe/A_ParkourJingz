#pragma once
#include "cocos2d.h"
#include "ProcedureGenController.h"

class GameMainController;
class Player;

class GameLayer:public cocos2d::Layer
{
	GameLayer();
public:
	
	~GameLayer();

	bool init(void);

	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);
	void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event);

	virtual void onEnter() override;
	virtual void onExit() override;

	void update(float delta) override;

	CREATE_FUNC(GameLayer);

	CC_DISALLOW_COPY_AND_ASSIGN(GameLayer);

private:
	cocos2d::EventListenerTouchOneByOne * _pTouchListenerOneByOne;
	Player * _pPlayer;
	
	ProcedureGenController _pPgController;

	GameMainController * _pGameMainController;
};
