#pragma once
#include "cocos2d.h"

//速度应该作为玩家、金币、怪物的属性，摄像机只做跟随操作

class Player:public cocos2d::Ref
{
	CREATE_FUNC(Player);
	Player();
public:
	~Player();
	bool init(const std::string &pathName = "model/zhanshi_pao.c3b");

	cocos2d::Sprite3D * getCurPlayerSprite();

	static Player * getInstance();

	static void destroyInstance();
	

private:
	cocos2d::Sprite3D * _pSprite;
	static Player * s_pPlayer;
};

