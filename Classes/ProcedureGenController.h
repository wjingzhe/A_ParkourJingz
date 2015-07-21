#pragma once

#include <vector>
#include "cocos2d.h"

class MapSequences;
struct SequenceInfo;
class Player;

class ProcedureGenController
{
public:
	ProcedureGenController();
	~ProcedureGenController();

	void randomGenElement(Player * pPlayer, cocos2d::Node * pRenderNode, float dt);
	void generateObstacle(Player * pPlayer, cocos2d::Node * pRenderNode, float dt);


	void insertMapSequence(MapSequences * map_sequence)
	{
		_vSequencesPtr.push_back(map_sequence);
	}


protected:
	void run(float dt);
	SequenceInfo pumpSequence();


private:
	MapSequences * _pCurSequences;
	std::vector<MapSequences *> _vSequencesPtr;
};
