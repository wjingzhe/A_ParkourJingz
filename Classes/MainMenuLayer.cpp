#include "MainMenuLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/UIButton.h"

#include "RegitsteredEvents.h"

//todo
#include "MainScene.h"
#include "GameLayer.h"

USING_NS_CC;


long MainMenuLayer::s_iCurrentGold = 0;

MainMenuLayer::MainMenuLayer() :_pRestartButton(nullptr), _pGoldText(nullptr), _pPauseButton(nullptr)
{
}

MainMenuLayer::~MainMenuLayer()
{
	CC_SAFE_RELEASE_NULL(_pRestartButton);
	CC_SAFE_RELEASE_NULL(_pGoldText);
	CC_SAFE_RELEASE_NULL(_pPauseButton);
}

bool MainMenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	CC_SAFE_RELEASE_NULL(_pPauseButton);
	CC_SAFE_RELEASE_NULL(_pRestartButton);
	CC_SAFE_RELEASE_NULL(_pGoldText);

	_pPauseButton = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("HUD/HUD.json");
	_pGoldText = dynamic_cast<ui::TextAtlas *>(_pPauseButton->getChildByName("gold"));
	_pGoldText->setString("0");
	this->addChild(_pPauseButton, 100);
	CC_SAFE_RETAIN(_pPauseButton);
	CC_SAFE_RETAIN(_pGoldText);

	auto pauseButton = dynamic_cast<cocos2d::ui::Button *>(_pPauseButton->getChildByName("Button_1"));
	pauseButton->addTouchEventListener(
		[&](Ref * sender,cocos2d::ui::Widget::TouchEventType type)
		{
			static bool bIsPaused = false;
			if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
			{
				if (bIsPaused)
				{
					bIsPaused = false;
					Director::getInstance()->resume();
				}
				else
				{
					Director::getInstance()->pause();
					bIsPaused = true;
				}
			}//if_type
			
		}//lambdy
	);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainMenuLayer::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 100);


	auto label = Label::createWithTTF("Game Parkour", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	this->addChild(label,100);

	//this->scheduleUpdate();

	auto pGoldChanged = EventListenerCustom::create(RegitsteredEvents::GOLD_CHANGED, CC_CALLBACK_1(MainMenuLayer::ChangeGold, this));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pGoldChanged, this);

	auto pRestart = EventListenerCustom::create(RegitsteredEvents::SHOW_RESTART, CC_CALLBACK_1(MainMenuLayer::showRestart, this));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pRestart, this);

	_pRestartButton = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("Menu/Menu.json");
	this->addChild(_pRestartButton, 10);
	auto restart_btn = dynamic_cast<cocos2d::ui::Button *>(_pRestartButton->getChildByName("restart"));
	restart_btn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
			static_cast<GameLayer *>(Director::getInstance()->getRunningScene()->getChildByName("Game_Main"))->stopGame();
			Director::getInstance()->replaceScene(MainScene::create());
		}
	});

	_pRestartButton->setVisible(false);

	CC_SAFE_RETAIN(_pRestartButton);
	

	return true;
}

void MainMenuLayer::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MainMenuLayer::update(float delta)
{

}

void MainMenuLayer::showRestart(cocos2d::EventCustom * pEvent)
{
	static_cast<GameLayer *>(Director::getInstance()->getRunningScene()->getChildByName("Game_Main"))->stopGame();
	//Director::getInstance()->getRunningScene()->stopAllActions();
	//cocos2d::Director::getInstance()->stopAnimation();
	s_iCurrentGold = 0;
	_pPauseButton->setVisible(false);
	_pRestartButton->setVisible(true);
	
}