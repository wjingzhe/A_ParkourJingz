#include "PlayerController.h"
#include "Player.h"

USING_NS_CC;

#define TURN_LEFT 1
#define TURN_RIGHT 2

#define MIDDLE_LINE_POS_X 0

PlayerController::PlayerController(Player * player) 
	:_pPlayer(nullptr)
	, _fStepLength(1.0f), _fElapsed(0.0f), _fPerTime(1/60.0f)
	, _bMovePlayerMode(false), _pTouchListenerOneByOne(nullptr)
{
	this->_pPlayer = player;
	CC_SAFE_RETAIN(this->_pPlayer);

	_fStepLength = _pPlayer->getMoveSpeed()*_fPerTime;
}

PlayerController::~PlayerController()
{
	if (_pTouchListenerOneByOne != nullptr)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(_pTouchListenerOneByOne);
		CC_SAFE_RELEASE_NULL(_pTouchListenerOneByOne);
	}

	Director::getInstance()->getScheduler()->unscheduleUpdate(this);
	CC_SAFE_RELEASE_NULL(this->_pPlayer);
}

PlayerController * PlayerController::create(Player * player)
{
	PlayerController *pRet = new(std::nothrow) PlayerController(player);
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}

}


bool PlayerController::init()
{
	return true; 
}

bool PlayerController::onTouchBegan(Touch *touch, Event *unused_event)
{
	this->_touchBeginPos = std::move(touch->getLocation());
	return true;
}

void PlayerController::onTouchEnded(Touch *touch, Event *unused_event)
{
	this->_touchEndPos = std::move(touch->getLocation());

	Vec2 diff = _touchEndPos - _touchBeginPos;

	diff.normalize();

	auto temp = Vec2(1, 0);//horizontal line

	auto result = Vec2::dot(diff, temp);

	//转向动作抖动阀值，偏移绝对量大于阀值才认定为有效的左右移动
	const float Threshold = std::sqrt(2) / 2;//假如刚好移动方向和水平方位处于45度角（-135°）时，点乘值为sqrt(2)/2，即平行四边形的面积
	auto player = _pPlayer;
	auto sportStatus = _pPlayer->getSportStatus();
	if (std::abs(result) > Threshold)
	{
		if (result > 0) // right
		{
			//可以移动 且 不是正执行左右移动操作 Gets an action from the running action list by its tag.
			if (_pPlayer->getCurSprite()->getPositionX() <= MIDDLE_LINE_POS_X
				&& (sportStatus & ELEM_STATUS_TURNING) != ELEM_STATUS_TURNING)
			{
				auto action = MoveBy::create(0.2f, Vec3(10.0f, 0, 0));
				auto callback = CCCallFunc::create([sportStatus, player]() mutable {player->setSportStatus(sportStatus); });
				auto pActionSeq = cocos2d::Sequence::createWithTwoActions(action, callback);
				action->setTag(TURN_RIGHT);
				this->_pPlayer->getCurSprite()->runAction(pActionSeq);
				_pPlayer->setSportStatus(sportStatus | ELEM_STATUS_TURNING);
			}
		}
		else //left
		{
			//可以移动 且 不是正执行左右移动操作 Gets an action from the running action list by its tag.
			if (_pPlayer->getCurSprite()->getPositionX() >= MIDDLE_LINE_POS_X
				&& (sportStatus & ELEM_STATUS_TURNING) != ELEM_STATUS_TURNING)
			{
				auto action = MoveBy::create(0.2f, Vec3(-10.0f, 0, 0));
				auto callback = CCCallFunc::create([sportStatus, player]() mutable {player->setSportStatus(sportStatus); });
				auto pActionSeq = cocos2d::Sequence::createWithTwoActions(action, callback);
				action->setTag(TURN_LEFT);
				this->_pPlayer->getCurSprite()->runAction(pActionSeq);
				_pPlayer->setSportStatus(sportStatus | ELEM_STATUS_TURNING);
			}
		}
	}
	else //up or down
	{

#define MOVE_FORWARD(POS_X) \
		auto cameraMask = _pPlayer->getCurSprite()->getCameraMask();\
		\
		std::vector<Camera*> cameras = pRenderNode->getScene()->getCameras();\
		\
		auto func = [cameraMask](decltype(*cameras.begin()) targetCamera) ->bool\
			{\
				return ((unsigned short)targetCamera->getCameraFlag() & cameraMask) != 0;\
			};\
		\
		auto it = std::find_if(cameras.begin(), cameras.end(), func);\
		\
		while (it != cameras.end())\
		{\
			auto temp = (*it)->getPosition3D();\
			temp.add(Vec3(0, 0, POS_X));\
			(*it)->setPosition3D(temp);\
			std::find_if(++it, cameras.end(), func);\
		}\
		_pPlayer->getCurSprite()->setPositionZ(_pPlayer->getCurSprite()->getPositionZ()+POS_X);


		if (diff.y > 0)
		{
			//可以跳跃
			if ((sportStatus & ELEM_STATUS_JUMPING) != ELEM_STATUS_JUMPING)
			{
				auto action = JumpBy::create(0.7f, Vec2(0.0f,0.0f),15.0f,1);
				auto callback = CCCallFunc::create([sportStatus, player]() mutable {player->setSportStatus(sportStatus); });
				auto pActionSeq = cocos2d::Sequence::createWithTwoActions(action, callback);
				action->setTag(TURN_LEFT);
				this->_pPlayer->getCurSprite()->runAction(pActionSeq);
				_pPlayer->setSportStatus(sportStatus | ELEM_STATUS_JUMPING);
			}

		}
		else
		{
			//MOVE_FORWARD(5);
		}
	}
}


void PlayerController::beganMovePlayer(void)
{
	_bMovePlayerMode = true;
}

void PlayerController::stopMovePlayer(void)
{
	_bMovePlayerMode = false;
}

void PlayerController::update(float delta)
{
	if (_bMovePlayerMode)
	{
		auto moveStep = _pPlayer->getMoveDirNormal() * _pPlayer->getMoveSpeed() * delta;

		auto temp = _pPlayer->getCurSprite()->getCameraMask();

		auto tempCameras = _pPlayer->getCurSprite()->getScene()->getCameras();

		for (auto it = tempCameras.begin(); it != tempCameras.end(); ++it)
		{
			if ((static_cast<unsigned short>((*it)->getCameraFlag()) & temp) != 0)
			{
				(*it)->setPosition3D((*it)->getPosition3D() + moveStep);
			}
		}

	}
	
}

void PlayerController::stopGame(void)
{
	Director::getInstance()->getScheduler()->unscheduleUpdate(this);
	if (_pTouchListenerOneByOne != nullptr)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(_pTouchListenerOneByOne);
		CC_SAFE_RELEASE_NULL(_pTouchListenerOneByOne);
	}
	_pPlayer->recycleSelf();
}

void PlayerController::startGame(void)
{
	if (_pTouchListenerOneByOne != nullptr)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(_pTouchListenerOneByOne);
		CC_SAFE_RELEASE_NULL(_pTouchListenerOneByOne);
	}

	_pTouchListenerOneByOne = EventListenerTouchOneByOne::create();
	CC_SAFE_RETAIN(_pTouchListenerOneByOne);

	_pTouchListenerOneByOne->setSwallowTouches(true);
	_pTouchListenerOneByOne->onTouchBegan = CC_CALLBACK_2(PlayerController::onTouchBegan, this);
	_pTouchListenerOneByOne->onTouchEnded = std::bind(&PlayerController::onTouchEnded, this, std::placeholders::_1, std::placeholders::_2);//实际使用当然是cocos封装的接口方便，但是要熟悉C++11就必须多使用
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_pTouchListenerOneByOne, 1);

	_pPlayer->setUsed();

	Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
}
