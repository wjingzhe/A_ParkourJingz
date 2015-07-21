#pragma once

#include "cocos2d.h"
#include "MoveableElems.h"

#define DEFAULT_MODEL_RES_PATH  "model/coin.c3b"

class Coin :public MoveableElems
{
protected:
	Coin();
public:
	virtual ~Coin();

	bool init(const std::string &pathName = DEFAULT_MODEL_RES_PATH);

	cocos2d::Sprite3D * getCurSprite() override
	{
		return _pSprite;
	}

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

private:

};

