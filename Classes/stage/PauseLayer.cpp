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