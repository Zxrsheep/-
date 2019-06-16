/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "HelpScene.h"
#include "GameMap.h"
#include "chooseweapon.h"
#define MUSIC_BACK_FILE_  "backmusic.mp3"
using namespace CocosDenshion;
USING_NS_CC;


Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(MUSIC_BACK_FILE_);
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSIC_BACK_FILE_, true);
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.7);
	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("hello000", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}


	auto settingpir = MenuItemImage::create("setting.png", "setting.png", CC_CALLBACK_1(HelloWorld::Helpscene, this));
	auto setting = Menu::create(settingpir, NULL);
	setting->setPosition(visibleSize.width * 0.8, visibleSize.height * 0.2);
	this->addChild(setting, 2);


	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("2016042660043257.jpg");
	if (sprite == nullptr)
	{
		problemLoading("'2016042660043257.jpg'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width *0.6 + origin.x, visibleSize.height / 2 + origin.y));
		sprite->setScale(0.8);
		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	}


		auto begingame = Label::create("Begin Game", "fonts/Marker Felt.ttf", 24);
		auto beginlabel = MenuItemLabel::create(begingame, CC_CALLBACK_1(HelloWorld::Gamemap, this));
		auto beginGame = Menu::create(beginlabel, NULL);
		begingame->setColor(ccc3(220, 20, 60));
		beginGame->setPosition(visibleSize.width * 0.5, visibleSize.height * 0.5);
		this->addChild(beginGame, 3);



	return true;
}

void HelloWorld::Helpscene(Ref * pSender)
{
	auto hs = HelpScene::createScene();
	Director::getInstance()->pushScene(hs);
}

void HelloWorld::Gamemap(Ref* pSender)
{
	auto gs = ChooseWeapon::createScene();
	Director::getInstance()->pushScene(gs);
}
void HelloWorld::menuCloseCallback(Ref * pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}