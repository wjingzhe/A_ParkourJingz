#pragma once
#include "cocos2d.h"
#include "MoveAbleElem.h"


#define ELEM_STATUS_FREE_STYLE (0)
#define ELEM_STATUS_SPORTING (1)
#define ELEM_STATUS_KEEP_STANDING (1<<1 | ELEM_STATUS_FREE_STYLE)
#define ELEM_STATUS_MOVING (1<<2 | ELEM_STATUS_SPORTING)
#define ELEM_STATUS_JUMPING (1<<3 | ELEM_STATUS_SPORTING)
#define ELEM_STATUS_TURNING (1<<4 | ELEM_STATUS_SPORTING)

#ifdef STD_VECTOR_ELEM
class Player :public MoveAbleElem, public cocos2d::Ref
#else
class Player :public MoveAbleElem
#endif
{
#define DEFAULT_MODEL_RES_PATH "model/zhanshi_pao.c3b"
	Player();
public:
	virtual ~Player();
	bool init(const std::string &pathName = DEFAULT_MODEL_RES_PATH);

	static Player* createWithAutoRealse(const std::string &szModelPath = DEFAULT_MODEL_RES_PATH)
	{
		Player *pRet = new(std::nothrow) Player();
		if (pRet)
		{
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
	}
	

	static Player* create(const std::string &szModelPath = DEFAULT_MODEL_RES_PATH)
	{
		Player *pRet = new(std::nothrow) Player();
		if (pRet && pRet->init(szModelPath))
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

	virtual void initSprite()
	{
		init();
	}

	unsigned int getSportStatus(void)
	{
		return _uSportStatus;
	}

	void setSportStatus(unsigned int newStatus)
	{
		_uSportStatus = newStatus;
	}

	virtual void beHitted(MoveAbleElem * pMoveAbleElem);
	
	//被使用状态启动计时器更新自身状态
	virtual void setUsed(void);

private:
	unsigned int _uSportStatus;
};

