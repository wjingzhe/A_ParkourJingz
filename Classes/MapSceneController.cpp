#include "MapSceneController.h"
#include "Player.h"

#define ROAD_SPRITE_MODEL_WIDTH 470.0f

USING_NS_CC;

//场景的有一段出现断拼感，已确认是资源问题，不是拼接问题
//资源来自网上，所以拼接的有问题，但不影响代码逻辑

MapSceneController::MapSceneController() 
	:_pGameLayer(nullptr), _pPlayer(nullptr), _pEventListenerAfterUpdate(nullptr)
	, _fStepLength(1.0f), _fElapsed(0.0f), _fPerTime(1/60.0f)
	, _bMoveSceneMode(false)
{
	
}

MapSceneController::~MapSceneController()
{

	CC_SAFE_RELEASE_NULL(_pPlayer);
	CC_SAFE_RELEASE_NULL(_pGameLayer);
	
	Director::getInstance()->getEventDispatcher()->removeEventListener(_pEventListenerAfterUpdate);
	CC_SAFE_RELEASE_NULL(_pEventListenerAfterUpdate);

	_vpRoadSprites.clear();
}

bool MapSceneController::init(Player * pPlayer, cocos2d::Layer * pGameLayer)
{
	CC_SAFE_RETAIN(pPlayer);
	CC_SAFE_RETAIN(pGameLayer);

	if (_pPlayer!=nullptr)
	{
		CC_SAFE_RELEASE(_pPlayer);
	}

	if (_pGameLayer != nullptr)
	{
		CC_SAFE_RELEASE(_pGameLayer);
	}

	_pPlayer = pPlayer;
	_pGameLayer = pGameLayer;

	preGenerate();

	CC_SAFE_RELEASE_NULL(_pEventListenerAfterUpdate);

	//std::bind(MapSceneController::afferUpdateCallback, this, std::placeholders::_1) == CC_CALLBACK_1(MapSceneController::afferUpdateCallback, this)
	_pEventListenerAfterUpdate = Director::getInstance()->getEventDispatcher()->addCustomEventListener
		(
		Director::EVENT_AFTER_UPDATE, std::bind(&MapSceneController::afferUpdateCallback, this, std::placeholders::_1)
		);
	
	CC_SAFE_RETAIN(_pEventListenerAfterUpdate);

	_fStepLength = 5;

	Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);

	return true;
}

void MapSceneController::preGenerate(void){
	//为什么是4，实际上我乱来的，没想好 这里刚好遇到一个问题，double转化为float导致截断问题
	//todo 
	for (int i = 0; i < 4; ++i)
	{
		auto pRoadSprite = Sprite3D::create("model/scene.c3b");
		pRoadSprite->setScale(0.2f);
		pRoadSprite->setRotation3D(Vec3(0, 90, 0));
		pRoadSprite->setPosition3D(Vec3(0, -5, -(ROAD_SPRITE_MODEL_WIDTH * i)));
		_pGameLayer->addChild(pRoadSprite, -100);

		_vpRoadSprites.pushBack(pRoadSprite);
	}
};

void MapSceneController::afferUpdateCallback(EventCustom * pEventCustom)
{
	//每次update完，精灵的固定位移动作已完成，这个时候判断精灵处于地图的那一端
	linkRoads();
}

void MapSceneController::linkRoads(void)
{
	//目前角色移动只有前后方向操作，所以暂时只需要根据z坐标进行实际逻辑实现
	auto pPlayer = _pPlayer;

	auto index = _vpRoadSprites.size();

	for each (auto pSprite in _vpRoadSprites)
	{
		auto pos = pSprite->getAABB().getCenter();
		pos.set(pos.x, pos.y, pPlayer->getCurPlayerSprite()->getPositionZ());
		if (pSprite->getAABB().containPoint(pos))
		{
			index = _vpRoadSprites.getIndex(pSprite);
			break;
		}
	}
	
	if (index >= _vpRoadSprites.size()/2)
	{
		auto size = _vpRoadSprites.size();
		for (decltype(index) i = 0; i < index; ++i)
		{
			auto pSprite = _vpRoadSprites.at(0);
			pSprite->retain();
			pSprite->setPosition3D(pSprite->getPosition3D() + Vec3(0, 0, -(ROAD_SPRITE_MODEL_WIDTH * static_cast<float>(size))));
			_vpRoadSprites.eraseObject(pSprite);
			_vpRoadSprites.pushBack(pSprite);
			pSprite->release();
		}
	}
	
}

void MapSceneController::update(float delta)
{
	if (_bMoveSceneMode)
	{
		_fElapsed += delta;
		if (_fElapsed >= _fPerTime)
		{
			moveScene(Vec3(0, 0, _fStepLength));
			_fElapsed = 0.0f;
		}
	}
	
}

void MapSceneController::moveScene(const Vec3 &pos)
{

	for each (auto pSprite in _vpRoadSprites)
	{
		pSprite->setPosition3D(pSprite->getPosition3D() + pos);
	}
	
}

void MapSceneController::beganMoveScene(void)
{
	_bMoveSceneMode = true;
}

void MapSceneController::stopMoveScene(void)
{
	_bMoveSceneMode = false;
}

