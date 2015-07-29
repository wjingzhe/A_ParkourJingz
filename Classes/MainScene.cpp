#include "MainScene.h"
#include "MainMenuLayer.h"
#include "BackgroundLayer.h"
#include "GameLayer.h"
USING_NS_CC;
#include "ElemsPreloadManager.h"

MainScene::MainScene() 
	:_pSelfCamera(nullptr)
{
}

MainScene::~MainScene()	
{
	CC_SAFE_RELEASE_NULL(_pSelfCamera);
}


// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

	ElemsPreloadManager::registerMoveAbleElemTypes();

	auto glView = Director::getInstance()->getOpenGLView();

	Size designSize = Size(960, 640);

	glView->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::SHOW_ALL);

	auto cameraBackground2D = Camera::createOrthographic(designSize.width, designSize.height, 0, 100);
	cameraBackground2D->setCameraFlag(CameraFlag::USER2);
	this->addChild(cameraBackground2D);
	cameraBackground2D->setDepth(-5);

	//todo 操作相机的添加顺序或排列方式才行
	auto cameraMainUI = Camera::createOrthographic(designSize.width, designSize.height, 0, 100);
	cameraMainUI->setCameraFlag(CameraFlag::USER4);
	this->addChild(cameraMainUI);
	cameraMainUI->setDepth(5);
	

	auto camera3D = Camera::createPerspective(35, GLfloat(designSize.width) / GLfloat(designSize.height), 1, 1000);
	camera3D->setCameraFlag(CameraFlag::DEFAULT);
	camera3D->setPosition3D(Vec3(0, 15, 10));
	camera3D->lookAt(Vec3(0, 5, -60), Vec3(0, 1, 0));
	this->addChild(camera3D);




	//远背景，使用正视角，固定摄像机位置
	auto pBgLayer = BackgroundLayer::create();
	this->addChild(pBgLayer, -20, "UI_Background");

	//主菜单界面，使用正视角，固定摄像机位置
	auto pMenuLayer = MainMenuLayer::create();
	this->addChild(pMenuLayer, 20, "UI_MainMenu");

	//3D
	auto pGameLayer = GameLayer::create();
	this->addChild(pGameLayer, 0, "Game_Main");

	
	

	//每个层使用了自己的摄像机视角
	pBgLayer->setCameraMask(static_cast<unsigned short>(CameraFlag::USER2));
	
	pGameLayer->setCameraMask(static_cast<unsigned short>(CameraFlag::DEFAULT));

	pMenuLayer->setCameraMask(static_cast<unsigned short>(CameraFlag::USER4));


	//scheduleUpdate();

    return true;
}

//void MainScene::update(float dt)
//{
//	
//}


