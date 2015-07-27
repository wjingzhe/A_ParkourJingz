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

	static Coin* create()
	{
		Coin *pRet = new(std::nothrow) Coin();
		if (pRet)
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

	virtual void initSprite()
	{
		init();
	}

	virtual void update(float dt) override;

	static int registerSelf(void);

private:

};

