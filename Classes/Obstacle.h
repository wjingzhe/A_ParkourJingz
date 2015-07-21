#pragma once
#include "cocos2d.h"
#include "MoveableElems.h"



class Obstacle :public MoveableElems
{
#define DEFAULT_MODEL_RES_PATH  "model/piglet.c3b"
#define DEFAULT_TEXTURE_RES_PATH  "model/zhu0928.jpg"
protected:
	Obstacle();
public:
	
	virtual ~Obstacle();

	bool init(const std::string &szModelPath = DEFAULT_MODEL_RES_PATH, const std::string &szTexturePath = DEFAULT_TEXTURE_RES_PATH);

	static Obstacle* create(const std::string &szModelPath = DEFAULT_MODEL_RES_PATH, const std::string &szTexturePath = DEFAULT_TEXTURE_RES_PATH)
	{
		Obstacle *pRet = new(std::nothrow) Obstacle();
		if (pRet && pRet->init(szModelPath, szTexturePath))
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
