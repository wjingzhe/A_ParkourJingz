#pragma once

#include "cocos2d.h"

class MoveableElems :public cocos2d::Ref
{
	

public:
	~MoveableElems()
	{
		CC_SAFE_RELEASE_NULL(_pSprite);
	}

	virtual cocos2d::Sprite3D * getCurSprite(void)
	{
		return _pSprite;
	}

	virtual float getMoveSpeed(void)
	{
		return _fMoveSpeed;
	}
	virtual void setMoveSpeed(float fSpeed)
	{
		_fMoveSpeed = fSpeed;
	}

	cocos2d::Vec3 getMoveDir(void)
	{
		return _vMoveDir;
	}

	void setMoveDir(cocos2d::Vec3 dir)
	{
		_vMoveDir = dir;
	}

protected:
	MoveableElems() :_pSprite(nullptr), _vMoveDir(0, 0, 1), _fMoveSpeed(1.0f)
	{
		_pSprite = cocos2d::Sprite3D::create();
		CC_SAFE_RETAIN(_pSprite);
	}

	cocos2d::Sprite3D * _pSprite;
	float _fMoveSpeed;
	cocos2d::Vec3 _vMoveDir;
};