#pragma once

#include <vector>
#include <string>

enum OPER_ID
{
	NOW_GEN = 0,
	PRE_GEN,
};

struct SequenceInfo
{
	unsigned int left;
	unsigned int middle;
	unsigned int right;
	unsigned int oper;

	SequenceInfo(unsigned int left, unsigned int middle, unsigned int right, unsigned int oper = OPER_ID::NOW_GEN)
	{
		this->left = left;
		this->middle = middle;
		this->right = right;
		this->oper = oper;
	}
};


class MapSequences
{
public:
	MapSequences(const char * fileName);
	MapSequences();
	~MapSequences();

	SequenceInfo pumpSequence();

	int getTotalSize();

	void rewind();

	bool isEnd()
	{
		return _iCurIndex >= _vSequences.size();
	}

protected:
	void addSequences(unsigned int l, unsigned int m, unsigned int r, unsigned int oper = OPER_ID::NOW_GEN);

private:
	unsigned int _iCurIndex;
	std::vector<SequenceInfo> _vSequences;
};
