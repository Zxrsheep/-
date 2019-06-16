#ifndef __ARROW_BASE__
#define __ARROW_BASE__
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include<iostream>
using namespace std;
USING_NS_CC;
using namespace ui;
class SpriteBase : public cocos2d::Sprite
{
private:
	//���������Ϣ��shengming,Ѫ��
	
public:
    int _lifeValue;

	LoadingBar* _HP;
	float _HPInterval;
	bool _move;
	int _moveCount;
	static SpriteBase* create(const string& filename) {
		SpriteBase* sprite = new SpriteBase();
		if (sprite && sprite->initWithFile(filename))
		{
			sprite->autorelease();
			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
	//���ú���
	void setLifeValue(int lifeValue);

	int getlifeValue() {
		return _lifeValue;
	}
	void setHP(LoadingBar* HP) {
		_HP = HP;
	}
	LoadingBar* getHP() {
		return _HP;
	}
	void setHPInterval(float HPInterval) {
		_HPInterval = HPInterval;
	}
	int getHPInterval() {
		return _HPInterval;
	}
	void setMove(bool move) {
		_move = move;
	}
	bool ismove() {
		return _move;
	}
	void setmoveCount(int moveCount) {
		_moveCount = moveCount;
	}
	int getmoveCount() {
		return _moveCount;
	}

};










#endif __ARROW_BASE__
