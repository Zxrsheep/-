#include"HelpScene.h"

USING_NS_CC;
Scene* HelpScene::createScene()
{
	auto scene = Scene::create();

	auto layer = HelpScene::create();

	scene->addChild(layer);

	return scene;
}
bool HelpScene::init()
{
	if (!Layer::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto explain = Sprite::create("explain.png");
	explain->setPosition(visibleSize.height * 0.5, visibleSize.height * 0.5);
	this->addChild(explain);


	auto stopmusic = Label::create("pause backgroundmusic", "fonts/Marker Felt.ttf", 24);
	auto stopmusicmenu = MenuItemLabel::create(stopmusic, CC_CALLBACK_1(HelpScene::menuMusicstopCallback, this));
	stopmusicmenu->setPosition(visibleSize.width * 0.4, visibleSize.height * 0.9);
	auto resumemusic = Label::create("resume backgroundmusic", "fonts/Marker Felt.ttf", 24);
	auto resumemusicmenu = MenuItemLabel::create(resumemusic, CC_CALLBACK_1(HelpScene::menuMusicresumeCallback, this));
	resumemusicmenu->setPosition(visibleSize.width * 0.4, visibleSize.height * 0.8);

	auto okMenuItem = MenuItemImage::create(
		"ok1.png",
		"ok2.png",
		CC_CALLBACK_1(HelpScene::menuOkCallback, this));

	okMenuItem->setPosition(visibleSize.width * 0.8, visibleSize.height * 0);

	Menu* mn = Menu::create(okMenuItem, stopmusicmenu, resumemusicmenu, NULL);
	mn->setPosition(0, 0);
	this->addChild(mn);

	return true;


}

void HelpScene::menuOkCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}
void HelpScene::menuMusicstopCallback(Ref* pSender)
{
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}
void HelpScene::menuMusicresumeCallback(Ref* pSender)
{
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}