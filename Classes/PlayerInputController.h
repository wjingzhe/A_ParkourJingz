#pragma once
#include "cocos2d.h"

//todo 没必要依赖于某个Player，可以使多个，这样子才能允许多人同屏的可能性，每次调用传入Player对象即可
class Player;

class PlayerInputController:public cocos2d::Ref
{
	PlayerInputController(Player * pPlayer);
public:
	~PlayerInputController();

	bool init() {return true;}

	void reveiveTouchBegin(cocos2d::Vec2 pos, cocos2d::Node * pRenderNode);

	void reveiveTouchEnd(cocos2d::Vec2 pos, cocos2d::Node * pRenderNode);

	static PlayerInputController * create(Player * pPlayer);
private:
	CC_DISALLOW_COPY_AND_ASSIGN(PlayerInputController);

private:
	Player * _pPlayer;
	cocos2d::Vec2 _touchBeginPos;
	cocos2d::Vec2 _touchEndPos;
};


