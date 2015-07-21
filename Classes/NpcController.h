#pragma once

#include <vector>
#include "cocos2d.h"

class MapSequences;
struct SequenceInfo;
class Player;
class MoveableElems;

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
	//todo
	float calcuratePosWillHit();

private:
	MapSequences * _pCurMapSequences;
	std::vector<MapSequences *> _vSequencesPtr;

	cocos2d::Vector<MoveableElems *> vpMoveableElems;

	Player * _pPlayer;
	cocos2d::Layer * _pGameLayer;
};
