#pragma once

#include "cocos2d.h"

class Obstacle
{
protected:
	
	//CREATE_FUNC_WITH_ARGS(Obstacle,"model/piglet.c3b");

public:
	Obstacle();

	~Obstacle();

	bool init(const std::string &szModelPath = "model/piglet.c3b", const std::string &szTexturePath = "model/zhu0928.jpg");

	cocos2d::Sprite3D * getCurSprite()
	{
		return _pSprite;
	}



private:

	cocos2d::Sprite3D * _pSprite;

};
