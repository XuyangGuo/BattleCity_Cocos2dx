/***********************************************

该类管维护技能页面的生命周期，主要包括技能页面的前端、按钮管理、
后台数据的传递（主要指加点信息和皮肤信息，传递给DataM）

***********************************************/

#include "data\Global.h"
#include "scene\SceneM.h"
#include "SkillScene.h"
#include "data\ChineseFonts.h"
#include "data\SuccessData.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
//加音效,方便复制，故而注释在此
//SimpleAudioEngine::getInstance()->playBackgroundMusic("menu_levelScene.mp3", true);

void SkillScene::onExit()
{
	Layer::onExit();
	removeAllChildrenWithCleanup(true);
}

void SkillScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	scheduleUpdate();
}

bool SkillScene::init()
{
	//数据初始化
	detailLayer = false;
	option = 0;
	row = 0;
	col = 0;
	skinMax = 3;
	dataM = DataM::getInstance();
	skillDetail = SkillDetail::getInstance();
	skinId = DataM::getInstance()->getSkinId();
	heroType = (HeroType)DataM::getInstance()->getHType();
	skinNum = SuccessData::getInstance()->updateSkin();
	DataM::getInstance()->getAllSPMatrix(SP, SPMax, SPNeed, SPDepend);


	Sprite *skillSceneBG = Sprite::create("LevelBackground.jpg");
	skillSceneBG->setPosition(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	this->addChild(skillSceneBG, 0);

	Label *skillLabel = Label::create(FontToUTF8("技能"), "Simple.ttf", 70);
	skillLabel->setPosition(Vec2(SCREEN_WIDTH*0.25, 703));
	this->addChild(skillLabel, 1);

	Label *skinLabel = Label::create(FontToUTF8("皮肤"),"Simple.ttf",70);
	skinLabel->setPosition(Vec2(SCREEN_WIDTH*0.75, 703));
	this->addChild(skinLabel, 1);

	rectBG = Sprite::create("SkillBGRect.png");
	rectBG->setPosition(Vec2(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5));
	this->addChild(rectBG, 0);

	//上方光标
	upSelectedRect = ui::Scale9Sprite::create("Normal.png");
	upSelectedRect->setContentSize(Size(200, 80));
	upSelectedRect->setPosition(SCREEN_WIDTH *(0.25 + option*0.5), 703);
	this->addChild(upSelectedRect, 2, "customSelectedRect");
	upSelectedRect->setVisible(!detailLayer);

	//下方光标
	downSelectedRect = Sprite::create("SelectedRect.png");
	downSelectedRect->setPosition(Vec2(168 + col * 173, 584 - 126 * row));
	this->addChild(downSelectedRect, 2);
	downSelectedRect->setVisible(detailLayer);

	//技能树初始化
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (0 != SPMax[i][j])
			{
				String *unitSpriteName = String::createWithFormat("Skill%d_%d_%d.png", heroType, i, j);
				Sprite *unitSprite = Sprite::create(unitSpriteName->getCString());
				unitSprite->setPosition(Vec2(168 + j * 173, 582 - 126 * i));
				this->addChild(unitSprite, 1, i * 10 + j);

				//阴影
				Sprite *shadowRect = Sprite::create("Shadow.png");
				shadowRect->setPosition(Vec2(50, 50));
				unitSprite->addChild(shadowRect, 2, "shadow");
				shadowRect->setVisible(!(bool)SP[i][j]);

				//普通框框
				Sprite *normalRect = Sprite::create("Normal.png");
				normalRect->setPosition(Vec2(50, 50));
				unitSprite->addChild(normalRect, 3);

				if (0 == j)
				{
					Sprite *fontBG = Sprite::create("skillRect.png");
					fontBG->setPosition(Vec2(80, 10));
					unitSprite->addChild(fontBG, 2, "fontBG");
					fontBG->setVisible((bool)SP[i][j]);
					
					String *skillLevelName = String::createWithFormat("%d/%d", SP[i][j], SPMax[i][j]);
					Label *skillLevelLabel = Label::create(skillLevelName->getCString(), "Simple.ttf", 19);
					fontBG->addChild(skillLevelLabel, 2, "skillLevel");
					skillLevelLabel->setPosition(20, 10);
					skillLevelLabel->setColor(Color3B(76, 76, 76));
				}
			}
		}
	}

	//技能依赖箭头
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (0 != SPDepend[i][j])
			{
				Sprite *tempUnitSprite = static_cast<Sprite *> (this->getChildByTag(i * 10 + j));
				auto tempUnitSpritePos = tempUnitSprite->getPosition();
				if (0 != (SPDepend[i][j] & 1))
				{
					Sprite *arrow = Sprite::create("rightArrow.png");
					arrow->setPosition(Vec2(-85 + tempUnitSpritePos.x, tempUnitSpritePos.y));
					//防止加点连接线闪烁,所以设置为下方矩形框的孩子
					rectBG->addChild(arrow, 1);
				}
				if (0 != (SPDepend[i][j] & 8))
				{
					Sprite *arrow = Sprite::create("downArrow.png");
					arrow->setPosition(Vec2(tempUnitSpritePos.x, 63 + tempUnitSpritePos.y));
					//防止加点连接线闪烁,所以设置为下方矩形框的孩子
					rectBG->addChild(arrow, 1);
				}
				//此处少了下方和右侧两种情况，因为暂时的游戏中还没有这两种情况出现，如果出现了，可以参考上两种情况，应该很好写
			}
		}
	}

	//星星
	starAll = Sprite::create("Star1.png");
	starAll->setPosition(800, 90);
	rectBG->addChild(starAll, 1, "star0");

	starNeed = Sprite::create("Star1.png");
	starNeed->setPosition(550, 90);
	rectBG->addChild(starNeed,1,"star1");

	starAllNum = dataM->getSP();
	String *starAllNumLabelString = String::createWithFormat("%s         X %02d", FontToUTF8("剩余"), starAllNum);
	starAllNumLabel = Label::create(starAllNumLabelString->getCString(), "Simple.ttf", 30);
	rectBG->addChild(starAllNumLabel);
	starAllNumLabel->setPosition(790, 90);

	starNeedNum = SPNeed[row][col];
	//String *starNeedNumLabelString = String::createWithFormat("%s         X%02d", FontToUTF8("所需"), starNeedNum);
	//starNeedNumLabel = Label::create(starNeedNumLabelString->getCString(), "Simple.ttf", 30);
	starNeedNumLabel = Label::create("", "Simple.ttf", 30);
	rectBG->addChild(starNeedNumLabel);
	starNeedNumLabel->setPosition(540, 90);
	
	starNeedNumLabel->setVisible(false);
	starNeed->setVisible(false);

	//技能描述,锚点为0,0
	skillDiscribeLabel = Label::create("", "Simple.ttf", 30);
	skillDiscribeLabel->setAnchorPoint(Vec2::ZERO);
	skillDiscribeLabel->setPosition(180, 20);
	rectBG->addChild(skillDiscribeLabel);
	skillDiscribeLabel->setVisible(false);

	//技能名称,锚点为0,0
	skillNameLabel = Label::create("", "Simple.ttf", 30);
	skillNameLabel->setAnchorPoint(Vec2::ZERO);
	skillNameLabel->setPosition(180, 75);
	rectBG->addChild(skillNameLabel);
	skillNameLabel->setVisible(false);

	//皮肤页面,标签101
	Sprite *currentSkin = Sprite::create(String::createWithFormat("Skin%d_%d.png", (int)heroType, skinId)->getCString());
	currentSkin->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	this->addChild(currentSkin, 1, 101);
	currentSkin->setVisible(false);
	currentSkin->setScale(0.4);
	//皮肤名称
	Label *skinName = Label::create(SkillDetail::getInstance()->getSkinName(), "Simple.ttf", 42);
	skinName->setPosition(SCREEN_WIDTH/2, 100);
	this->addChild(skinName, 1, "skinName");
	skinName->setVisible(false);
	//左箭头，标签100
	Sprite *leftArrow = Sprite::create("skinArrow.png");
	leftArrow->setPosition(53, SCREEN_HEIGHT * 0.5);
	this->addChild(leftArrow, 1, 100);
	leftArrow->setName("leftArrow");
	leftArrow->setVisible(false);
	//右箭头，标签102
	Sprite *rightArrow = Sprite::create("skinArrow.png");
	rightArrow->setPosition(SCREEN_WIDTH - 53, SCREEN_HEIGHT * 0.5);
	this->addChild(rightArrow, 1, 102);
	rightArrow->setRotation(180);
	rightArrow->setVisible(false);
	rightArrow->setName("rightArrow");
	//皮肤大圆
	Sprite *bigCircle = Sprite::create("FullBigCircle.png");
	bigCircle->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	this->addChild(bigCircle, 0, "bigCircle");
	bigCircle->setScale(2.0f);
	bigCircle->setVisible(false);

	return true;
}

void SkillScene::update(float dt)
{
	if (true == g_keySelect)
	{
		g_keySelect = false;
		if (detailLayer)
		{
			detailLayer = false;
			//下方光标消失
			downSelectedRect->setVisible(detailLayer);

			//上方光标出现
			upSelectedRect->setVisible(!detailLayer);

			//消失大圆
			Sprite *bigCircle = static_cast<Sprite *>(this->getChildByName("bigCircle"));
			bigCircle->setVisible(detailLayer);

			if (0 == option)
			{
				//所需星星
				starNeedNumLabel->setVisible(false);
				starNeed->setVisible(false);

				//技能描述
				skillDiscribeLabel->setVisible(false);

				//技能名称
				skillNameLabel->setVisible(false);

				//开启上方光标
				upSelectedRect->setVisible(!detailLayer);

				//关闭大圆
				Sprite *bigCircle = static_cast<Sprite *>(this->getChildByName("bigCircle"));
				bigCircle->setVisible(detailLayer);

			}
		}
		else
		{
			this->unscheduleUpdate();
			SceneM::getInstance()->changeScene(kHeroScene, kTransitionCrossFade);
		}
	}

	if (true == g_keyStart)
	{
		g_keyStart = false;
		if (detailLayer)
		{
			if (0 == option)
			{
				bool isDependReady = true;  //前置是否准备好
				if ((0 != (SPDepend[row][col] & 8)) && (0 == SP[row - 1][col]))
				{
					isDependReady = false;
				}
				if ((0 != (SPDepend[row][col] & 1)) && (0 == SP[row][col - 1]))
				{
					isDependReady = false;
				}
				//此处少了下方和右侧两种情况，因为暂时的游戏中还没有这两种情况出现，如果出现了，可以参考上两种情况，应该很好写


				//加技能
				if (dataM->getSP() >= SPNeed[row][col] && isDependReady)  //有SP判定
				{
					int spDecreament = dataM->addSkill(row, col);

					//刷新透明
					auto tempUnitSprite = static_cast<Sprite *>(this->getChildByTag(row * 10 + col));
					Sprite *tempShadowRect = static_cast<Sprite *>(tempUnitSprite->getChildByName("shadow"));
					tempShadowRect->setVisible(!(bool)SP[row][col]);

					if (0 == col)
					{
						//刷新右下角框框
						Sprite *currentFontBG = static_cast<Sprite *>(tempUnitSprite->getChildByName("fontBG"));
						currentFontBG->setVisible((bool)SP[row][col]);

						Label *cuttentskillLevel = static_cast<Label *>(currentFontBG->getChildByName("skillLevel"));
						String *skillLevelName = String::createWithFormat("%d/%d", SP[row][col], SPMax[row][col]);
						cuttentskillLevel->setString(skillLevelName->getCString());
					}

					//刷新剩余技能点
					auto tempStarAllNum = dataM->getSP();
					String *tempStarAllNumLabelString = String::createWithFormat("%s         X %02d", FontToUTF8("剩余"), tempStarAllNum);
					starAllNumLabel->setString(tempStarAllNumLabelString->getCString());
					//刷新所需技能点
					auto tempStarNeedNum = SPNeed[row][col];
					String *tempStarNeedNumLabelString = String::createWithFormat("%s         X %02d", FontToUTF8("所需"), tempStarNeedNum);
					starNeedNumLabel->setString(tempStarNeedNumLabelString->getCString());
					//刷新技能名字
					char *tempSkillName = skillDetail->getSkillName(row, col);
					skillNameLabel->setString(tempSkillName);

					//单技能成就
					SuccessData::getInstance()->updateIsSkillMax();

					//成就更新
					SuccessData::getInstance()->updateAlldata();

					if (spDecreament != 0)
					{
						//技能动画
						tempUnitSprite->stopAllActions();
						auto blink = Blink::create(1.5f, 2);
						auto changeToVisible = [&](Node * tempNode) {tempNode->setVisible(true); };
						auto seq = Sequence::create(blink, CallFuncN::create(changeToVisible), NULL);
						tempUnitSprite->runAction(seq);
						starAllNumLabel->runAction(seq->clone());
						starNeedNumLabel->runAction(seq->clone());
						auto star0 = static_cast<Sprite *>(rectBG->getChildByName("star0"));
						auto star1 = static_cast<Sprite *>(rectBG->getChildByName("star1"));
						star0->stopAllActions();
						star1->stopAllActions();
						star0->runAction(seq->clone());
						star1->runAction(seq->clone());
					}
					else
					{
						//加音效
						SimpleAudioEngine::getInstance()->playEffect("noCanDoInSkillScene.mp3", false);

					}

				}
				else
				{
					//加音效
					SimpleAudioEngine::getInstance()->playEffect("noCanDoInSkillScene.mp3", false);

				}
			}
			if (1 == option)
			{
				this->removeAllChildrenWithCleanup(true);
				this->removeFromParent();
				SceneM::getInstance()->changeScene(kMenuScene);
			}
		}
		else //detailLayer = false,光标在上;
		{
			detailLayer = true;
			if (0 == option)
			{
				//下方光标出现
				downSelectedRect->setVisible(detailLayer);

				//上方光标消失
				upSelectedRect->setVisible(!detailLayer);

				//刷新所需技能点
				auto tempStarNeedNum = SPNeed[row][col];
				String *tempStarNeedNumLabelString = String::createWithFormat("%s         X %02d", FontToUTF8("所需"), tempStarNeedNum);
				starNeedNumLabel->setString(tempStarNeedNumLabelString->getCString());
				starNeedNumLabel->setVisible(true);
				starNeed->setVisible(true);

				//技能描述
				char *tempSkillDiscribe = skillDetail->getSkillDescribe(row, col);
				skillDiscribeLabel->setString(tempSkillDiscribe);
				skillDiscribeLabel->setVisible(true);

				//技能名称
				char *tempSkillName = skillDetail->getSkillName(row, col);
				skillNameLabel->setString(tempSkillName);
				skillNameLabel->setVisible(true);
			}
			if (1 == option)
			{

				//上方光标消失
				upSelectedRect->setVisible(!detailLayer);

				//出现大圆
				Sprite *bigCircle = static_cast<Sprite *>(this->getChildByName("bigCircle"));
				bigCircle->setVisible(detailLayer);

			}
		}
	}

	if (true == g_keyUp)
	{
		g_keyUp = false;

		//加音效
		SimpleAudioEngine::getInstance()->playEffect("buttonMouseMoveOverInSikllScene.mp3", false);

		if (detailLayer)
		{
			if (0 == option)
			{
				if (0 == row)
				{
					detailLayer = false;
					//下方光标消失
					downSelectedRect->setVisible(detailLayer);

					//上方光标出现
					upSelectedRect->setVisible(!detailLayer);


					//所需星星
					starNeedNumLabel->setVisible(false);
					starNeed->setVisible(false);

					//技能描述
					skillDiscribeLabel->setVisible(false);

					//技能名称
					skillNameLabel->setVisible(false);
				}
				else
				{
					--row;
					while (0 == SPMax[row][col])  //保证有技能
					{
						--col;
					}

					//移动光标
					downSelectedRect->setPosition(Vec2(168 + col * 173, 584 - 126 * row));

					//刷新所需技能点
					auto tempStarNeedNum = SPNeed[row][col];
					String *tempStarNeedNumLabelString = String::createWithFormat("%s         X %02d", FontToUTF8("所需"), tempStarNeedNum);
					starNeedNumLabel->setString(tempStarNeedNumLabelString->getCString());

					//技能描述
					char *tempSkillDiscribe = skillDetail->getSkillDescribe(row, col);
					skillDiscribeLabel->setString(tempSkillDiscribe);

					//技能名称
					char *tempSkillName = skillDetail->getSkillName(row, col);
					skillNameLabel->setString(tempSkillName);
				}
			}
			else  //1==option
			{
				detailLayer = false;
				//上方光标出现
				upSelectedRect->setVisible(!detailLayer);

				//消失大圆
				Sprite *bigCircle = static_cast<Sprite *>(this->getChildByName("bigCircle"));
				bigCircle->setVisible(detailLayer);

			}
		}
	}

	if (true == g_keyDown)
	{
		g_keyDown = false;

		//加音效
		SimpleAudioEngine::getInstance()->playEffect("buttonMouseMoveOverInSikllScene.mp3", false);

		if (detailLayer)
		{
			if (0 == option) 
			{
				if (row <= 2)//row=3时按下无效
				{
					++row;
					while (0 == SPMax[row][col])  //保证有技能
					{
						++col;
					}

					//移动光标
					downSelectedRect->setPosition(Vec2(168 + col * 173, 584 - 126 * row));

					//刷新所需技能点
					auto tempStarNeedNum = SPNeed[row][col];
					String *tempStarNeedNumLabelString = String::createWithFormat("%s         X %02d", FontToUTF8("所需"), tempStarNeedNum);
					starNeedNumLabel->setString(tempStarNeedNumLabelString->getCString());

					//技能描述
					char *tempSkillDiscribe = skillDetail->getSkillDescribe(row, col);
					skillDiscribeLabel->setString(tempSkillDiscribe);

					//技能名称
					char *tempSkillName = skillDetail->getSkillName(row, col);
					skillNameLabel->setString(tempSkillName);
				}
			}
		}
		else //detailLayer ==false
		{
			detailLayer = true;
			if (0 == option)
			{
				//下方光标出现
				upSelectedRect->setVisible(!detailLayer);
				//上方光标消失
				downSelectedRect->setVisible(detailLayer);

				row = 0;
				col = 0;

				//刷新所需技能点
				auto tempStarNeedNum = SPNeed[row][col];
				String *tempStarNeedNumLabelString = String::createWithFormat("%s         X %02d", FontToUTF8("所需"), tempStarNeedNum);
				starNeedNumLabel->setString(tempStarNeedNumLabelString->getCString());
				starNeedNumLabel->setVisible(true);
				starNeed->setVisible(true);

				//技能描述
				char *tempSkillDiscribe = skillDetail->getSkillDescribe(row, col);
				skillDiscribeLabel->setString(tempSkillDiscribe);
				skillDiscribeLabel->setVisible(true);

				//技能名称
				char *tempSkillName = skillDetail->getSkillName(row, col);
				skillNameLabel->setString(tempSkillName);
				skillNameLabel->setVisible(true);
			}
			else  //1==option
			{
				//上方光标消失
				upSelectedRect->setVisible(!detailLayer);

				//出现大圆
				Sprite *bigCircle = static_cast<Sprite *>(this->getChildByName("bigCircle"));
				bigCircle->setVisible(detailLayer);

			}
		}
	}

	if (true == g_keyLeft || true == g_keyRight)
	{
		int move = (true == g_keyLeft) ? (-1) : (1);  //按左键move为-1，右键为1
		g_keyLeft = false;
		g_keyRight = false;

		//加音效
		SimpleAudioEngine::getInstance()->playEffect("buttonMouseMoveOverInSikllScene.mp3", false);

		if (detailLayer)
		{
			if (0 == option)
			{
				do
				{
					col += move;
					if (col < 0)
					{
						col += 5;
					}
					col = col % 5;
				} while (0 == SPMax[row][col]);

				//移动光标
				downSelectedRect->setPosition(Vec2(168 + col * 173, 584 - 126 * row));

				//刷新所需技能点
				auto tempStarNeedNum = SPNeed[row][col];
				String *tempStarNeedNumLabelString = String::createWithFormat("%s         X %02d", FontToUTF8("所需"), tempStarNeedNum);
				starNeedNumLabel->setString(tempStarNeedNumLabelString->getCString());

				//技能描述
				char *tempSkillDiscribe = skillDetail->getSkillDescribe(row, col);
				skillDiscribeLabel->setString(tempSkillDiscribe);

				//技能名称
				char *tempSkillName = skillDetail->getSkillName(row, col);
				skillNameLabel->setString(tempSkillName);

			}
			else //1 ==option
			{

				skinId+=move;
				if (skinId < 0)
				{
					skinId += skinMax;
				}
				if (skinId >= skinMax)
				{
					skinId -= skinMax;
				}
				Sprite *currentSkin = static_cast<Sprite *>(this->getChildByTag(101));
				Label *skinName = static_cast<Label *>(this->getChildByName("skinName"));
				if (skinId < skinNum)
				{
					//更新Id
					dataM->updateSkinId(skinId);
					//修改皮肤
					currentSkin->setTexture(String::createWithFormat("Skin%d_%d.png", (int)heroType, skinId)->getCString());
					//皮肤名称
					skinName->setString(SkillDetail::getInstance()->getSkinName());
				}
				else 
				{
					currentSkin->setTexture(String::createWithFormat("Skin%d_%d_1.png", (int)heroType, skinId)->getCString());
					if (skinId == skinMax - 1)
					{
						skinName->setString(FontToUTF8("完成所有成就开启该皮肤"));
					}
					else
					{
						skinName->setString(FontToUTF8("完成部分成就开启该皮肤"));
					}
				}

			}
		}
		else  //detailLayer == false
		{
			option ^= 1;
			upSelectedRect->setPosition(SCREEN_WIDTH *(0.25 + option*0.5), 703);
			bool isVisited = (bool)option; //isVisited 为false时皮肤页面为false
			{
				//皮肤页面,标签101
				auto currentSkin = this->getChildByTag(101);
				currentSkin->setVisible(isVisited);
				Label *skinName = static_cast<Label *>(this->getChildByName("skinName"));
				skinName->setVisible(isVisited);
				//左箭头，标签100
				auto leftArrow = this->getChildByTag(100);
				leftArrow->setVisible(isVisited);
				//右箭头，标签102
				auto rightArrow = this->getChildByTag(102);
				rightArrow->setVisible(isVisited);

				//技能树初始化
				for (int i = 0; i < 5; ++i)
				{
					for (int j = 0; j < 5; ++j)
					{
						if (0 != SPMax[i][j])
						{
							auto tempUnitSprite = this->getChildByTag(i * 10 + j);
							tempUnitSprite->setVisible(!isVisited);
						}
					}
				}
				//技能页面下方框
				rectBG->setVisible(!isVisited);
			}
		}
	}

	//加音效
	if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		unsigned int randNum = rand() % 6;
		SimpleAudioEngine::getInstance()->playBackgroundMusic(String::createWithFormat("skillScene%d.mp3", randNum)->getCString(), false);
	}

}