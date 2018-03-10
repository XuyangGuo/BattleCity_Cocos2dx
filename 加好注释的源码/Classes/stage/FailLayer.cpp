/***********************************************

该类管维护失败弹出层的生命周期

***********************************************/

#include "FailLayer.h"
#include "data\Global.h"

bool FailLayer::init()
{
	failOption = 0;   // nextLevel

	auto failBG = Sprite::create("Fail0.png");
	failBG->setPosition(Vec2(SCREEN_WIDTH*0.5, SCREEN_HEIGHT));
	this->addChild(failBG, 2, 97);

	return true;
}