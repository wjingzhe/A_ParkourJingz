#pragma once
#include "cocos2d.h"
#include "MoveAbleElem.h"

//速度应该作为玩家、金币、怪物的属性，摄像机只做跟随操作

class Player :public MoveAbleElem,public cocos2d::Ref
{
#define DEFAULT_MODEL_RES_PATH "model/zhanshi_pao.c3b"
	Player();
public:
	~Player();
	bool init(const std::string &pathName = DEFAULT_MODEL_RES_PATH);

	static int registerSelf(void);

	static Player* create(const std::string &szModelPath = DEFAULT_MODEL_RES_PATH)
	{
		Player *pRet = new(std::nothrow) Player();
		if (pRet && pRet->init(szModelPath))
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

	
private:
};

