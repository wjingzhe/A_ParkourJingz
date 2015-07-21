#pragma once
#include "cocos2d.h"

class BackgroundLayer :public cocos2d::Layer
{
	BackgroundLayer();
public:
	~BackgroundLayer();

	bool init(const char * szFileName = "model/back_ground.jpg");

	CREATE_FUNC(BackgroundLayer);

	CC_DISALLOW_COPY_AND_ASSIGN(BackgroundLayer);


private:

};