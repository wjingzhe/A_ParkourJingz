#include "MapSequences.h"
#include <cassert>
#include "cocos2d\external\tinyxml2\tinyxml2.h"

using namespace std;
using namespace tinyxml2;

MapSequences::MapSequences() :_iCurIndex(0)
{
	addSequences(0, 0, 2);
	addSequences(0, 0, 2);
	addSequences(0, 0, 2);
	addSequences(0, 0, 2);
	addSequences(0, 0, 2);
	addSequences(0, 0, 2);
	addSequences(0, 0, 2);
	addSequences(0, 2, 0);
	addSequences(0, 2, 0);
	addSequences(0, 2, 0);
	addSequences(0, 2, 0);
	addSequences(0, 2, 0);
	addSequences(0, 2, 0);
	addSequences(0, 2, 0);
	addSequences(0, 2, 0);
	addSequences(0, 2, 0);
	addSequences(0, 0, 1);
	addSequences(0, 1, 0);
	addSequences(1, 0, 0);
	addSequences(1, 1, 0);
	addSequences(0, 1, 0);
	addSequences(1, 0, 0);
	addSequences(1, 1, 0);
	addSequences(0, 0, 1);
	addSequences(0, 1, 0);
	addSequences(1, 1, 0);
	addSequences(1, 1, 0);
	addSequences(0, 1, 1);
	addSequences(0, 1, 1);
	addSequences(0, 1, 1);
	addSequences(0, 1, 1);
	addSequences(0, 1, 1);
	addSequences(0, 1, 1);
	addSequences(0, 0, 1);
	addSequences(0, 1, 0);
	addSequences(1, 1, 0);
	addSequences(1, 1, 0);
	addSequences(0, 1, 1);
	addSequences(0, 1, 1);
	addSequences(0, 1, 1);
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

void MapSequences::addSequences(unsigned short l, unsigned short m, unsigned short r)
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