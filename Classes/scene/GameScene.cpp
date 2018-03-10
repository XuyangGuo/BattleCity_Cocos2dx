/***********************************************

该类是进行游戏的场景，用来管理当前游戏的运行状态，
管理坦克类、子弹类、爆炸类的生命周期

***********************************************/


#include "GameScene.h"
#include "SceneM.h"
#include "data\SuccessData.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
//加音效,方便复制，故而注释在此
//SimpleAudioEngine::getInstance()->playBackgroundMusic("menu_levelScene.mp3", true);

TankM * GameScene::_tankM = nullptr;
Stage * GameScene::_stage = nullptr;
BulletM *GameScene::_bulletM = nullptr;
GameState GameScene::_gameState = kNone;
BombM* GameScene::_bombM = nullptr;


GameScene::GameScene()
{
	NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(GameScene::win), "game_win", nullptr);
	NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(GameScene::fail), "game_fail", nullptr);
}

GameScene::~GameScene()
{
	NotificationCenter::getInstance()->removeAllObservers(this);
}

void GameScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();

	_tankM = TankM::create();
	_stage->getBG()->addChild(_tankM, 3);

	_bulletM = BulletM::create();
	_stage->getBG()->addChild(_bulletM, 3);

	_bombM = BombM::create();
	_stage->getBG()->addChild(_bombM, 4);

	_stage->initInfo();
	this->scheduleUpdate();

	unsigned int randNum = rand() % 6;
	//更换BGM
	SimpleAudioEngine::getInstance()->playBackgroundMusic(String::createWithFormat("gameScene%d.mp3",randNum)->getCString(), true);

}

void GameScene::onExit()
{
	Layer::onExit();
	this->removeAllChildrenWithCleanup(true);
}

bool GameScene::init()
{
	_stage = Stage::create();
	this->addChild(_stage, 0);
	_stage->setGameScene(this);

	_gameState = kRuning;

	return true;
}

void GameScene::update(float dt)
{
	// 游戏运行
	if (kRuning == _gameState)
	{
		if (g_keySelect)
		{
			g_keySelect = false;
			_gameState = kPause;
			this->pauseGame();

			//加音效,方便复制，故而注释在此
			SimpleAudioEngine::getInstance()->playEffect("pause.mp3", false);
		}
	}

	// 游戏暂停
	if (kPause == _gameState)
	{
		auto pauseLayer = _stage->getPauseLayer();
		if (g_keySelect == true)
		{
			g_keySelect = false;
			_gameState = kRuning;
			this->resumeGame();
		}
		if (g_keyLeft || g_keyRight == true)
		{
			g_keyLeft = false;
			g_keyRight = false;
			int currentOption = _stage->getPauseLayer()->getPauseOption() ^ 1;
			pauseLayer->setPauseOption(currentOption);
			String *pauseName = String::createWithFormat("Pause%d.png", currentOption);
			static_cast<Sprite *>(pauseLayer->getChildByTag(99))->setTexture(pauseName->getCString());
		}
		if(g_keyStart)
		{
			g_keyStart = false;
			if (ReStart == (PauseOption)pauseLayer->getPauseOption())
			{
				_gameState = kRuning;
				this->resumeGame();
			}
			else
			{
				this->unscheduleUpdate();
				SceneM::getInstance()->changeScene(kMenuScene, kTransitionFade);
			}
		}
	}

	//游戏胜利
	if (kWin == _gameState)
	{
		if (g_keyLeft || g_keyRight == true)
		{
			g_keyLeft = false;
			g_keyRight = false;
			int currentOption = winLayer->getWinOption() ^ 1;
			winLayer->setWinOption(currentOption);
			int score = winLayer->getScore();
			String *winName = String::createWithFormat("Star%d_%d.png", score, currentOption);
			static_cast<Sprite *>(winLayer->getChildByTag(98))->setTexture(winName->getCString());
		}
		if (g_keyStart)
		{
			g_keyStart = false;
			this->unscheduleUpdate();
			if (nextLevel == (WinOption)winLayer->getWinOption() && DataM::getInstance()->get_id() > 0)
			{
				DataM::getInstance()->set_id(((DataM::getInstance()->get_id())%LEVEL_NUM + 1));
				SceneM::getInstance()->changeScene(kSelectHeroScene, kTransitionFade);
			}
			else if (DataM::getInstance()->get_id() < 0)
			{
				//自定义地图 3个地方
				int currentDifficulty = DataM::getInstance()->getEnemyDifficulty();
				//4为最难
				int nextDifficulty = (currentDifficulty + 1) % 5 == 0 ? 4 : currentDifficulty + 1;
				DataM::getInstance()->setEnemyDifficulty(nextDifficulty);
				SceneM::getInstance()->changeScene(kSelectHeroScene, kTransitionProgressRadialCCW);
			}
			else if(winBack == (WinOption)winLayer->getWinOption())
			{
				SceneM::getInstance()->changeScene(kMenuScene, kTransitionFade);
			}
		}
	}

	//游戏失败
	if (kFail == _gameState)
	{
		if (g_keyLeft || g_keyRight == true)
		{
			g_keyLeft = false;
			g_keyRight = false;
			int currentOption = failLayer->getFailOption() ^ 1;
			failLayer->setFailOption(currentOption);
			String *failName = String::createWithFormat("Fail%d.png", currentOption);
			static_cast<Sprite *>(failLayer->getChildByTag(97))->setTexture(failName->getCString());
		}
		if (g_keyStart)
		{
			g_keyStart = false;
			// 删除tankM
			//_tankM->fail();
			_tankM->removeFromParentAndCleanup(true);
			if (reBegin == (FailOption)failLayer->getFailOption())
			{
				this->unscheduleUpdate();
				SceneM::getInstance()->changeScene(kSelectHeroScene, kTransitionProgressRadialCCW);
			}
			else
			{
				this->unscheduleUpdate();
				SceneM::getInstance()->changeScene(kMenuScene, kTransitionFade);
			}
		}
	}
}

void GameScene::pauseGame()
{
	_stage->pauseGame();
	_tankM->pauseGame();
	_bulletM->pauseGame();
}

void GameScene::resumeGame()
{
	_stage->resumeGame();
	_tankM->resumeGame();
	_bulletM->resumeGame();
}

void GameScene::win(Ref *pSender)
{
	_stage->unschedule(schedule_selector(Stage::sliderUpdate));
	_stage->unschedule(schedule_selector(Stage::MPUpdate));
	_stage->getProgressSlider()->setPercent(100);
	this->unscheduleUpdate();  //防止2秒内暂停出BUG

	
	schedule(ccSchedulerFunc([&](float dt)
	{
		if (kFail != _gameState && kWin != _gameState)
		{
			//通关成就
			SuccessData::getInstance()->updateIsAllLevel();

			//成就更新
			currentFinished = SuccessData::getInstance()->updateAlldata();
			if (!currentFinished.empty())
			{
				showFinishedSuccess();
			}

			_gameState = kWin;
			_bulletM->pauseGame();
			_stage->pause();
			_bombM->pauseGame();
			_tankM->pauseGame();
			this->scheduleUpdate();  //打开选择关卡的update

			winLayer = WinLayer::create();
			this->addChild(winLayer, 5);

			//动画
			auto moveDown = MoveTo::create(2.0f, Vec2(0, -SCREEN_HEIGHT / 2));
			auto elasticOut = EaseElasticOut::create(moveDown);
			winLayer->runAction(elasticOut);

			// 修改最大关卡数据
			if (DataM::getInstance()->get_id() < 15 && DataM::getInstance()->get_id() > 0)
			{
				DataM::getInstance()->updateMaxLevelCanPlayed();
			}
			// 更新MaxScore和SP
			DataM::getInstance()->updateLevelMaxScoreArray(winLayer->getScore());

			//更换BGM
			SimpleAudioEngine::getInstance()->playBackgroundMusic("victory.mp3", false);

		}
	}), 2.0f, "Win");
}

void GameScene::fail(Ref *pSender)
{
	_stage->unschedule(schedule_selector(Stage::sliderUpdate));
	_stage->unschedule(schedule_selector(Stage::MPUpdate));
	_stage->getHPSlider()->setPercent(0);
	this->unscheduleUpdate();  //防止2秒内暂停出BUG

	schedule(ccSchedulerFunc([&](float dt) 
	{
		if (kFail != _gameState && kWin !=_gameState)
		{
			//成就更新
			currentFinished = SuccessData::getInstance()->updateAlldata();
			if (!currentFinished.empty())
			{
				showFinishedSuccess();
			}
			_gameState = kFail;
			_bulletM->pauseGame();
			_bombM->pauseGame();
			_stage->pause();
			_tankM->pauseGame();
			this->scheduleUpdate();  //打开选择关卡的update

			failLayer = FailLayer::create();
			this->addChild(failLayer, 5);

			//动画
			auto moveDown = MoveTo::create(2.0f, Vec2(0, -SCREEN_HEIGHT / 2));
			auto elasticOut = EaseElasticOut::create(moveDown);
			failLayer->runAction(elasticOut);

			//更换BGM
			SimpleAudioEngine::getInstance()->playBackgroundMusic("loseGame.mp3", false);

		}
	}
	), 2.0f, "Fail");
}

bool GameScene::isKReady()
{
	return _stage->changeIsKReady();
}

//void GameScene::showFinishedSuccess(std::vector<char *> &currentFinished)
//{
//	//此处用到递归动画
//	//if (0 == currentFinished.size())
//	//{
//	//	scheduleUpdate();
//	//	return;
//	//}
//	//else
//	//{
//	cocos2d::Vector<FiniteTimeAction*> Vector_action1(currentFinished.size() * 5);    //这里不能用std::vector，再一个就是<FiniteTimeAction*> 
//	cocos2d::Vector<FiniteTimeAction*> Vector_action2(currentFinished.size() * 5);    //这里不能用std::vector，再一个就是<FiniteTimeAction*> 
//
//	unscheduleUpdate();
//
//	//创建文字
//	Label *temp = Label::create("", "Simple.ttf", 50);
//	temp->setColor(Color3B(251, 255, 221));
//	temp->setPosition(210, 52.5f);
//	//创建文本框
//	Sprite *border = Sprite::create("whitebg.png");
//	this->addChild(border, 6);
//	border->addChild(temp);
//	//创建奖杯
//	Sprite *cup = Sprite::create("goldcup.png");
//	cup->setPosition(326, 52);
//	border->addChild(cup);
//
//	for (int i = 0; i < currentFinished.size(); ++i)
//	{
//		ActionInterval *blink = Blink::create(1.0f, 2);
//		ActionInterval *moveto1 = MoveTo::create(1.0f, Vec2(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5));
//		auto flyin = EaseExponentialOut::create(moveto1);
//		ActionInterval *moveto2 = MoveTo::create(1.0f, Vec2(SCREEN_WIDTH*0.5, SCREEN_HEIGHT));
//		auto flyout = EaseExponentialIn::create(moveto2);
//
//		//加入Vector
//		Vector_action1.pushBack(CallFunc::create([&]() {	border->setPosition(Vec2(SCREEN_WIDTH*0.5, 0)); }));
//		Vector_action1.pushBack(flyin);
//		Vector_action1.pushBack(DelayTime::create(1.0f));
//		Vector_action1.pushBack(flyout);
//
//		Vector_action2.pushBack(CallFunc::create([&]() {	temp->setString(currentFinished[i]); }));
//		Vector_action2.pushBack(flyin);
//		Vector_action2.pushBack(blink);
//		Vector_action2.pushBack(flyout);
//
//	}
//	Vector_action1.pushBack(CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, border)));
//	Vector_action2.pushBack(CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, temp)));
//	Vector_action2.pushBack(CallFunc::create([&]() {scheduleUpdate(); }));
//
//	auto seq1 = Sequence::create(Vector_action1);
//	auto seq2 = Sequence::create(Vector_action2);
//	temp->runAction(seq2);
//	border->runAction(seq1);
//}

void GameScene::showFinishedSuccess()
{
	log("currentFinished.size() = %d", currentFinished.size());
	//此处用到递归动画
	if (0 == currentFinished.size())
	{
		scheduleUpdate();
		return;
	}
	else
	{
		unscheduleUpdate();

		//创建文字
		Label *temp = Label::create(currentFinished[0], "Simple.ttf", 32);
		temp->setAnchorPoint(Vec2::ZERO);
		temp->setColor(Color3B(251, 255, 221));
		temp->setPosition(27, 36.5f);
		//创建文本框
		Sprite *border = Sprite::create("whitebg.png");
		this->addChild(border, 6);
		border->setPosition(Vec2(SCREEN_WIDTH*0.5, 0));
		border->addChild(temp);
		//创建奖杯
		Sprite *cup = Sprite::create("success10_1.png");
		cup->setPosition(326, 52);
		border->addChild(cup);

		ActionInterval *blink = Blink::create(1.0f, 2);
		ActionInterval *moveto1 = MoveTo::create(1.0f, Vec2(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5));
		auto flyin = EaseExponentialOut::create(moveto1);
		ActionInterval *moveto2 = MoveTo::create(1.0f, Vec2(SCREEN_WIDTH*0.5, SCREEN_HEIGHT));
		auto flyout = EaseExponentialIn::create(moveto2);
		//
		std::vector<char *>::iterator it = currentFinished.begin();
		currentFinished.erase(it);
		auto tempCurrentFinished = currentFinished;
		auto callFunUnS = [&]() {GameScene::unscheduleUpdate(); };

		auto callFunNext = [&]() {GameScene::showFinishedSuccess(); };
		//run动画
		auto sequenceAction = Sequence::create(CallFunc::create(callFunUnS), flyin, DelayTime::create(1.0f), flyout, CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, border)), NULL);
		auto sequenceAction1 = Sequence::create(flyin, blink, flyout, CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, temp)), CallFunc::create(callFunNext), NULL);
		temp->runAction(sequenceAction1);
		border->runAction(sequenceAction);
	}
}