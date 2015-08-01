#pragma once

#include "cocos2d.h"


/*
我曾经思考过一个C++注入机制，
现在我已经实现了类似的机制，但是没能让它自动被调用注册的代码，如今有个构思

在继承阶段，派生的初始化列表中增加调用派生类的static函数或者某些特定函数的可能性，这样子就能让继承之后实现注册。
这样子添加派生类代码时无需修改原先的代码，只需要重新编译即可

*/

#ifdef STD_VECTOR_ELEM
class MoveAbleElem
#else
class MoveAbleElem :public cocos2d::Ref
#endif
{
protected:
	MoveAbleElem() :_pSprite(nullptr), _vMoveDir(0, 0, 1), _fMoveSpeed(1.0f*60.0f)
		, _iElemTypeId(0), _bIsSpriteInit(false), _pAction(nullptr)
	{
		
	}

public:

	virtual ~MoveAbleElem()
	{
		cocos2d::Director::getInstance()->getScheduler()->unscheduleUpdate(this);
		CC_SAFE_RELEASE_NULL(_pSprite);
		CC_SAFE_RELEASE_NULL(_pAction);
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

	cocos2d::Vec3 getMoveDirNormal(void)
	{
		return _vMoveDir;
	}

	void setMoveDir(cocos2d::Vec3 dir)
	{
		_vMoveDir = dir;
		_vMoveDir.normalize();
	}

	virtual void update(float dt)
	{

	}

	unsigned int getElemType()
	{
		return _iElemTypeId;
	}

	void setElemType(unsigned int iTypeId)
	{
		_iElemTypeId = iTypeId;
	}

	virtual void recycleSelf(void)
	{
		_pSprite->pause();
		_pSprite->removeFromParentAndCleanup(false);
		cocos2d::Director::getInstance()->getScheduler()->unscheduleUpdate(this);
	}

	//被使用状态启动计时器更新自身状态
	virtual void setUsed(void)
	{
		if (!_bIsSpriteInit)
		{
			initSprite();;
		}
		cocos2d::Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
		_pSprite->resume();
	}
	
	virtual void initSprite()
	{
		CC_SAFE_RELEASE_NULL(_pSprite);
		_pSprite = cocos2d::Sprite3D::create();
		CC_SAFE_RETAIN(_pSprite);
		if (_pAction!=nullptr)
		{
			_pSprite->runAction(_pAction);
		}
	}


	virtual void hitOthers(MoveAbleElem * pMoveAbleElem, std::function<void(void)> callback = [](){})
	{
		//目标对象受击处理
		pMoveAbleElem->beHitted(this);
		//自身状态处理
		this->beHitted(pMoveAbleElem);
		//回调
		callback();
	}

	//自己被击效果
	virtual void beHitted(MoveAbleElem * pMoveAbleElem)
	{

	}

protected:
	cocos2d::Sprite3D * _pSprite;
	float _fMoveSpeed;
	cocos2d::Vec3 _vMoveDir;
	bool _bIsSpriteInit;
	unsigned int _iElemTypeId;
	cocos2d::Action * _pAction;
};