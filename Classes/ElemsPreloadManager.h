#pragma once


class ElemsPreloadManager
{
	ElemsPreloadManager();
public:
	
	~ElemsPreloadManager();

	static void registerMoveAbleElemTypes(void);

	static void forceCreateMoveAbleElems(void);

private:
	static bool s_bRegisterd;
};
