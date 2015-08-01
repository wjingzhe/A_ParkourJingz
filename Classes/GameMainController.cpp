#include "GameMainController.h"
#include "Player.h"
#include "MapSceneController.h"
#include "PlayerController.h"
#include "NpcController.h"
#include "RegitsteredEvents.h"
#include "MainScene.h"
#include "MainMenuLayer.h"

USING_NS_CC;

GameMainController::GameMainController() 
	:_pMapSceneController(nullptr), _pPlayerController(nullptr), _pNpcController(nullptr)
	, _pGameLayer(nullptr), _pMainMenuLayer(nullptr)
	, _pEventListenerStopGame(nullptr), _pEventListenerStartGame(nullptr), _pEventListenerRestartGame(nullptr), _pEventListenerShowRestartButton(nullptr)
	, _eMode(MOVE_MODE::NONE)
{
}

GameMainController::~GameMainController()
{
	if (_pEventListenerStopGame)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(_pEventListenerStopGame);
		CC_SAFE_RELEASE_NULL(_pEventListenerStopGame);
	}

	if (_pEventListenerStartGame)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(_pEventListenerStartGame);
		CC_SAFE_RELEASE_NULL(_pEventListenerStartGame);
	}

	if (_pEventListenerRestartGame)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(_pEventListenerRestartGame);
		CC_SAFE_RELEASE_NULL(_pEventListenerRestartGame);
	}

	if (_pEventListenerShowRestartButton)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(_pEventListenerShowRestartButton);
		CC_SAFE_RELEASE_NULL(_pEventListenerShowRestartButton);
	}

	CC_SAFE_RELEASE_NULL(_pPlayerController);
	CC_SAFE_RELEASE_NULL(_pMapSceneController);
	CC_SAFE_RELEASE_NULL(_pNpcController);

	CC_SAFE_RELEASE_NULL(_pGameLayer);
	CC_SAFE_RELEASE_NULL(_pMainMenuLayer);
}

bool GameMainController::init(Player * pPlayer, Layer * pGameLayer, Layer * pMainMenuLayer)
{
	CC_SAFE_RETAIN(pGameLayer);
	CC_SAFE_RELEASE(_pGameLayer);
	_pGameLayer = pGameLayer;

	CC_SAFE_RETAIN(pMainMenuLayer);
	CC_SAFE_RELEASE(_pMainMenuLayer);
	_pMainMenuLayer = pMainMenuLayer;

	CC_SAFE_RETAIN(pPlayer);

	CC_SAFE_RELEASE_NULL(_pMapSceneController);
	_pMapSceneController = MapSceneController::create(pPlayer, pGameLayer);
	CC_SAFE_RETAIN(_pMapSceneController);

	CC_SAFE_RELEASE(_pPlayerController);
	_pPlayerController = PlayerController::create(pPlayer);
	CC_SAFE_RETAIN(_pPlayerController);

	CC_SAFE_RELEASE_NULL(_pNpcController);
	_pNpcController = NpcController::create(pPlayer, pGameLayer);
	CC_SAFE_RETAIN(_pNpcController);


	CC_SAFE_RELEASE_NULL(pPlayer);
	

	CC_SAFE_RELEASE_NULL(_pEventListenerStartGame);
	_pEventListenerStartGame = Director::getInstance()->getEventDispatcher()->addCustomEventListener
		(
		RegitsteredEvents::GAME_START,
		std::bind(&GameMainController::onStart, this, std::placeholders::_1)
		);
	CC_SAFE_RETAIN(_pEventListenerStartGame);


	return true;
}

void GameMainController::onStop(cocos2d::EventCustom * pEvent)
{
	if (_pEventListenerStopGame)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(_pEventListenerStopGame);
		CC_SAFE_RELEASE_NULL(_pEventListenerStopGame);
	}

	if (_pEventListenerStartGame)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(_pEventListenerStartGame);
		CC_SAFE_RELEASE_NULL(_pEventListenerStartGame);
	}

	if (_pEventListenerShowRestartButton)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(_pEventListenerShowRestartButton);
		CC_SAFE_RELEASE_NULL(_pEventListenerShowRestartButton);
	}


	_pPlayerController->stopGame();
	_pMapSceneController->stopGame();
	_pNpcController->stopGame();

	
}
void GameMainController::onShowRestart(cocos2d::EventCustom * pEvent)
{
	static_cast<MainMenuLayer *> (_pMainMenuLayer)->showRestart();
}


void GameMainController::onStart(cocos2d::EventCustom * pEvent)
{
	if (_pEventListenerStartGame)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(_pEventListenerStartGame);
		CC_SAFE_RELEASE_NULL(_pEventListenerStartGame);
	}

	CC_SAFE_RELEASE_NULL(_pEventListenerStopGame);
	_pEventListenerStopGame = Director::getInstance()->getEventDispatcher()->addCustomEventListener
		(
		RegitsteredEvents::GAME_OVER,
		std::bind(&GameMainController::onStop, this, std::placeholders::_1)
		);
	CC_SAFE_RETAIN(_pEventListenerStopGame);

	CC_SAFE_RELEASE_NULL(_pEventListenerRestartGame);
	_pEventListenerRestartGame = Director::getInstance()->getEventDispatcher()->addCustomEventListener
		(
		RegitsteredEvents::GAME_RESTART,
		std::bind(&GameMainController::onRestart, this, std::placeholders::_1)
		);
	CC_SAFE_RETAIN(_pEventListenerRestartGame);

	CC_SAFE_RELEASE_NULL(_pEventListenerShowRestartButton);
	_pEventListenerShowRestartButton = Director::getInstance()->getEventDispatcher()->addCustomEventListener
		(
		RegitsteredEvents::SHOW_RESTART,
		std::bind(&GameMainController::onShowRestart, this, std::placeholders::_1)
		);
	CC_SAFE_RETAIN(_pEventListenerShowRestartButton);

	_pMapSceneController->startGame();
	_pPlayerController->startGame();
	_pNpcController->startGame();
	setMoveMode(GameMainController::PLAYER);
}

void GameMainController::onRestart(cocos2d::EventCustom * pEvent)
{
	Director::getInstance()->replaceScene(MainScene::create());
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
