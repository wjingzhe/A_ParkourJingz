#pragma once

#include <vector>
#include "cocos2d.h"

class MapSequences;
struct SequenceInfo;
class Player;
class MoveAbleElem;

class NpcController:public cocos2d::Ref
{
	NpcController();
public:
	
	~NpcController();

	void randomGenElement(Player * pPlayer, cocos2d::Node * pRenderNode, float dt);
	void generateObstacle(Player * pPlayer, cocos2d::Node * pRenderNode, float dt);


	void insertMapSequence(MapSequences * map_sequence)
	{
		_vSequencesPtr.push_back(map_sequence);
	}

	void update(float delta);

	bool init(Player * pPlayer, cocos2d::Layer * pGameLayer);

	static NpcController * create(Player * pPlayer, cocos2d::Layer * pGameLayer)
	{
		NpcController *pRet = new(std::nothrow) NpcController();
		if (pRet && pRet->init(pPlayer, pGameLayer))
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

protected:
	SequenceInfo pumpSequence();

	//
	cocos2d::Vec3 && calcuratePosWillHit(MoveAbleElem * pElemSrc, Player * pElemTar, float fDtToHit);

private:
	MapSequences * _pCurMapSequences;
	std::vector<MapSequences *> _vSequencesPtr;


#ifdef STD_VECTOR_ELEM
	std::vector<MoveAbleElem *> vpMoveableElems;
#else
	cocos2d::Vector<MoveAbleElem *> vpMoveableElems;
#endif
	

	Player * _pPlayer;
	cocos2d::Layer * _pGameLayer;

	float _fRecationDt;

	cocos2d::Vec3 _diffCoinWithPlay;
	cocos2d::Vec3 _diffObstacleWithPlay;
};
