#pragma once

#include "cocos2d.h"

class Coin
{
protected:
	

public:
	//CREATE_FUNC_WITH_ARGS(Coin, "model/coin.c3b");
	Coin();
	~Coin();

	bool init(const std::string &pathName = "model/coin.c3b");

	cocos2d::Sprite3D * getCurSprite()
	{
		return _pSprite;
	}

private:

	cocos2d::Sprite3D * _pSprite;

};

