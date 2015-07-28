#include "MainMenuLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/UIButton.h"

USING_NS_CC;


int MainMenuLayer::s_iCurrentGold = 0;

MainMenuLayer::MainMenuLayer()
{
}

MainMenuLayer::~MainMenuLayer()
{
}

bool MainMenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto widget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("HUD/HUD.json");
	pGoldText = (ui::TextAtlas *)widget->getChildByName("gold");
	pGoldText->setString("0");
	this->addChild(widget,100);

	auto pauseButton = static_cast<cocos2d::ui::Button *>(widget->getChildByName("Button_1"));
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