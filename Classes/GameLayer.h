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

	void update(float delta) override;

	CREATE_FUNC(GameLayer);

	CC_DISALLOW_COPY_AND_ASSIGN(GameLayer);

	Player * getPlayer(void);

	void setPlayer(Player * pPlayer);

private:
	Player * _pPlayer;
	
};
