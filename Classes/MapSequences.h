#pragma once

#include <vector>

struct SequenceInfo
{
	unsigned short left;
	unsigned short middle;
	unsigned short right;

	SequenceInfo(unsigned short left, unsigned short middle, unsigned short right)
	{
		this->left = left;
		this->middle = middle;
		this->right = right;
	}
};


#define EMPTY 0
#define MONSTER 1
#define COIN 2

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
	void addSequences(unsigned short l, unsigned short m, unsigned short r);

private:
	unsigned int _iCurIndex;
	std::vector<SequenceInfo> _vSequences;
};
