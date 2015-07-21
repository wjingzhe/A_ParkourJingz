#include "GameMainController.h"
#include "Player.h"
#include "MapSceneController.h"
#include "PlayerController.h"

USING_NS_CC;

GameMainController::GameMainController() 
	:_pMapSceneController(nullptr), _pPlayerController(nullptr), _pGameLayer(nullptr), _pEventListenerAfterDraw(nullptr)
	, _eMode(MOVE_MODE::PLAYER)
{
}

GameMainController::~GameMainController()
{
	CC_SAFE_RELEASE_NULL(_pPlayerController);
	CC_SAFE_RELEASE_NULL(_pMapSceneController);
	Director::getInstance()->getEventDispatcher()->removeEventListener(_pEventListenerAfterDraw);
	CC_SAFE_RELEASE_NULL(_pEventListenerAfterDraw);
}

bool GameMainController::init(Player * pPlayer,Layer * pGameLayer)
{
	CC_SAFE_RELEASE_NULL(_pMapSceneController);
	_pMapSceneController = MapSceneController::create(pPlayer, pGameLayer);
	CC_SAFE_RETAIN(_pMapSceneController);

	CC_SAFE_RELEASE(_pPlayerController);
	_pPlayerController = PlayerController::create(pPlayer);
	CC_SAFE_RETAIN(_pPlayerController);

	CC_SAFE_RETAIN(pGameLayer);
	CC_SAFE_RELEASE(_pGameLayer);
	_pGameLayer = pGameLayer;
	

	CC_SAFE_RELEASE_NULL(_pEventListenerAfterDraw);

	_pEventListenerAfterDraw = Director::getInstance()->getEventDispatcher()->addCustomEventListener
		(
		Director::EVENT_AFTER_DRAW, 
		std::bind(&GameMainController::onAfterDraw, this, std::placeholders::_1)
		);

	_pEventListenerAfterDraw->retain();//ÎÒ¹ÊÒâµÄ

	return true;
}



bool GameMainController::onTouchBegan(Touch *touch, Event *unused_event)
{
	_pPlayerController->reveiveTouchBegin(touch->getLocation(), _pGameLayer);
	return true;
}

void GameMainController::onTouchEnded(Touch *touch, Event *unused_event)
{
	_pPlayerController->reveiveTouchEnd(touch->getLocation(), _pGameLayer);
}

void GameMainController::onAfterDraw(cocos2d::EventCustom * pEvent)
{

}

void GameMainController::setMoveMode(MOVE_MODE mode)
{
	_eMode = mode;

	switch (_eMode)
	{
	case GameMainController::SCENE:
		_pPlayerController->stopMovePlayer();
		_pMapSceneController->beganMoveScene();
		break;

	case GameMainController::PLAYER:
		_pMapSceneController->stopMoveScene();
		_pPlayerController->beganMovePlayer();
		break;

	case GameMainController::BOTH_SCENE_AND_PLAYER:
		_pMapSceneController->beganMoveScene();
		_pPlayerController->beganMovePlayer();
		break;
	case GameMainController::NONE:
		_pPlayerController->stopMovePlayer();
		_pMapSceneController->stopMoveScene();
		break;
	default:
		break;
	}
}