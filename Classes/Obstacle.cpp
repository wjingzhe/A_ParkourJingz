#include "Obstacle.h"

USING_NS_CC;

Obstacle::Obstacle() :_pSprite(nullptr)
{

}

Obstacle::~Obstacle()
{
	CC_SAFE_RELEASE_NULL(_pSprite);
}

bool Obstacle::init(const std::string &szModelPath, const std::string &szTexturePath)
{
	CC_SAFE_RELEASE_NULL(_pSprite);
	_pSprite = Sprite3D::create(szModelPath);
	CC_SAFE_RETAIN(_pSprite);

	_pSprite->setTexture(szTexturePath);
	_pSprite->setLocalZOrder(100);//£¿£¿ //todo 
	//_pSprite->setRotation3D(Vec3(-90, 0, 90));
	_pSprite->setScale(0.1);

	return true;
}