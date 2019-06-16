#include "EndScene.h"
#include "GameMap.h"
USING_NS_CC;
Scene* EndScene::createScene()
{
	return EndScene::create();
}
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
bool EndScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	tilemap = TMXTiledMap::create("arrowmap2.tmx");
	tilemap->setAnchorPoint(Vec2::ZERO);
	tilemap->setPosition(Vec2::ZERO);
	this->addChild(tilemap, -1);

	auto ending = Sprite::create("End.png");
	ending->setScale(1.23);
	ending->setPosition(visibleSize.width * 0.5, visibleSize.height * 0.5 + 30);
	this->addChild(ending, 0);
	//再来一次
	auto AgainItem = MenuItemImage::create(
		"Again.png",
		"again.png",
		CC_CALLBACK_1(EndScene::again, this));
	AgainItem->setScale(0.4);
	AgainItem->setPosition(visibleSize.width * 0.5 - 100, visibleSize.height * 0.5 - 100);
	Menu * ma = Menu::create(AgainItem, NULL);
	ma->setPosition(0, 0);
	this->addChild(ma);
	//结束游戏
	auto ExitItem = MenuItemImage::create(
		"Exit.png",
		"Exit.png",
		CC_CALLBACK_1(EndScene::end, this));
	ExitItem->setScale(0.4);
	ExitItem->setPosition(visibleSize.width * 0.5 + 100, visibleSize.height * 0.5 - 100);
	Menu * mu = Menu::create(ExitItem, NULL);
	mu->setPosition(0, 0);
	this->addChild(mu);
	return true;
}
/*
void EndScene::menuAgainCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}*/
void EndScene::again(Ref * pSender)
{
	auto hs = GameMap::createScene();
	Director::getInstance()->replaceScene(hs);
}
void EndScene::end(Ref * pSender)
{
	Director::getInstance()->end();
}