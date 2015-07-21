#pragma once
#include "cocos2d.h"
#include "MoveableElems.h"

//速度应该作为玩家、金币、怪物的属性，摄像机只做跟随操作

class Player :public MoveableElems
{
	Player();
public:
	~Player();
	bool init(const std::string &pathName = "model/zhanshi_pao.c3b");

	CREATE_FUNC(Player);
	
private:
};

