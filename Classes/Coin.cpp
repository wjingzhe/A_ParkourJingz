#include "Coin.h"
#include "MoveAbleElemManager.h"

USING_NS_CC;

Coin::Coin()
{
	_iElemTypeId = 2;
}

Coin::~Coin()
{
	CC_SAFE_RELEASE_NULL(_pSprite);
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

int Coin::registerSelf(void)
{
	MoveAbleElemManager::getInstance()->registerElemAndFactory(2, MoveAbleElemFactory<Coin>::create);
	return 0;
}

static int  a = Coin::registerSelf();//注册，同时完成预生成