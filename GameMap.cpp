#include "GameMap.h"
#include "time.h"
#include "stdlib.h"
#include "SpriteBase.h"
#include "EndScene.h"

USING_NS_CC;

//extern int weapon;

//int	GameMap::weapon = 0;

Scene* GameMap::createScene()
{
	return GameMap::create();
}
bool GameMap::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	/*auto arrowmap = Sprite::create("map.png");
	arrowmap->setScale(1.23);
	arrowmap->setPosition(visibleSize.width * 0.5, visibleSize.height * 0.5);
	this->addChild(arrowmap,0);*/

	tilemap = TMXTiledMap::create("arrowmap2.tmx");
	tilemap->setAnchorPoint(Vec2::ZERO);
	tilemap->setPosition(Vec2::ZERO);
	this->addChild(tilemap, -1);

	collidable = tilemap->getLayer("collidable");

	arrowman = SpriteBase::create("arrowman15.png");
	arrowman->setScale(0.2);
	arrowman->setPosition(visibleSize.width * 0.3, visibleSize.height * 0.2);
	tilemap->addChild(arrowman, 1);

	///////血条
	HP = Sprite::create("background.png");
	HP->setScale(4);
	HP->setPosition(Point(arrowman->getPosition().x - 70, arrowman->getPosition().y * 3.5));
	arrowman->addChild(HP);;//血条底层
	Loadingbarman = LoadingBar::create("foreground.png");   //创建进度框
	Loadingbarman->setPosition(Point(arrowman->getPosition().x - 70, arrowman->getPosition().y * 3.5)); //设置框的位置1
	Loadingbarman->setPercent(manpercent);
	Loadingbarman->setScale(4);
	Loadingbarman->setDirection(LoadingBar::Direction::LEFT);
	arrowman->addChild(Loadingbarman);            //加到默认图层里面去
	///////经验条
	EXP = Sprite::create("energyback.png");
	EXP->setScale(0.7);
	EXP->setPosition(visibleSize.width * 0.5, visibleSize.height * 0.95);
	tilemap->addChild(EXP, 4);//经验底层
	LoadingbarEXP = LoadingBar::create("energyfore.png");   //创建进度框
	LoadingbarEXP->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.95)); //设置框的位置1
	LoadingbarEXP->setPercent(exppercent);
	LoadingbarEXP->setScale(0.7);
	LoadingbarEXP->setDirection(LoadingBar::Direction::LEFT);
	this->addChild(LoadingbarEXP);            //加到默认图层里面去

	/*monster = Sprite::create("player4.png");
	monster->setPosition(visibleSize.width * 0.3, visibleSize.height * 0.5);
	monster->setScale(0.6);
	tilemap->addChild(monster, 2);*/

	//	rangex = visibleSize.width / tilemap->getMapSize().width;
	//	rangey = visibleSize.height / tilemap->getMapSize().height;

	auto backMenu = Label::create("Return to Select", "fonts/Marker Felt.ttf", 15);
	backMenu->setColor(ccc3(0, 0, 128));
	auto okMenuItem = MenuItemLabel::create(backMenu, CC_CALLBACK_1(GameMap::backmenu, this));
	okMenuItem->setPosition(visibleSize.width * 0.9, visibleSize.height * 0.1);

	Menu * mn = Menu::create(okMenuItem, NULL);
	mn->setPosition(0, 0);
	this->addChild(mn);

	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event * event) {
		keys[keyCode] = true;
	};
	listenerkeyPad->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event * event) {
		keys[keyCode] = false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);
	this->schedule(schedule_selector(GameMap::keyupdate));

	this->schedule(schedule_selector(GameMap::slowupdate) ,1);

	this->schedule(schedule_selector(GameMap::quickupdate));



	//攻击
	if (num > 0) {
	auto attackListener = EventListenerTouchOneByOne::create();
	attackListener->onTouchBegan = [](Touch * touch, Event * event) {
		return true;
	};
	attackListener->onTouchEnded = [=](Touch * touch, Event * event) {
		Vec2 touchLocation = touch->getLocation();
		Vec2 nodeLocation = this->convertToNodeSpace(touchLocation);
		float k = ((float)nodeLocation.x - (float)monster->getPosition().x) /((float)nodeLocation.y - (float)monster->getPosition().y) ;
		attposx = nodeLocation.x;
		attposy = nodeLocation.y;
		shootaction();
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(attackListener, this);
	}

	//this->scheduleUpdate();
		
	return true;

}
Vec2 GameMap::tileCoordForPosition(Vec2 position) {
	int x = (int)(position.x / (tilemap->getTileSize().width)/CC_CONTENT_SCALE_FACTOR());
	float pointHeight = tilemap->getTileSize().height / CC_CONTENT_SCALE_FACTOR();
	int y = (int)((tilemap->getMapSize().height * pointHeight - position.y) / pointHeight);
	return Vec2(x, y);
}

bool GameMap::keyState(EventKeyboard::KeyCode key) {
	if (keys[key]) {
		return true;
	}
	else {
		return false;
	}
}
//箭的角度
float GameMap::angle(cocos2d::Vec2 beginpos, cocos2d::Vec2 endpos) {
	Vec2 dis = endpos - beginpos;
	float angle = Vec2(dis.y, dis.x).getAngle() / 3.14f * 180;
	return angle;
}
//攻击范围；计算点坐标
cocos2d::Vec2 GameMap::attackpos(cocos2d::Vec2 beginpos, cocos2d::Vec2 endpos, float range) {
	Vec2 pos;
	float distance = (float)sqrt(pow(endpos.x - beginpos.x, 2) + pow(endpos.y - beginpos.y, 2));
	pos.x = (range * endpos.x - range * beginpos.x + distance * beginpos.x) / distance;
	pos.y = (range * endpos.y - range * beginpos.y + distance * beginpos.y) / distance;
	return pos;
}


void GameMap::animationcreate(int direct)
{
	if (animating)
		return;
	animating = 1;
	
	Animation* animation = Animation::create();
	if (direct >= 5) {
		int dir = direct * 6;
		char nameSize[100] = { 0 };
		sprintf(nameSize, "arrowman%d.png", dir);
		animation->addSpriteFrameWithFile("arrowman%d.png");

	animation->setDelayPerUnit(0.15f);
	}
	if (direct <= 4) {
        for (int i = 1 + direct * 7; i <= 7 + direct * 7; i++)
	    {
		     char nameSize[100] = { 0 };
		     sprintf(nameSize, "arrowman%d.png", i);
		     animation->addSpriteFrameWithFile(nameSize);
	    }

        animation->setDelayPerUnit(0.15f);

	}
	

	

	/* 将动画包装成一个动作 */
	Animate* action = Animate::create(animation);

	auto callbackFunc = [&]()
	{
		animating = 0;
	};
	CallFunc* callFunc = CallFunc::create(callbackFunc);

	Action* actions = Sequence::create(action, callFunc, NULL);

	arrowman->runAction(actions);
}

void GameMap::monsteranimationcreate(int direct)
{
	if (animating)
		return;
	animating = 1;

	Animation* animation = Animation::create();
	if (direct == 1) {
		for (int i =8 ; i < 10 ; i++)
		{
			char nameSize[100] = { 0 };
			sprintf(nameSize, "player4_%d.png", i);
			animation->addSpriteFrameWithFile(nameSize);
		}

		animation->setDelayPerUnit(0.15f);
	}
	else if (direct == -1) {
		for (int i = 11; i < 13; i++)
		{
			char nameSize[100] = { 0 };
			sprintf(nameSize, "player4_%d.png", i);
			animation->addSpriteFrameWithFile(nameSize);
		}

		animation->setDelayPerUnit(0.15f);
	}


	/* 将动画包装成一个动作*/
	Animate* action = Animate::create(animation);

	auto callbackFunc = [&]()
	{
		animating = 0;
	};
	CallFunc* callFunc = CallFunc::create(callbackFunc);

	Action* actions = Sequence::create(action, callFunc, NULL);

	monster->runAction(actions);
}
 


void GameMap::keyupdate(float delta) {
	/* / CC_CONTENT_SCALE_FACTOR() / CC_CONTENT_SCALE_FACTOR()*/
	// Register an update function that checks to see if the CTRL key is pressed
	// and if it is displays how long, otherwise tell the user to press it
	Node::update(delta);
	auto KEY_W = cocos2d::EventKeyboard::KeyCode::KEY_W, KEY_A = cocos2d::EventKeyboard::KeyCode::KEY_A,
		KEY_S = cocos2d::EventKeyboard::KeyCode::KEY_S, KEY_D = cocos2d::EventKeyboard::KeyCode::KEY_D;
	if (keyState(KEY_W) && !keyState(KEY_A) && !keyState(KEY_S) && !keyState(KEY_D)) {
        move(KEY_W);
		animationcreate(3);
	}
	else if (!keyState(KEY_W) && keyState(KEY_A) && !keyState(KEY_S) && !keyState(KEY_D)) {
		move(KEY_A);
		animationcreate(0);
	}
	else if (!keyState(KEY_W) && !keyState(KEY_A) && keyState(KEY_S) && !keyState(KEY_D)) {
		move(KEY_S);
		animationcreate(2);
	}
	else if (!keyState(KEY_W) && !keyState(KEY_A) && !keyState(KEY_S) && keyState(KEY_D)) {
		move(KEY_D);
		animationcreate(1);
	}
	else if (keyState(KEY_W) && keyState(KEY_A) && !keyState(KEY_S) && !keyState(KEY_D)) {
		move(KEY_W);
		move(KEY_A);
		animationcreate(0);
		
	}
	else if (keyState(KEY_W) && !keyState(KEY_A) && !keyState(KEY_S) && keyState(KEY_D)) {
		move(KEY_W);
		move(KEY_D);
		animationcreate(1);
		
	}
	else if (!keyState(KEY_W) && keyState(KEY_A) && keyState(KEY_S) && !keyState(KEY_D)) {
		move(KEY_S);
		move(KEY_A);
		animationcreate(0);
		
	}
	else if (!keyState(KEY_W) && !keyState(KEY_A) && keyState(KEY_S) && keyState(KEY_D)) {
		move(KEY_S);
		move(KEY_D);
		animationcreate(1);
		
	}
//	updateHPSprite(delta);//调用随机出现
//	updateEXPSprite(delta);
//	pickup(delta);
//	levelup(delta);
}
void GameMap::move(EventKeyboard::KeyCode code) {

	int offsetX = 0, offsetY = 0;
	switch (code) {
	case EventKeyboard::KeyCode::KEY_W:
		offsetY = 1;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		offsetX = -1;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		offsetY = -1;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		offsetX = 1;
		break;
	default:
		offsetY = offsetX = 0;
		break;
	}
	Vec2 position = arrowman->getPosition();
	int dis = 10;
	position.x = position.x + dis * offsetX;
	position.y = position.y + dis * offsetY;
	Point tileCoord = tileCoordForPosition(position);
	int tileGid = collidable->getTileGIDAt(tileCoord);
	if (tileGid) {
		Value properties = tilemap->getPropertiesForGID(tileGid);
		ValueMap map = properties.asValueMap();
		string value = map.at("collidable").asString();
		if (value.compare("true") == 0) {
			offsetY = offsetX = 0;
		}
	}
	// 0.3s代表着动作从开始到结束所用的时间，从而显得不会那么机械。
	auto moveTo = MoveTo::create(0.3, Vec2(arrowman->getPositionX() + offsetX, arrowman->getPositionY() + offsetY));
	arrowman->runAction(moveTo);
}
	
void GameMap::backmenu(Ref* pSender)
{
	auto hs = HelloWorld::createScene();
	Director::getInstance()->pushScene(hs);
}
bool GameMap::rightposition(cocos2d::Vec2 position){

	Point tileCoord = tileCoordForPosition(position);
	if (tileCoord.x <= 0 || tileCoord.y<= 0|| tileCoord.x>= tilemap->getMapSize().width|| tileCoord.y >= tilemap->getMapSize().height) {
		return false;
	}
	int tileGid = collidable->getTileGIDAt(tileCoord);
	if (tileGid) {
		Value properties = tilemap->getPropertiesForGID(tileGid);
		ValueMap map = properties.asValueMap();
		string value = map.at("collidable").asString();
		if (value.compare("true") == 0) {
			return false;
		}
	}
	return true;
}

Vec2 GameMap::randomMovePosition(Sprite* monster) {
	srand((unsigned)time(NULL));
	//_moveCount++

	Point position;
	//	int randx = rand() % 10;
		//int	randy = rand() % 10;          // -rand() % rangey/2 + rangey / 4;
	//CCLOG("   +++");
	position = Vec2(monster->getPosition().x + dir * 20, monster->getPosition().y);
	if (!rightposition(position)) {
		dir = -dir;
		//	randx = rand() % 10;
		//	randy = rand() % 10;// -rand() % rangey + rangey / 2;
			/*_moveCount = rand() % 10 ;
			if (_moveCount % 2 == 0) {

			}
			else {
				position = Vec2(monster->getPosition().x - randx, monster->getPosition().y - randy);
			}*/
		position =  Vec2(monster->getPosition().x + dir * 55, monster->getPosition().y);
	//	CCLOG(" ....");
	}
	return position;
}

Vec2 GameMap::randomPosition() {
	int randX = random() %
		(int)(tilemap->getMapSize().width * tilemap->getTileSize().width);// +100;
	int randY = random() %
		(int)(tilemap->getMapSize().height * tilemap->getTileSize().height);// +120;
	Vec2 position = Point(randX, randY);
	Vec2 tileCoord = tileCoordForPosition(position);
	if (tileCoord.x < 0 || tileCoord.x >= tilemap->getMapSize().width
		|| tileCoord.y < 0 || tileCoord.y >= tilemap->getMapSize().height) {
		return randomPosition();
	}
	int tileGid = collidable->getTileGIDAt(tileCoord);
	if (tileGid) {
		Value properties = tilemap->getPropertiesForGID(tileGid);
		ValueMap map = properties.asValueMap();
		std::string value = map.at("collidable").asString();
		if (value.compare("true") == 0) {
			return randomPosition();
		}
		else {
			return position;
		}
	}
	return position;
}

void GameMap::updateHPSprite(float delta) {
	if (_count % 200 == 0 && _HPArray.size() <= 2) {
		Sprite* HP = Sprite::create("HP_tiledmap.png");
		HP->setScale(0.3);
		//monster->setLifeValue(9);
		//monster->setmoveCount(1);
		HP->setPosition(randomPosition());
		tilemap->addChild(HP, 12);
		_HPArray.pushBack(HP);
	}

}
void GameMap::updateEXPSprite(float delta) {
	if (_count % 200 == 0 && _EXPArray.size() <= 2) {
		Sprite* EXP = Sprite::create("EXP_tiledmap.png");
		EXP->setScale(0.3);
		//monster->setLifeValue(9);
		//monster->setmoveCount(1);
		EXP->setPosition(randomPosition());
		tilemap->addChild(EXP, 12);
		_EXPArray.pushBack(EXP);
	}
}
void GameMap::pickup(float delta) {
	for (int i = 0; i < _HPArray.size(); i++) {
		Sprite* HP = _HPArray.at(i);
		if (HP->getBoundingBox().intersectsRect(arrowman->getBoundingBox())) {
			currentmanlife = currentmanlife + 10;
			manpercent = 100 * (float)(currentmanlife / manlife);
			Loadingbarman->setPercent(manpercent);
			tilemap->removeChild(HP);
			_HPArray.eraseObject(HP);
		}
	}

	for (int i = 0; i < _EXPArray.size(); i++) {
		Sprite* EXP = _EXPArray.at(i);
		if (EXP->getBoundingBox().intersectsRect(arrowman->getBoundingBox())) {
			currentexp = currentexp + 10;
			exppercent = 100 * (float)(currentexp / expmax);
			LoadingbarEXP->setPercent(exppercent);
			tilemap->removeChild(EXP);
			_EXPArray.eraseObject(EXP);
		}
	}
}
void GameMap::levelup(float delta) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (level < 6) {
		removeChild(Level_, true);
		switch (level)
		{
		case 0:Level_ = Label::create(StringUtils::format("LV 0"), "fonts/Marker Felt.ttf", 24);
			Level_->setPosition(Vec2(visibleSize.width / 2,
				visibleSize.height - Level_->getContentSize().height + 9.5));
			addChild(Level_, 3);
			break;
		case 1:Level_ = Label::create(StringUtils::format("LV 1"), "fonts/Marker Felt.ttf", 24);
			Level_->setPosition(Vec2(visibleSize.width / 2,
				visibleSize.height - Level_->getContentSize().height + 9.5));
			addChild(Level_, 3);
			break;
		case 2:Level_ = Label::create(StringUtils::format("LV 2"), "fonts/Marker Felt.ttf", 24);
			Level_->setPosition(Vec2(visibleSize.width / 2,
				visibleSize.height - Level_->getContentSize().height + 9.5));
			addChild(Level_, 3);
			break;
		case 3:Level_ = Label::create(StringUtils::format("LV 3"), "fonts/Marker Felt.ttf", 24);
			Level_->setPosition(Vec2(visibleSize.width / 2,
				visibleSize.height - Level_->getContentSize().height + 9.5));
			addChild(Level_, 3);
			break;
		case 4:Level_ = Label::create(StringUtils::format("LV 4"), "fonts/Marker Felt.ttf", 24);
			Level_->setPosition(Vec2(visibleSize.width / 2,
				visibleSize.height - Level_->getContentSize().height + 9.5));
			addChild(Level_, 3);
		case 5:Level_ = Label::create(StringUtils::format("LV 5"), "fonts/Marker Felt.ttf", 24);
			Level_->setPosition(Vec2(visibleSize.width / 2,
				visibleSize.height - Level_->getContentSize().height + 9.5));
			addChild(Level_, 3);
			break;
		default:
			break;
		}
		if (exppercent == 100) {

			level++;
			currentexp = 0;
			exppercent = 0;
			//CCLOG("%d", level);
		}
	}
	else {
		exppercent = 0;
	}
}
void GameMap::updateMonsterSprite(float delta) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    if (num > 0) {
	   
	   if (currentmonsterlife <= 0) {
		   tilemap->removeChild(monster);
		   monsterCount=0;

	   }
	}
	if(num<=0){
		auto gs = VctoryScene::createScene();
		Director::getInstance()->pushScene(gs);
	}
	
	
	if (monsterCount ==0&& num>0) {
		monster = Sprite::create("player4.png");
		monster->setPosition(randomPosition());//(visibleSize.width*0.35, visibleSize.height*0.6);
		monster->setScale(0.6);
		tilemap->addChild(monster, 2);
		Loadingbar = LoadingBar::create("foreground.png");   //创建进度框
		Loadingbar->setPosition(Vec2(15, 40)); //设置框的位置1
		currentmonsterlife = 100;
		//manpercent = 100 * (float)(currentmanlife / manlife);
		monsterpercent = 100 * (float)(currentmonsterlife / monsterlife);
	//	CCLOG("%f", manpercent);
		Loadingbar->setPercent(monsterpercent);
		Loadingbar->setScale(0.8);
		Loadingbar->setDirection(LoadingBar::Direction::LEFT);
		monster->addChild(Loadingbar);   //加到里面去
		num--;
		monsterCount = 1;
	}

	
}
void GameMap::monsterattack() {
	float distance = (float)sqrt(pow(monster->getPosition().x - arrowman->getPosition().x, 2) + pow(monster->getPosition().y - arrowman->getPosition().y, 2));
	if (distance <= monsterrange) {
		monstershoot();
	}
}

//每帧更新，比较快。
void GameMap::quickupdate(float  delta) {
	updateMonsterSprite(delta);
	collisionDetection();
	waeponjudge();
    aishootcollisionDetection(delta);
	pickup(delta);
	levelup(delta);
	Loadingbar->setPercent(monsterpercent);
	Loadingbarman->setPercent(manpercent);
}

//更新慢，人机射箭频率慢一些。
void GameMap::slowupdate(float  delta) {

	monsterattack();

	//aishootcollisionDetection(delta, arrowman);
	if (!ismove) {
		ismove = true;
		
		auto moveTo = MoveTo::create(1, randomMovePosition(monster));
		monster->runAction(moveTo);
		monsteranimationcreate(-dir);
		ismove = false;
	}

	updateHPSprite(delta);//调用随机出现
	updateEXPSprite(delta);

}


//人射箭
void GameMap::shootaction() {
	if (isshoot) {
		return;
	}
	else if (!isshoot) {
		CCLOG("...%d...", selectedweapon);
		if (selectedweapon == 1) {
	        Vec2 manpos = arrowman->getPosition();
	        arrow = Sprite::create("arrow.png");
	        arrow->setPosition(arrowman->getPosition().x, arrowman->getPosition().y);
	        arrow->setScale(0.4);
			float angl = angle(manpos, Vec2(attposx, attposy));
			arrow->setRotation(angl);
			tilemap->addChild(arrow, 2);
        	auto moveTo = MoveTo::create(0.3, attackpos(manpos, Vec2(attposx, attposy), range1));
			auto func = CallFunc::create(CC_CALLBACK_0(GameMap::CallFunremove, this));
			arrow->runAction(Sequence::create(moveTo, func, NULL));
		    isshoot = true;
		}
		else if (selectedweapon == 2) {

			Vec2 manpos = arrowman->getPosition();
			hammer = Sprite::create("hammer.png");
			hammer->setPosition(arrowman->getPosition().x, arrowman->getPosition().y);
			hammer->setScale(0.4);
			float angl = angle(manpos, Vec2(attposx, attposy));
			hammer->setRotation(angl);
			tilemap->addChild(hammer, 2);
			auto moveTo = MoveTo::create(0.5, attackpos(manpos, Vec2(attposx, attposy), range2));
			auto rotateto = RotateTo::create(0.5, 720);
			auto func = CallFunc::create(CC_CALLBACK_0(GameMap::CallFunremove, this));
			hammer->runAction(Sequence::create(Spawn::create(moveTo, rotateto,NULL), func, NULL));
			isshoot = true;
		}

	}
}
void GameMap::CallFunremove()
{
	if (isshoot) {
		if (selectedweapon == 1) {
			isshoot = false;
			tilemap->removeChild(arrow);
		}
		else if (selectedweapon == 2) {
			isshoot = false;
			tilemap->removeChild(hammer);
		}


	
	}

}
void GameMap::collisionDetection() {
	if (isCollidearrow()) {
		if (selectedweapon == 1) {
			currentmonsterlife = currentmonsterlife - 10;
			monsterpercent = 100 * (float)(currentmonsterlife / monsterlife);
			isshoot = false;
			tilemap->removeChild(arrow);
		}
		else if (selectedweapon == 2) {
			currentmonsterlife = currentmonsterlife - 15;
			monsterpercent = 100 * (float)(currentmonsterlife / monsterlife);
			isshoot = false;
			tilemap->removeChild(hammer);
		}
	 }
	
}
bool GameMap::isCollidearrow() {
	if (isshoot) {
		if (selectedweapon == 1) {
			Rect entityRect = arrow->getBoundingBox();
			Point monsterpos = monster->getPosition();
			return entityRect.containsPoint(monsterpos);
		}
		else if (selectedweapon == 2) {
			Rect entityRect = hammer->getBoundingBox();
			Point monsterpos = monster->getPosition();
			return entityRect.containsPoint(monsterpos);
		}
	}
	else
		return false;
}


//monster射箭
void GameMap::monstershoot() {
	if (monisshot) {
		return;
	}
	else if (!monisshot) {
		monisshot = true;
		Vec2 manpos = arrowman->getPosition();
		Vec2 monsterpos = monster->getPosition();
		monsterarrow = Sprite::create("monsterarrow.png");
		monsterarrow->setPosition(monster->getPosition().x, monster->getPosition().y);
		monsterarrow->setScale(0.2);
		float angl = angle(monsterpos,manpos);
		monsterarrow->setRotation(angl);
		tilemap->addChild(monsterarrow, 2);
		auto moveTo = MoveTo::create(0.6, attackpos(monsterpos,manpos, monsterrange));
		auto func = CallFunc::create(CC_CALLBACK_0(GameMap::CallFunremovemon, this));
		monsterarrow->runAction(Sequence::create(moveTo, func, NULL));

	}
}
void GameMap::CallFunremovemon()
{
	if (monisshot) {
		tilemap->removeChild(monsterarrow);
		monisshot = false;

	}

}
void GameMap::aishootcollisionDetection(float delta) {
	if (monisCollidearrow()) {
		currentmanlife = currentmanlife - 10;
		manpercent = 100 * (float)(currentmanlife / manlife);
		CCLOG( "..    %f  %d ",manpercent, selectedweapon);

		tilemap->removeChild(monsterarrow);
		monisshot = false;
		if (currentmanlife == 0) {
			auto gs = EndScene::createScene();
			Director::getInstance()->pushScene(gs);
		}
	}

}

bool GameMap::monisCollidearrow() {
	if (monisshot) {
		Rect entityRect = monsterarrow->getBoundingBox();
		Point monsterpos = arrowman->getPosition();
		Loadingbarman->setPercent(manpercent);
		return entityRect.containsPoint(monsterpos);
	}
	else
		return false;
}

void GameMap::waeponjudge() {
	if (isshoot) {
		if (selectedweapon == 1) {
			Point pos1 = arrow->getPosition();
			if (!rightposition(pos1)) {
				isshoot = false;
				tilemap->removeChild(arrow);

			}
		}
		else if (selectedweapon == 2) {
			Point pos1 = hammer->getPosition();
			if (!rightposition(pos1)) {
				isshoot = false;
					tilemap->removeChild(hammer);
			}
		}

	}
	if (monisshot) {
		Point pos2 = monsterarrow->getPosition();
		if (!rightposition(pos2)) {
			monisshot = false;
			tilemap->removeChild(monsterarrow);

		}
	}
}

