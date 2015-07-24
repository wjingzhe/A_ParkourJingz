#pragma once

#include "cocos2d.h"
#include "MoveAbleElem.h"

class MoveAbleElemManager;

class Coin :public MoveAbleElem
{
#define DEFAULT_MODEL_RES_PATH  "model/coin.c3b"
	friend MoveAbleElemManager;
protected:
	Coin();
public:
	virtual ~Coin();

	bool init(const std::string &pathName = DEFAULT_MODEL_RES_PATH);

	static Coin* create(const std::string &szModelPath = DEFAULT_MODEL_RES_PATH)
	{
		Coin *pRet = new(std::nothrow) Coin();
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

	virtual void update(float dt) override;


	static int registerSelf(void);

private:

};

