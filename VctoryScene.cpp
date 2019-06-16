#include "VctoryScene.h"
#include "GameMap.h"
USING_NS_CC;
Scene* VctoryScene::createScene()
{
	return VctoryScene::create();
}
bool VctoryScene::init()
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

	auto ending = Sprite::create("victory.png");
	ending->setScale(0.6);
	ending->setPosition(visibleSize.width * 0.5, visibleSize.height * 0.5 + 30);
	this->addChild(ending, 0);
	//再来一次
	auto AgainItem = MenuItemImage::create(
		"Again.png",
		"again.png",
		CC_CALLBACK_1(VctoryScene::again, this));
	AgainItem->setScale(0.4);
	AgainItem->setPosition(visibleSize.width * 0.5 - 100, visibleSize.height * 0.5 - 100);
	Menu * ma = Menu::create(AgainItem, NULL);
	ma->setPosition(0, 0);
	this->addChild(ma);
	//结束游戏
	auto ExitItem = MenuItemImage::create(
		"Exit.png",
		"Exit.png",
		CC_CALLBACK_1(VctoryScene::end, this));
	ExitItem->setScale(0.4);
	ExitItem->setPosition(visibleSize.width * 0.5 + 100, visibleSize.height * 0.5 - 100);
	Menu * mu = Menu::create(ExitItem, NULL);
	mu->setPosition(0, 0);
	this->addChild(mu);
	return true;
}
void VctoryScene::again(Ref * pSender)
{
	auto hs = GameMap::createScene();
	Director::getInstance()->replaceScene(hs);
}
void VctoryScene::end(Ref * pSender)
{
	Director::getInstance()->end();
}