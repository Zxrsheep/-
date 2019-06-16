#include"chooseweapon.h"
#include "GameMap.h"
USING_NS_CC;
//extern int weapon;


int ChooseWeapon::weapon = 0;
Scene* ChooseWeapon::createScene()
{
	auto scene = Scene::create();

	auto layer = ChooseWeapon::create();

	scene->addChild(layer);

	return scene;
}
bool ChooseWeapon::init()
{
	if (!Layer::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize(); //arrow.png

	auto selection = Sprite::create("selectback.jpg");
	selection->setPosition(visibleSize.width * 0.5, visibleSize.height * 0.5);
	selection->setScale(0.6);
	this->addChild(selection);

	auto backMenu = Label::create("Back Menu", "fonts/Marker Felt.ttf", 15);
	auto okMenuItem = MenuItemLabel::create(backMenu, CC_CALLBACK_1(ChooseWeapon::backmainmenu, this));
	okMenuItem->setPosition(visibleSize.width * 0.9, visibleSize.height * 0.1);

	Menu* backitem = Menu::create(okMenuItem, NULL);
	backitem->setPosition(0, 0);
	this->addChild(backitem);

	auto Weapon_1 = MenuItemImage::create(
		"arrow_1.png",
		"arrow_1.png",
		CC_CALLBACK_1(ChooseWeapon::Weapon_1, this));
	Weapon_1->setPosition(-50, -10);

	auto Weapon_2 = MenuItemImage::create(
		"Hammer.png",
		"Hammer.png",
		CC_CALLBACK_1(ChooseWeapon::Weapon_2, this));
	Weapon_2->setPosition(50, -10);
	CCLOG("1");
	Menu * mn = Menu::create(Weapon_1, Weapon_2, NULL);
	this->addChild(mn, 3);

	return true;


}

void ChooseWeapon::Weapon_1(Ref * pSender)
{	
	ChooseWeapon::weapon = 1;
	auto w1 = GameMap::createScene();
	Director::getInstance()->pushScene(w1);
}
void ChooseWeapon::Weapon_2(Ref * pSender)
{
	ChooseWeapon::weapon = 2;
	auto w2 = GameMap::createScene();

	Director::getInstance()->pushScene(w2);
	CCLOG("2222");
}

void ChooseWeapon::backmainmenu(Ref* pSender)
{
	Director::getInstance()->popScene();
}