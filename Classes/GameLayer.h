#pragma once
#include "cocos2d.h"

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

	void stopGame(void);

private:
	cocos2d::EventListenerTouchOneByOne * _pTouchListenerOneByOne;
	Player * _pPlayer;
	GameMainController * _pGameMainController;
};
