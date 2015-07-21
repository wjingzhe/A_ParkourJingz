#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::Scene
{
protected:
	MainScene();

public:
	~MainScene();

    bool init();

	//void update(float dt)override;

	CREATE_FUNC(MainScene);

private:
	cocos2d::Camera * _pSelfCamera;
};

#endif // __MAIN_SCENE_H__
