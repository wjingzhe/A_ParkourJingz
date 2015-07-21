#pragma once
#include "cocos2d.h"
#include "ui/UITextAtlas.h"


class MainMenuLayer:public cocos2d::Layer
{
	MainMenuLayer();
public:
	~MainMenuLayer();

	bool init();

	CREATE_FUNC(MainMenuLayer);

	CC_DISALLOW_COPY_AND_ASSIGN(MainMenuLayer);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	int getCurGold(void)
	{
		return s_iCurrentGold;
	}

	void update(float delta) override;

protected:

	void ChangeGold(signed int increament)
	{
		s_iCurrentGold += increament;
		char str[20];
		sprintf_s(str, "%d", s_iCurrentGold);
		pGoldText->setString(str);
	}

private:
	cocos2d::ui::TextAtlas * pGoldText;
	static int s_iCurrentGold;
};

