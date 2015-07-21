#pragma once

#include "cocos2d.h"

class MoveableElems :public cocos2d::Ref
{
	

public:
	~MoveableElems()
	{
		CC_SAFE_RELEASE_NULL(_pSprite);
	}

	virtual cocos2d::Sprite3D * getCurSprite(void) = 0;

protected:
	MoveableElems() :_pSprite(nullptr)
	{

	}
	cocos2d::Sprite3D * _pSprite;

};