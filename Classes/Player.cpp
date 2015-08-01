#include "Player.h"
#include "MoveAbleElemTypeDefines.h"
#include "RegitsteredEvents.h"

USING_NS_CC;

Player::Player() :_uSportStatus(ELEM_STATUS_FREE_STYLE)
{
	_vMoveDir = Vec3(0, 0, -1.0f), _fMoveSpeed = 1.0f*60.0f;
	_vMoveDir.normalize();
	_iElemTypeId = PLAYER_TYPE_ID;
}

Player::~Player()
{
}

bool Player::init(const std::string &pathName)
{
	if (_pSprite != nullptr)
	{
		CC_SAFE_RELEASE_NULL(_pSprite);
	}
	_pSprite = Sprite3D::create(pathName);
	_pSprite->setRotation3D(Vec3(0, 180, 0));

	CC_SAFE_RETAIN(_pSprite);

	//模型资源中一般和骨骼动作通道一起导出，第二个参数是导出的动画通道，可以我不清楚原资源的通道内容
	//创建动作对象
	auto animation = Animation3D::create(pathName);
	auto animate = Animate3D::create(animation);
	_pSprite->runAction(RepeatForever::create(animate));

	_bIsSpriteInit = true;
	_uSportStatus = ELEM_STATUS_MOVING;
	return true;
}

//自己被击效果
void Player::beHitted(MoveAbleElem * pMoveAbleElem)
{
	if (pMoveAbleElem->getElemType() == OBSTACLE__ID)
	{
		//TODO 此处应该播放死亡动作后回调派发死亡消息，暂时不知道死亡动作
		_pSprite->stopAllActions();
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(RegitsteredEvents::SHOW_RESTART);
	}
}

//被使用状态启动计时器更新自身状态
void Player::setUsed(void)
{
	if (_pAction!=nullptr)
	{
		_pSprite->stopAction(_pAction);
		CC_SAFE_RELEASE_NULL(_pAction);
	}
	
	//动作为绕y轴旋转90度
	_pAction = RepeatForever::create(MoveBy::create(2.0f, this->getMoveSpeed() * 2.0f * this->getMoveDirNormal()));
	CC_SAFE_RETAIN(_pAction);
	_pSprite->runAction(_pAction);
}