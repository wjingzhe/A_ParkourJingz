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
	cocos2d::Vec3 && calcuratePosWillHit(MoveAbleElem * pElemSrc, Player * pElemTar, float fDtToHit,const cocos2d::Vec3 & vOffset = cocos2d::Vec3(0.0f,0.f,0.f));

private:
	MapSequences * _pCurMapSequences;
	std::vector<MapSequences *> _vSequencesPtr;

	std::vector<MoveAbleElem *> vpMoveableElems;

	Player * _pPlayer;
	cocos2d::Layer * _pGameLayer;

	float _fRecationDt;
};
