#pragma once

#include <vector>

struct SequenceInfo
{
	unsigned int left;
	unsigned int middle;
	unsigned int right;

	SequenceInfo(unsigned int left, unsigned int middle, unsigned int right)
	{
		this->left = left;
		this->middle = middle;
		this->right = right;
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
	void addSequences(unsigned int l, unsigned int m, unsigned int r);

private:
	unsigned int _iCurIndex;
	std::vector<SequenceInfo> _vSequences;
};
