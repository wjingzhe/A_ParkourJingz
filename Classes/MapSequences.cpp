#include "MapSequences.h"
#include <cassert>
#include "cocos2d\external\tinyxml2\tinyxml2.h"
#include "MoveAbleElemTypeDefines.h"

using namespace std;
using namespace tinyxml2;

MapSequences::MapSequences() :_iCurIndex(0)
{
	addSequences(0, 0, COIN_TYPE_ID);
	addSequences(0, 0, COIN_TYPE_ID);
	addSequences(0, 0, COIN_TYPE_ID);
	addSequences(0, 0, COIN_TYPE_ID);
	addSequences(0, 0, COIN_TYPE_ID);
	addSequences(0, 0, COIN_TYPE_ID);
	addSequences(0, 0, COIN_TYPE_ID);
	addSequences(0, COIN_TYPE_ID, 0);
	addSequences(0, COIN_TYPE_ID, 0);
	addSequences(0, COIN_TYPE_ID, 0);
	addSequences(0, COIN_TYPE_ID, 0);
	addSequences(0, COIN_TYPE_ID, 0);
	addSequences(0, COIN_TYPE_ID, 0);
	addSequences(0, COIN_TYPE_ID, 0);
	addSequences(0, COIN_TYPE_ID, 0);
	addSequences(0, COIN_TYPE_ID, 0);
	addSequences(0, 0, 0);
	addSequences(0, 0, 0);
	addSequences(0, 0, 0);
	addSequences(0, 0, 0);
	addSequences(0, 0, 0);
	addSequences(0, 0, 0);
	addSequences(0, 0, OBSTACLE__ID);
	addSequences(0, COIN_TYPE_ID, 0);
	addSequences(0, COIN_TYPE_ID, 0);
	addSequences(0, COIN_TYPE_ID, 0);
	addSequences(0, OBSTACLE__ID, 0);
	addSequences(0, COIN_TYPE_ID, 0);
	addSequences(0, COIN_TYPE_ID, 0);
	addSequences(0, COIN_TYPE_ID, 0);
	addSequences(OBSTACLE__ID, 0, 0);
	addSequences(0, COIN_TYPE_ID, 0);
	addSequences(0, COIN_TYPE_ID, 0);
	addSequences(0, COIN_TYPE_ID, 0);
	addSequences(OBSTACLE__ID, OBSTACLE__ID, 0);
	addSequences(0, 0, 0);
	addSequences(0, 0, 0);
	addSequences(0, OBSTACLE__ID, 0);
	addSequences(0, 0, 0);
	addSequences(0, 0, 0);
	addSequences(OBSTACLE__ID, 0, 0);
	addSequences(OBSTACLE__ID, OBSTACLE__ID, 0);
	addSequences(0, COIN_TYPE_ID, 0);
	addSequences(0, COIN_TYPE_ID, 0);
	addSequences(0, 0, OBSTACLE__ID);
	addSequences(0, OBSTACLE__ID, 0);
	addSequences(0, COIN_TYPE_ID, 0);
	addSequences(0, COIN_TYPE_ID, 0);
	addSequences(OBSTACLE__ID, OBSTACLE__ID, 0);
	addSequences(OBSTACLE__ID, OBSTACLE__ID, 0);
	addSequences(0, 0, 0);
	addSequences(0, 0, 0);
	addSequences(0, OBSTACLE__ID, OBSTACLE__ID);
	addSequences(0, OBSTACLE__ID, OBSTACLE__ID);
	addSequences(0, OBSTACLE__ID, OBSTACLE__ID);
	addSequences(0, OBSTACLE__ID, OBSTACLE__ID);
	addSequences(0, OBSTACLE__ID, OBSTACLE__ID);
	addSequences(0, OBSTACLE__ID, OBSTACLE__ID);
	addSequences(0, 0, OBSTACLE__ID);
	addSequences(0, 0, 0);
	addSequences(0, OBSTACLE__ID, 0);
	addSequences(OBSTACLE__ID, OBSTACLE__ID, 0);
	addSequences(OBSTACLE__ID, OBSTACLE__ID, 0);
	addSequences(0, 0, 0);
	addSequences(0, 0, 0);
	addSequences(0, OBSTACLE__ID, OBSTACLE__ID);
	addSequences(0, OBSTACLE__ID, OBSTACLE__ID);
	addSequences(0, OBSTACLE__ID, OBSTACLE__ID);
	addSequences(0, 0, 0);
	addSequences(0, 0, 0);
	addSequences(0, 0, 0);
	addSequences(0, 0, 0);
	addSequences(0, 0, 0);
}

MapSequences::MapSequences(const char * fileName) :_iCurIndex(0)
{
	XMLDocument doc;
	doc.LoadFile(fileName);
	auto rootNode = doc.RootElement();
	auto sequence = rootNode->FirstChildElement("SEQ");

	while (sequence)
	{
		auto left = sequence->FirstChildElement("Left");
		auto middle = sequence->FirstChildElement("Middle");
		auto right = sequence->FirstChildElement("Right");

		addSequences(atoi(left->GetText()), atoi(middle->GetText()), atoi(right->GetText()));
		sequence = sequence->NextSiblingElement();
	}
}

MapSequences::~MapSequences()
{
}

void MapSequences::addSequences(unsigned int l, unsigned int m, unsigned int r)
{
	_vSequences.push_back(std::move(SequenceInfo(l, m, r)));
}

SequenceInfo MapSequences::pumpSequence()
{
	if (_iCurIndex < _vSequences.size())
	{
		auto seq = _vSequences[_iCurIndex];
		++_iCurIndex;
		return seq;
	}
	else
	{
		rewind();
		return pumpSequence();
	}
}

int MapSequences::getTotalSize()
{
	return _vSequences.size();
}

void MapSequences::rewind()
{
	_iCurIndex = 0;
}