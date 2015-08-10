#pragma once

#include "cocos2d.h"
#include "MoveAbleElem.h"


class Coin :public MoveAbleElem
{
#define DEFAULT_MODEL_RES_PATH  "model/coin.c3b"
protected:
	Coin();
public:
	virtual ~Coin();

	bool init(const std::string &pathName = DEFAULT_MODEL_RES_PATH);

	static Coin* createWithAutoRealse()
	{
		Coin *pRet = new(std::nothrow) Coin();
#ifdef STD_VECTOR_ELEM
		if (pRet)
#else
		if (pRet)
#endif
		{
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
	}

	static Coin* create()
	{
		Coin *pRet = new(std::nothrow) Coin();
#ifdef STD_VECTOR_ELEM
		if (pRet)
#else
		if (pRet && pRet->init())
#endif
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

	virtual void initSprite()
	{
		init();
	}

	virtual void update(float dt) override;

	//自己被击效果
	virtual void beHitted(MoveAbleElem * pMoveAbleElem);

private:
	int _iGold;
};

