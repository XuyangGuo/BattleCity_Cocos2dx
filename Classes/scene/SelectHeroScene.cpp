#include "SelectHeroScene.h"
#include "data\Global.h"
#include "SceneM.h"
#include "data\DataM.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
//加音效,方便复制，故而注释在此
//SimpleAudioEngine::getInstance()->playBackgroundMusic("menu_levelScene.mp3", true);


void SelectHeroScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	this->scheduleUpdate();
	//加音效
	SimpleAudioEngine::getInstance()->playBackgroundMusic("heroScene.mp3", true);

}

void SelectHeroScene::onExit()
{
	Layer::onExit();
	this->removeAllChildrenWithCleanup(true);
}

bool SelectHeroScene::init()
{
	Sprite *bgHero = Sprite::create("BGHero.png");
	bgHero->setPosition(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5);
	this->addChild(bgHero, 0);

	selectedHero = Sprite::create("Hero0.png");
	selectedHero->setPosition(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5);
	this->addChild(selectedHero, 1);

	heroOption = 0;

	return true;
}

void SelectHeroScene::update(float dt)
{
	if (g_keyRight)
	{
		g_keyRight = false;
		heroOption = (heroOption + 1) % 3;
		String *selectedHeroName = String::createWithFormat("Hero%d.png", heroOption);
		selectedHero->setTexture(selectedHeroName->getCString());
	}
	if (g_keyLeft)
	{
		g_keyLeft = false;
		if (--heroOption < 0)
		{
			heroOption += 3;
		}
		String *selectedHeroName = String::createWithFormat("Hero%d.png", heroOption);
		selectedHero->setTexture(selectedHeroName->getCString());
	}
	if (g_keyStart)
	{
		g_keyStart = false;
		DataM::getInstance()->setHType((HeroType)heroOption);
		this->unscheduleUpdate();
		SceneM::getInstance()->changeScene(kGameScene, kTransitionSplitRows);
	}
	if (g_keySelect)
	{
		g_keySelect = false;
		/*AudioM::play2d(A_START);*/
		this->unscheduleUpdate();
		SceneM::getInstance()->changeScene(kLevelScene, kTransitionCrossFade);
	}
}