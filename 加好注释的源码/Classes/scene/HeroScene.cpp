/***********************************************

该类是主菜单角色选项下面的角色按钮的跳转页面，
主要功能包括音效管理、按钮管理、主菜单和技能页面的跳转

***********************************************/

#include "HeroScene.h"
#include "data\Global.h"
#include "SceneM.h"
#include "data\DataM.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
//加音效,方便复制，故而注释在此
//SimpleAudioEngine::getInstance()->playBackgroundMusic("menu_levelScene.mp3", true);

void HeroScene::onExit()
{
	Layer::onExit();
	removeAllChildrenWithCleanup(true);
}

void HeroScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	this->scheduleUpdate();

	//加音效
	unsigned int randNum = rand() % 6;
	SimpleAudioEngine::getInstance()->playBackgroundMusic(String::createWithFormat("skillScene%d.mp3", randNum)->getCString(), false);

}

bool HeroScene::init()
{
	Sprite *heroBG = Sprite::create("LevelBackground.jpg");
	heroBG->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);	
	this->addChild(heroBG, 0);

	Sprite *threeTanks = Sprite::create("ThreeTanks.png");
	threeTanks->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	this->addChild(threeTanks, 2);
	
	//tag 为0
	bigCircle0 = Sprite::create("BigCircle.png");
	bigCircle0->setPosition(216, 417);
	this->addChild(bigCircle0, 1, 0);

	//tag 为1
	bigCircle1 = Sprite::create("FullBigCircle.png");
	bigCircle1->setPosition(512, 417);
	this->addChild(bigCircle1, 1, 1);

	//tag 为2
	bigCircle2 = Sprite::create("FullBigCircle.png");
	bigCircle2->setPosition(815, 417);
	this->addChild(bigCircle2, 1, 2);

	return true;
}

void HeroScene::update(float dt)
{
	//圆圈转动
	Sprite *selectedBigCircle = static_cast<Sprite *>(getChildByTag(heroOption));
	selectedBigCircle->setRotation(selectedBigCircle->getRotation() - 90 * dt);

	if (g_keyRight || g_keyLeft)
	{
		int move; //移动方向
		if (g_keyRight)
		{
			move = 1;
		}
		else
		{
			move = -1;
		}
		g_keyRight = false;
		g_keyLeft = false;
		Sprite *currentBigCircle = static_cast<Sprite *>(getChildByTag(heroOption));
		currentBigCircle->setTexture("FullBigCircle.png");
		currentBigCircle->setRotation(0); //圆圈复位
		heroOption = heroOption + move;
		if (heroOption < 0)
		{
			heroOption += 3;
		}
		heroOption = heroOption % 3;
		Sprite *nextOverBigCircle = static_cast<Sprite *>(getChildByTag(heroOption));
		nextOverBigCircle->setTexture("BigCircle.png");
	}
	if (g_keyStart)
	{
		g_keyStart = false;
		this->unscheduleUpdate();
		auto sceneM = SceneM::getInstance();
		DataM::getInstance()->setHType((HeroType)heroOption);
		sceneM->changeScene(kSkillScene, kTransitionCrossFade);
	}
	if (g_keySelect)
	{
		g_keySelect = false;
		this->unscheduleUpdate();
		SceneM::getInstance()->changeScene(kMenuScene, kTransitionZoomFlipAngular_LEFT_OVER);
	}

	//加音效
	if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		unsigned int randNum = rand() % 6;
		SimpleAudioEngine::getInstance()->playBackgroundMusic(String::createWithFormat("skillScene%d.mp3", randNum)->getCString(), false);
	}
}