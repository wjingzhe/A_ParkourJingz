#include "ProcedureGenController.h"
#include "cocos2d.h"
#include <ctime>
#include "Obstacle.h"
#include "Coin.h"
#include "MapSequences.h"

USING_NS_CC;


#define TRACK_0 0
#define TRACK_1 1
#define TRACK_2 2

ProcedureGenController::ProcedureGenController() :_pCurSequences(nullptr)
{
	//用时间函数初始化随机种子
	srand(static_cast<unsigned int>(clock()));
}

ProcedureGenController::~ProcedureGenController()
{
	if (_pCurSequences !=nullptr)
	{
		_pCurSequences = nullptr;
	}

	for each (auto ptr in _vSequencesPtr)
	{
		delete ptr;
	}
	_vSequencesPtr.clear();
}

void ProcedureGenController::randomGenElement(Player * pPlayer, cocos2d::Node * pRenderNode, float dt)
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

void ProcedureGenController::run(float dt)
{

}

SequenceInfo ProcedureGenController::pumpSequence()
{
	if (!_pCurSequences || _pCurSequences->isEnd())
	{

		unsigned int index = rand() % this->_vSequencesPtr.size();
		_pCurSequences = this->_vSequencesPtr[index];

	}
	return _pCurSequences->pumpSequence();
}


void ProcedureGenController::generateObstacle(Player * pPlayer, cocos2d::Node * pRenderNode, float dt)
{
	auto seq = pumpSequence();

#define POS_LEFT -10
#define POS_MIDDLE 0
#define POS_RIGHT 10

#define GEN_ELEMENTS(NUM,POS_X) switch(NUM) \
	{\
	case MONSTER:\
		{\
			auto temp = new Obstacle();\
			temp->init();\
			pRenderNode->addChild(temp->getCurSprite());\
			temp->getCurSprite()->setPosition3D(Vec3(POS_X, -5, -250));\
		}\
		break;\
	case EMPTY:\
		break;\
	case COIN:\
		{\
			auto temp = new Coin(); \
			temp->init(); \
			pRenderNode->addChild(temp->getCurSprite()); \
			temp->getCurSprite()->setPosition3D(Vec3(POS_X, -5, -250)); \
			temp->getCurSprite()->setRotation3D(Vec3(90, 0, 180));\
		}\
		break;\
	}

	GEN_ELEMENTS(seq.left, POS_LEFT);
	GEN_ELEMENTS(seq.middle, POS_MIDDLE);
	GEN_ELEMENTS(seq.right, POS_RIGHT);
}

