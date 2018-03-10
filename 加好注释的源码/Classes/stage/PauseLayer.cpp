/***********************************************

该类管维护暂停弹出层的生命周期

***********************************************/

#include "PauseLayer.h"
#include "data\Global.h"

bool PauseLayer::init()
{
	auto pauseBG = Sprite::create("Pause0.png");
	pauseBG->setPosition(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	this->addChild(pauseBG, 1, 99);

	pauseOption = 0;

	return true;
}