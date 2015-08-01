#include "MainMenuLayer.h"
#include "cocostudio/CocoStudio.h"

#include "RegitsteredEvents.h"

//todo
#include "MainScene.h"
#include "GameLayer.h"

USING_NS_CC;


long MainMenuLayer::s_iCurrentGold = 0;

MainMenuLayer::MainMenuLayer() :_pRestartButton(nullptr), _pGoldText(nullptr), _pPauseAndGold(nullptr), _pGoldImage(nullptr), _pPauseButton(nullptr), _pGoldChanged(nullptr)
{
}

MainMenuLayer::~MainMenuLayer()
{
	CC_SAFE_RELEASE_NULL(_pRestartButton);
	CC_SAFE_RELEASE_NULL(_pGoldText);
	CC_SAFE_RELEASE_NULL(_pPauseAndGold);
	CC_SAFE_RELEASE_NULL(_pGoldImage);
	CC_SAFE_RELEASE_NULL(_pPauseButton);
	if (_pGoldChanged != nullptr)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(_pGoldChanged);
		CC_SAFE_RELEASE_NULL(_pGoldChanged);
	}
}

bool MainMenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	CC_SAFE_RELEASE_NULL(_pPauseAndGold);
	CC_SAFE_RELEASE_NULL(_pRestartButton);
	CC_SAFE_RELEASE_NULL(_pGoldText);
	CC_SAFE_RELEASE_NULL(_pGoldImage);
	CC_SAFE_RELEASE_NULL(_pPauseButton);

	_pPauseAndGold = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("HUD/HUD.json");
	this->addChild(_pPauseAndGold, 100);
	CC_SAFE_RETAIN(_pPauseAndGold);

	_pGoldText = dynamic_cast<ui::TextAtlas *>(_pPauseAndGold->getChildByName("gold"));
	CC_SAFE_RETAIN(_pGoldText);
	_pGoldText->setString("0");
	_pGoldText->setPosition(Vec2(origin.x + visibleSize.width - _pGoldText->getContentSize().width,
		origin.y + visibleSize.height - _pGoldText->getContentSize().height));

	_pGoldImage = dynamic_cast<ui::ImageView *>(_pPauseAndGold->getChildByName("Image_3"));
	_pGoldImage->setPosition(Vec2(_pGoldText->getPositionX() - _pGoldImage->getContentSize().width,
		_pGoldText->getPositionY()));
	CC_SAFE_RETAIN(_pGoldImage);
	
	_pPauseButton = dynamic_cast<cocos2d::ui::Button *>(_pPauseAndGold->getChildByName("Button_1"));
	CC_SAFE_RETAIN(_pPauseButton);
	_pPauseButton->addTouchEventListener(
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

	_pPauseButton->setPosition(Vec2(origin.x + _pPauseButton->getContentSize().width / 2,
		origin.y + visibleSize.height - _pPauseButton->getContentSize().height / 2));
	_pPauseButton->setVisible(true);

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

	_pGoldChanged = EventListenerCustom::create(RegitsteredEvents::GOLD_CHANGED, CC_CALLBACK_1(MainMenuLayer::ChangeGold, this));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_pGoldChanged, this);
	CC_SAFE_RETAIN(_pGoldChanged);

	_pRestartButton = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("Menu/Menu.json");
	this->addChild(_pRestartButton, 10);
	auto restart_btn = dynamic_cast<cocos2d::ui::Button *>(_pRestartButton->getChildByName("restart"));
	restart_btn->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(RegitsteredEvents::GAME_RESTART);
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

void MainMenuLayer::showRestart()
{
	if (_pGoldChanged != nullptr)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(_pGoldChanged);
		CC_SAFE_RELEASE_NULL(_pGoldChanged);
	}
	s_iCurrentGold = 0;
	_pPauseButton->setVisible(false);
	_pRestartButton->setVisible(true);
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(RegitsteredEvents::GAME_OVER);
}

void MainMenuLayer::ChangeGold(cocos2d::EventCustom * pEvent)
{
	int * pIncreament = static_cast<int *>(pEvent->getUserData());
	s_iCurrentGold += *pIncreament;
	_pGoldText->setString(cocos2d::StringUtils::format("%ld", s_iCurrentGold));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_pGoldText->setPosition(Vec2(origin.x + visibleSize.width - _pGoldText->getContentSize().width,
		_pGoldText->getPositionY()));

	_pGoldImage->setPosition(Vec2(_pGoldText->getPositionX() - _pGoldImage->getContentSize().width,
		_pGoldText->getPositionY()));

	delete pIncreament;
}