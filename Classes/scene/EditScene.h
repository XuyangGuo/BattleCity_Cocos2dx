#pragma once
#include"cocos2d.h"
#include<iostream>
#include "ui\UIScale9Sprite.h"
#include <vector>
#include <fstream>

USING_NS_CC;
using namespace ui;


class EditScene :public Layer {
public:
	CREATE_FUNC(EditScene);
	virtual bool init();
	Vec2 getPosition(int x, int y);
private:
	void update(float dt);
	void moveArrow();
	void readName();
	void saveName();
	void initMapChoice();
	void updateMapChoice();

	int mapNumMax = 0;
	Scale9Sprite*_arrow;
	int option1;
	int option2;
	int option3;
	int option4;
	Sprite* difficulty[5];
	
	std::vector<Sprite*> mapChoice;
	int enemyDifficulty=4;
	std::vector<std::string> mapNames;
	int mapNumber=-1;
};
