#include "Coin.h"
#include "MoveAbleElemTypeDefines.h"
#include "RegitsteredEvents.h"

USING_NS_CC;

#define COMMON_COIN 10;

Coin::Coin()
{
	_iElemTypeId = COIN_TYPE_ID;
	_iGold = COMMON_COIN;
}

Coin::~Coin()
{
}

bool Coin::init(const std::string &pathName)
{
	CC_SAFE_RELEASE_NULL(_pSprite);

	this->_pSprite = Sprite3D::create(pathName);
	this->_pSprite->setRotation3D(Vec3(-90, 0, 90));
	this->_pSprite->setScale(0.3f);

	CC_SAFE_RETAIN(_pSprite);

	this->setMoveSpeed(0.0f);
	_bIsSpriteInit = true;
	return true;
}

void Coin::update(float dt)
{

}

void Coin::beHitted(MoveAbleElem * pMoveAbleElem)
{
	//todo ¼ÓÇ®
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(RegitsteredEvents::GOLD_CHANGED, new int(_iGold));
}