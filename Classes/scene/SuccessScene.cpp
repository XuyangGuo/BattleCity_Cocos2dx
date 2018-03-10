#include"SuccessScene.h"
#include<iostream>
#include "SceneM.h"
#include "data\Global.h"
#include "data\SuccessData.h"
#include "data\ChineseFonts.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
//加音效,方便复制，故而注释在此
//SimpleAudioEngine::getInstance()->playBackgroundMusic("menu_levelScene.mp3", true);


void SuccessScene::onExit()
{
	removeAllChildren();
	Layer::onExit();
}

void SuccessScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	this->scheduleUpdate();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("successScene.mp3", true);

}

bool SuccessScene::init() {
	Sprite *successBackground = Sprite::create("LevelBackground.jpg");
	successBackground->setPosition(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	this->addChild(successBackground, 0);
	SuccessData *successData = SuccessData::getInstance();
	//破砖成就
	int bricknum = successData->getBrickNumProgress();
	Sprite *success1 = Sprite::create("whitebg.png");
	success1->setPosition(Vec2(274, 653.5));
	Sprite *goldcup1 = Sprite::create(String::createWithFormat("success1_%d.png", successData->isBrickNumFinished() ? 1 : 0)->getCString());
	goldcup1->setPosition(Vec2(425, 651));
	this->addChild(goldcup1, 3);
	this->addChild(success1);
	if (!successData->isBrickNumFinished()) 
	{
		Sprite *success1greyBG = Sprite::create("greybg.png");
		success1greyBG->setPosition(Vec2(274, 651.5));
		this->addChild(success1greyBG, 4);
	}
	Label* brick = Label::create(FontToUTF8("搬砖工"), "Simple.ttf", 46);
	brick->setColor(Color3B(251, 255, 221));
	brick->setAnchorPoint(Vec2::ZERO);
	brick->setPosition(Vec2(91,649));
	this->addChild(brick, 2);
	Label* brick1 = Label::create(FontToUTF8("打破1000块砖"), "Simple.ttf", 32);
	brick1->setAnchorPoint(Vec2::ZERO);
	brick1->setPosition(Vec2(91, 607));
	this->addChild(brick1, 2);
	Label* label1 = Label::create(String::createWithFormat("%d/1000", bricknum)->getCString(), "Simple.ttf", 22);
	label1->setAnchorPoint(Vec2(1, 0));
	label1->setPosition(Vec2(460, 614));
	this->addChild(label1, 5);

	//发射子弹成就
	int bulletnum = successData->getBulletNumProgress();
	Sprite *success2 = Sprite::create("whitebg.png");
	success2->setPosition(Vec2(274, 517.75));
	this->addChild(success2);
	Sprite *goldcup2 = Sprite::create(String::createWithFormat("success2_%d.png", successData->isBulletNumFinished() ? 1 : 0)->getCString());
	goldcup2->setPosition(Vec2(425, 517.25));
	this->addChild(goldcup2, 3);
	if (!successData->isBulletNumFinished())
	{
		Sprite *success2greyBG = Sprite::create("greybg.png");
		success2greyBG->setPosition(Vec2(274, 517.75));
		this->addChild(success2greyBG, 4);
	}
	Label* bullet = Label::create(FontToUTF8("神枪手"), "Simple.ttf", 46);
	bullet->setAnchorPoint(Vec2::ZERO);
	bullet->setPosition(Vec2(91, 515.25f));
	this->addChild(bullet,2);
	Label* bullet1 = Label::create(FontToUTF8("发出2000颗子弹"), "Simple.ttf", 32);
	bullet1->setAnchorPoint(Vec2::ZERO);
	bullet1->setPosition(Vec2(91, 473.25f));
	this->addChild(bullet1,2);
	Label* label2 = Label::create(String::createWithFormat("%d/2000", bulletnum)->getCString(), "Simple.ttf", 22);
	label2->setAnchorPoint(Vec2(1, 0));
	label2->setPosition(Vec2(460, 480.25));
	this->addChild(label2,5);

	//打爆100辆坦克成就
	int hittanknum = successData->getHitTankNumProgress();
	Sprite *success3 = Sprite::create("whitebg.png");
	success3->setPosition(Vec2(274, 384));
	this->addChild(success3);

	Sprite *goldcup3 = Sprite::create(String::createWithFormat("success3_%d.png", successData->isHitTankNumFinished() ? 1 : 0)->getCString());
	goldcup3->setPosition(Vec2(425, 383.5));
	this->addChild(goldcup3, 3);
	if (!successData->isHitTankNumFinished())
	{
		Sprite *success3greyBG = Sprite::create("greybg.png");
		success3greyBG->setPosition(Vec2(274, 384));
		this->addChild(success3greyBG, 4);
	}

	Label* tank = Label::create(FontToUTF8("杀人如麻"), "Simple.ttf", 46);
	tank->setAnchorPoint(Vec2::ZERO);
	tank->setPosition(Vec2(91, 381.5f));
	this->addChild(tank,2);
	Label* tank1 = Label::create(FontToUTF8("打死300辆坦克"), "Simple.ttf", 32);
	tank1->setAnchorPoint(Vec2::ZERO);
	tank1->setPosition(Vec2(91, 339.5f));
	this->addChild(tank1,2);
	Label* label3 = Label::create(String::createWithFormat("%d/100", hittanknum)->getCString(), "Simple.ttf", 26);
	label3->setAnchorPoint(Vec2::ZERO);
	label3->setPosition(Vec2(395, 346.5));
	this->addChild(label3,5);

	//死亡15次成就
	int deathtime = successData->getDeathTimeProgress();
	Sprite *success4 = Sprite::create("whitebg.png");
	success4->setPosition(Vec2(274, 250.25));
	this->addChild(success4);

	Sprite *goldcup4 = Sprite::create(String::createWithFormat("success4_%d.png", successData->isDeathTimeFinished() ? 1 : 0)->getCString());
	goldcup4->setPosition(Vec2(425, 249.75));
	this->addChild(goldcup4, 3);
	if (!successData->isDeathTimeFinished())
	{
		Sprite *success4greyBG = Sprite::create("greybg.png");
		success4greyBG->setPosition(Vec2(274, 250.25));
		this->addChild(success4greyBG, 4);
	}

	Label* death = Label::create(FontToUTF8("死神来了"), "Simple.ttf", 46);
	death->setAnchorPoint(Vec2::ZERO);
	death->setPosition(Vec2(91, 247.75f));
	this->addChild(death,2);
	Label* death1 = Label::create(FontToUTF8("死亡15次"), "Simple.ttf", 32);
	death1->setAnchorPoint(Vec2::ZERO);
	death1->setPosition(Vec2(91, 205.75f));
	this->addChild(death1,2);
	Label* label4 = Label::create(String::createWithFormat("%d/15", deathtime)->getCString(), "Simple.ttf", 26);
	label4->setAnchorPoint(Vec2::ZERO);
	label4->setPosition(Vec2(400, 213));
	this->addChild(label4,5);

	//被摧毁基地20次
	int homebreaktime = successData->getHomeBreakTimeProgress();
	Sprite *success5 = Sprite::create("whitebg.png");
	success5->setPosition(Vec2(274, 116.5));
	this->addChild(success5);

	Sprite *goldcup5 = Sprite::create(String::createWithFormat("success5_%d.png", successData->isHomeBreakTimeFinished() ? 1 : 0)->getCString());
	goldcup5->setPosition(Vec2(425, 116));
	this->addChild(goldcup5, 3);
	if (!successData->isHomeBreakTimeFinished())
	{
		Sprite *success5greyBG = Sprite::create("greybg.png");
		success5greyBG->setPosition(Vec2(274, 116.5));
		this->addChild(success5greyBG, 4);
	}

	Label* home = Label::create(FontToUTF8("隔壁老王"), "Simple.ttf", 46);
	home->setAnchorPoint(Vec2::ZERO);
	home->setPosition(Vec2(91, 114));
	this->addChild(home,2);
	Label* home1 = Label::create(FontToUTF8("家被拆20次"), "Simple.ttf", 32);
	home1->setAnchorPoint(Vec2::ZERO);
	home1->setPosition(Vec2(91, 72));
	this->addChild(home1,2);
	Label* label5 = Label::create(String::createWithFormat("%d/20", homebreaktime)->getCString(), "Simple.ttf", 26);
	label5->setAnchorPoint(Vec2::ZERO);
	label5->setPosition(Vec2(400,79.25));
	this->addChild(label5,5);

	//发动大招30次成就
	int bigskilltime = successData->getBigSkillTimeProgress();
	Sprite *success6 = Sprite::create("whitebg.png");
	success6->setPosition(Vec2(750, 651.5));
	this->addChild(success6);

	Sprite *goldcup6 = Sprite::create(String::createWithFormat("success6_%d.png", successData->isBigSkillTimeFinished() ? 1 : 0)->getCString());
	goldcup6->setPosition(Vec2(901, 651));
	this->addChild(goldcup6, 3);
	if (!successData->isBigSkillTimeFinished())
	{
		Sprite *success6greyBG = Sprite::create("greybg.png");
		success6greyBG->setPosition(Vec2(750, 651.5f));
		this->addChild(success6greyBG, 4);
	}

	Label* bigskill = Label::create(FontToUTF8("洪荒之力"), "Simple.ttf", 46);
	bigskill->setAnchorPoint(Vec2::ZERO);
	bigskill->setPosition(Vec2(567, 649));
	this->addChild(bigskill,2);
	Label* bigskill1 = Label::create(FontToUTF8("施放技能30次"), "Simple.ttf", 32);
	bigskill1->setAnchorPoint(Vec2::ZERO);
	bigskill1->setPosition(Vec2(567, 607));
	this->addChild(bigskill1,2);

	Label* label6 = Label::create(String::createWithFormat("%d/30", bigskilltime)->getCString(), "Simple.ttf", 26);
	label6->setAnchorPoint(Vec2::ZERO);
	label6->setPosition(Vec2(876,614));
	this->addChild(label6,5);

	//游戏3小时成就
	int staytime = successData->getStayTime();
	Sprite *success7 = Sprite::create("whitebg.png");
	success7->setPosition(Vec2(750, 517.75));
	this->addChild(success7);

	Sprite *goldcup7 = Sprite::create(String::createWithFormat("success7_%d.png", successData->isStayTimeFinished() ? 1 : 0)->getCString());
	goldcup7->setPosition(Vec2(901, 517.25));
	this->addChild(goldcup7, 3);
	if (!successData->isStayTimeFinished())
	{
		Sprite *success7greyBG = Sprite::create("greybg.png");
		success7greyBG->setPosition(Vec2(750, 517.75));
		this->addChild(success7greyBG, 4);
	}
	Label* stay = Label::create(FontToUTF8("在洗澡呢"), "Simple.ttf", 46);
	stay->setAnchorPoint(Vec2::ZERO);
	stay->setPosition(Vec2(567, 515.25f));
	this->addChild(stay,2);
	Label* staytime1 = Label::create(FontToUTF8("待机3小时"), "Simple.ttf", 32);
	staytime1->setAnchorPoint(Vec2::ZERO);
	staytime1->setPosition(Vec2(567, 473.25f));
	this->addChild(staytime1,2);

	Label* label7 = Label::create(String::createWithFormat("%d/180", int(staytime/60))->getCString(), "Simple.ttf", 26);
	label7->setAnchorPoint(Vec2::ZERO);
	label7->setPosition(Vec2(876,480.25));
	this->addChild(label7,5);

	//任一普通技能max成就
	int skillmax = successData->getSkillMaxProgress();
	Sprite *success8 = Sprite::create("whitebg.png");
	success8->setPosition(Vec2(750, 384));
	this->addChild(success8);

	Sprite *goldcup8 = Sprite::create(String::createWithFormat("success8_%d.png", successData->isSkillMaxFinished() ? 1 : 0)->getCString());
	goldcup8->setPosition(Vec2(901, 383.5));
	this->addChild(goldcup8, 3);
	if (!successData->isSkillMaxFinished())
	{
		Sprite *success8greyBG = Sprite::create("greybg.png");
		success8greyBG->setPosition(Vec2(750, 384));
		this->addChild(success8greyBG, 4);
	}
	Label* maxskill= Label::create(FontToUTF8("大师"), "Simple.ttf", 46);
	maxskill->setAnchorPoint(Vec2::ZERO);
	maxskill->setPosition(Vec2(567, 381.5f));
	this->addChild(maxskill,2);

	Label* maxskill1 = Label::create(FontToUTF8("任一技能点满"), "Simple.ttf", 32);
	maxskill1->setAnchorPoint(Vec2::ZERO);
	maxskill1->setPosition(Vec2(567, 339.5f));
	this->addChild(maxskill1,2);

	Label* label8 = Label::create(String::createWithFormat("%d/5", skillmax)->getCString(), "Simple.ttf", 26);
	label8->setAnchorPoint(Vec2::ZERO);
	label8->setPosition(Vec2(876,346.5));
	this->addChild(label8,5);

	//成就打通所有关卡
	int alllevel = successData->getAllLevelProgress();
	Sprite *success9 = Sprite::create("whitebg.png");
	success9->setPosition(Vec2(750, 250.25f));
	this->addChild(success9);

	Sprite *goldcup9 = Sprite::create(String::createWithFormat("success9_%d.png", successData->isAllLevelFinished() ? 1 : 0)->getCString());
	goldcup9->setPosition(Vec2(901, 249.75));
	this->addChild(goldcup9, 3);
	if (!successData->isAllLevelFinished())
	{
		Sprite *success9greyBG = Sprite::create("greybg.png");
		success9greyBG->setPosition(Vec2(750, 250.25f));
		this->addChild(success9greyBG, 4);
	}
	Label* levelall = Label::create(FontToUTF8("独孤求败"), "Simple.ttf", 46);
	levelall->setAnchorPoint(Vec2::ZERO);
	levelall->setPosition(Vec2(567, 247.75f));
	this->addChild(levelall,2);
	Label* levelall1 = Label::create(FontToUTF8("打通所有关卡"), "Simple.ttf", 32);
	levelall1->setAnchorPoint(Vec2::ZERO);
	levelall1->setPosition(Vec2(567, 205.75f));
	this->addChild(levelall1,2);
	
	Label* label9 = Label::create(String::createWithFormat("%d/15", alllevel)->getCString(), "Simple.ttf", 26);
	label9->setAnchorPoint(Vec2::ZERO);
	label9->setPosition(Vec2(876,213));
	this->addChild(label9,5);

	//打通所有成就成就
	int allopen = successData->getAllOpenProgress();
	Sprite *success10 = Sprite::create("whitebg.png");
	success10->setPosition(Vec2(750, 116.5f));
	this->addChild(success10);

	Sprite *goldcup10 = Sprite::create(String::createWithFormat("success10_%d.png", successData->isAllOpenFinished() ? 1 : 0)->getCString());
	goldcup10->setPosition(Vec2(901, 116));
	this->addChild(goldcup10, 3);
	if (!successData->isAllOpenFinished())
	{
		Sprite *success10greyBG = Sprite::create("greybg.png");
		success10greyBG->setPosition(Vec2(750, 116.5f));
		this->addChild(success10greyBG, 4);
	}
	Label* all = Label::create(FontToUTF8("老司机"), "Simple.ttf", 46);
	all->setAnchorPoint(Vec2::ZERO);
	all->setPosition(Vec2(567, 114));
	this->addChild(all,2);
	Label* all1 = Label::create(FontToUTF8("获得所有成就"), "Simple.ttf", 32);
	all1->setAnchorPoint(Vec2::ZERO);
	all1->setPosition(Vec2(567, 72));
	this->addChild(all1,2);
	
	Label* label10 = Label::create(String::createWithFormat("%d/10", allopen)->getCString(), "Simple.ttf", 26);
	label10->setAnchorPoint(Vec2::ZERO);
	label10->setPosition(Vec2(876,79.25));
	this->addChild(label10,5);

	return true;
}

void SuccessScene::update(float dt) {
	if (g_keySelect || g_keyStart)
	{
		g_keySelect = false;
		g_keyStart = false;
		this->unscheduleUpdate();
		/*AudioM::play2d(A_START);*/
		SceneM::getInstance()->changeScene(kMenuScene, kTransitionPageTurn_true);
	}
}