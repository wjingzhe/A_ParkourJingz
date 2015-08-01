#include "MainScene.h"
#include "MainMenuLayer.h"
#include "BackgroundLayer.h"
#include "GameLayer.h"
USING_NS_CC;
#include "ElemsPreloadManager.h"
#include "GameMainController.h"

MainScene::MainScene() 
	:_pSelfCamera(nullptr), _pGameMainController(nullptr)
{
}

MainScene::~MainScene()	
{
	CC_SAFE_RELEASE_NULL(_pSelfCamera);
	CC_SAFE_RELEASE_NULL(_pGameMainController);
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

	Size designSize = Size(960, 540);
	auto screanRatio = glView->getFrameSize().width / glView->getFrameSize().height;
	auto ratio_16_9 = 16.0f / 9.0f;
	if (screanRatio < ratio_16_9)
	{
		designSize = Size(960, 640);
	}

	glView->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::NO_BORDER);

	auto cameraBackground2D = Camera::createOrthographic(designSize.width, designSize.height, 0, 100);
	cameraBackground2D->setCameraFlag(CameraFlag::USER2);
	this->addChild(cameraBackground2D);
	cameraBackground2D->setDepth(-5);

	//todo 操作相机的添加顺序或排列方式才行
	auto cameraMainUI = Camera::createOrthographic(designSize.width, designSize.height, 0, 100);
	cameraMainUI->setCameraFlag(CameraFlag::USER4);
	this->addChild(cameraMainUI);
	cameraMainUI->setDepth(5);
	

	auto camera3D = Camera::createPerspective(35, GLfloat(designSize.width) / GLfloat(designSize.height), 1, 800);
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

	CC_SAFE_RELEASE_NULL(_pGameMainController);
	_pGameMainController = GameMainController::create(pGameLayer->getPlayer(), pGameLayer, pMenuLayer);
	CC_SAFE_RETAIN(_pGameMainController);
	//scheduleUpdate();
	_pGameMainController->onStart(nullptr);
    return true;
}

//void MainScene::update(float dt)
//{
//	
//}


