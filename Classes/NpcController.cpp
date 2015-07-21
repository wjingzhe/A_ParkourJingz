#include "NpcController.h"
#include "cocos2d.h"
#include <ctime>
#include "Obstacle.h"
#include "Coin.h"
#include "MapSequences.h"
#include "Player.h"

USING_NS_CC;


#define TRACK_0 0
#define TRACK_1 1
#define TRACK_2 2

NpcController::NpcController() :_pCurMapSequences(nullptr), _pPlayer(nullptr), _pGameLayer(nullptr)
{
	//用时间函数初始化随机种子
	srand(static_cast<unsigned int>(clock()));
}

NpcController::~NpcController()
{
	if (_pCurMapSequences !=nullptr)
	{
		_pCurMapSequences = nullptr;
	}

	for each (auto ptr in _vSequencesPtr)
	{
		delete ptr;
	}
	_vSequencesPtr.clear();

	CC_SAFE_RELEASE_NULL(_pPlayer);

	CC_SAFE_RELEASE_NULL(_pGameLayer);
}
//先使用，迟点调整模块结构
bool NpcController::init(Player * pPlayer, cocos2d::Layer * pGameLayer)
{
	CC_SAFE_RETAIN(pPlayer);
	CC_SAFE_RETAIN(pGameLayer);

	CC_SAFE_RELEASE_NULL(_pPlayer);
	CC_SAFE_RELEASE_NULL(_pGameLayer);

	_pPlayer = pPlayer;
	_pGameLayer = pGameLayer;

	this->insertMapSequence(new MapSequences());
	Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
	return true;
}

void NpcController::update(float delta)
{
	randomGenElement(_pPlayer, _pGameLayer, delta);
}

void NpcController::randomGenElement(Player * pPlayer, cocos2d::Node * pRenderNode, float dt)
{
	static float fObstacleStepTime = 0.0f;

	fObstacleStepTime += dt;

	//每隔0.5秒生成一次障碍物
	if (fObstacleStepTime > 0.5)
	{
		generateObstacle(pPlayer, pRenderNode, dt);
		fObstacleStepTime = 0.0f;
	}

}

SequenceInfo NpcController::pumpSequence()
{
	if (!_pCurMapSequences || _pCurMapSequences->isEnd())
	{

		unsigned int index = rand() % this->_vSequencesPtr.size();
		_pCurMapSequences = this->_vSequencesPtr[index];

	}
	return _pCurMapSequences->pumpSequence();
}


void NpcController::generateObstacle(Player * pPlayer, cocos2d::Node * pRenderNode, float dt)
{
	auto seq = pumpSequence();

#define POS_LEFT -10
#define POS_MIDDLE 0
#define POS_RIGHT 10

#define GEN_ELEMENTS(NUM,POS_X) switch(NUM) \
		{\
	case EMPTY:\
		break;\
		\
	case MONSTER:\
			{\
			auto temp = Obstacle::create();\
			vpMoveableElems.pushBack(temp);\
			pRenderNode->addChild(temp->getCurSprite());\
			temp->getCurSprite()->setPosition3D(Vec3(POS_X, -5, -250+pPlayer->getCurPlayerSprite()->getPositionZ()));\
		}\
		break;\
	   \
	case COIN:\
		{\
			auto temp = Coin::create(); \
			vpMoveableElems.pushBack(temp);\
			pRenderNode->addChild(temp->getCurSprite()); \
			temp->getCurSprite()->setPosition3D(Vec3(POS_X, 0, -250+pPlayer->getCurPlayerSprite()->getPositionZ())); \
			temp->getCurSprite()->setRotation3D(Vec3(90.0f, 0.0f, 180.0f));\
		}\
		break;\
	}

	GEN_ELEMENTS(seq.left, POS_LEFT);
	GEN_ELEMENTS(seq.middle, POS_MIDDLE);
	GEN_ELEMENTS(seq.right, POS_RIGHT);
}

