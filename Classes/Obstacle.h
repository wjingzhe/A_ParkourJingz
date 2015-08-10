#pragma once
#include "cocos2d.h"
#include "MoveAbleElem.h"



class Obstacle :public MoveAbleElem
{
#define DEFAULT_MODEL_RES_PATH  "model/piglet.c3b"
#define DEFAULT_TEXTURE_RES_PATH  "model/zhu0928.jpg"
protected:
	Obstacle();

public:
	
	virtual ~Obstacle();

	bool init(const std::string &szModelPath = DEFAULT_MODEL_RES_PATH, const std::string &szTexturePath = DEFAULT_TEXTURE_RES_PATH);

	static Obstacle* createWithAutoRealse(const std::string &szModelPath = DEFAULT_MODEL_RES_PATH, const std::string &szTexturePath = DEFAULT_TEXTURE_RES_PATH)
	{
		Obstacle *pRet = new(std::nothrow) Obstacle();
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

	static Obstacle* create(const std::string &szModelPath = DEFAULT_MODEL_RES_PATH, const std::string &szTexturePath = DEFAULT_TEXTURE_RES_PATH)
	{
		Obstacle *pRet = new(std::nothrow) Obstacle();
#ifdef STD_VECTOR_ELEM
		if (pRet)
#else
		if (pRet&&pRet->init())
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

	virtual void recycleSelf(void);

private:
};
