#include "Obstacle.h"
#include "MoveAbleElemTypeDefines.h"

USING_NS_CC;

Obstacle::Obstacle()
{
	_iElemTypeId = OBSTACLE__ID;
}

Obstacle::~Obstacle()
{
}

bool Obstacle::init(const std::string &szModelPath, const std::string &szTexturePath)
{

	
	CC_SAFE_RELEASE_NULL(_pSprite);
	_pSprite = Sprite3D::create(szModelPath, szTexturePath);
	CC_SAFE_RETAIN(_pSprite);
	_pSprite->setLocalZOrder(100);//？？ //todo 
	//_pSprite->setRotation3D(Vec3(-90, 0, 90));
	_pSprite->setScale(0.1f);

	this->setMoveSpeed(1.0f*60.0f);

	CC_SAFE_RELEASE_NULL(_pAction);
	//动作为绕y轴旋转90度
	_pAction = RepeatForever::create(MoveBy::create(2.0f, this->getMoveSpeed() * 2.0f * this->getMoveDirNormal()));
	CC_SAFE_RETAIN(_pAction);
	_pSprite->runAction(_pAction);

	_bIsSpriteInit = true;

	return true;
}

void Obstacle::update(float dt)
{
}

void Obstacle::beHitted(MoveAbleElem * pMoveAbleElem)
{
	//todo
	//如果是子弹类型，则播放死亡特效

	//如果是玩家，则不处理
}

void Obstacle::recycleSelf(void)
{
	_pSprite->setLocalZOrder(100);//？？ //todo 
	//_pSprite->setRotation3D(Vec3(-90, 0, 90));
	_pSprite->setScale(0.1f);

	this->setMoveSpeed(1.0f*60.0f);

	_bIsSpriteInit = true;

	MoveAbleElem::recycleSelf();
}