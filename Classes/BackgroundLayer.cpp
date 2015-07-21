#include "BackgroundLayer.h"

USING_NS_CC;

BackgroundLayer::BackgroundLayer()
{
}

BackgroundLayer::~BackgroundLayer()
{
}

bool BackgroundLayer::init(const char * szFileName)
{
	if (!Layer::init())
	{
		return false;
	}
	auto backgroundSprite = Sprite::create(szFileName);
	backgroundSprite->setAnchorPoint(Vec2(0, 0));
	this->addChild(backgroundSprite);
	return true;
}