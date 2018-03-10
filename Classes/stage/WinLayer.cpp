#include "WinLayer.h"
#include "data\Global.h"
#include "scene\GameScene.h"
#include "tank\TankM.h"

bool WinLayer::init()
{
	int hpPercent = GameScene::getTankM()->remainedHP();
	if (hpPercent >= 80)
	{
		score = 3;
	}
	else if (hpPercent >= 40)
	{
		score = 2;
	}
	else
	{
		score = 1;
	}

	winOption = 0;   // nextLevel

	String *winName = String::createWithFormat("Star%d_%d.png", score, winOption);
	auto winBG = Sprite::create(winName->getCString());
	winBG->setPosition(Vec2(SCREEN_WIDTH*0.5, SCREEN_HEIGHT));
	this->addChild(winBG, 2, 98);

	return true;
}