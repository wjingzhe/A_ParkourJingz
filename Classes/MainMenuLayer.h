#pragma once
#include "cocos2d.h"
#include "ui/UITextAtlas.h"
#include "ui/UIButton.h"
#include "ui/UIImageView.h"
#include <string>

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

	void ChangeGold(cocos2d::EventCustom * pEvent);

	void showRestart(cocos2d::EventCustom * pEvent);

private:
	cocos2d::ui::TextAtlas * _pGoldText;
	cocos2d::ui::Widget* _pRestartButton;
	cocos2d::ui::Widget* _pPauseAndGold;
	cocos2d::ui::Button * _pPauseButton;
	cocos2d::ui::ImageView * _pGoldImage;
	static long s_iCurrentGold;
};

