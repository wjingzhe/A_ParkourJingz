#pragma once


class ElemsPreloadManager
{
	ElemsPreloadManager();
public:
	
	~ElemsPreloadManager();

	static void registerMoveAbleElemTypes(void);

	static void preCreateMoveAbleElems(void);

private:
	static bool s_bRegisterd;
};
