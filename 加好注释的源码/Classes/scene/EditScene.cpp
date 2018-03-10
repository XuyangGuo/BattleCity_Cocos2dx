/***********************************************

该类用来制作自定义地图选项页。
包括自定义地图选项页面按钮布局、按键跳转、动画和音效管理

***********************************************/

#include"EditScene.h"
#include"input\keyboardInput.h"
#include"data\Global.h"
#include "data\DataM.h"
#include"SceneM.h"
#include"data\ChineseFonts.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
//加音效,方便复制，故而注释在此
//SimpleAudioEngine::getInstance()->playBackgroundMusic("menu_levelScene.mp3", true);

bool EnterSelectedDifficulty;
bool EnterSelectedMap;


bool EditScene::init() {
	Sprite*background = Sprite::create("LevelBackground.jpg");
	background->setPosition(Vec2(512, 384));
	this->addChild(background);
	readName();
	EnterSelectedDifficulty = false;
	EnterSelectedMap = false;

	for (int i = 0; i < 5; i++) {
		String * spriteName1 = String::createWithFormat("difficulty%d.png", i);
		difficulty[i] = Sprite::create(spriteName1->getCString());
		difficulty[i]->setPosition(Vec2(262, 508 - 50 * i));
		this->addChild(difficulty[i]);
	}

	String*spriteName0 = String::createWithFormat("difficulty%d&%d.png", 0,0);
	difficulty[0]->setTexture(spriteName0->getCString());

	initMapChoice();

	Label*label1 = Label::createWithTTF(FontToUTF8("开 始 游 戏"), "Simple.ttf", 40);
	label1->setPosition(Vec2(150, 35));
	Scale9Sprite*sprite1 = Scale9Sprite::create("Normal.png");
	sprite1->setContentSize(Size(300, 70));
	sprite1->setPosition(Vec2(262, 718));
	sprite1->addChild(label1);
	this->addChild(sprite1);

	Label*label2 = Label::createWithTTF(FontToUTF8("选 择 地 图"), "Simple.ttf", 40);
	label2->setPosition(Vec2(150, 35));
	Scale9Sprite*sprite2 = Scale9Sprite::create("Normal.png");
	sprite2->setContentSize(Size(300, 70));
	sprite2->setPosition(Vec2(262, 633));
	sprite2->addChild(label2);
	this->addChild(sprite2);

	Label*label3 = Label::createWithTTF(FontToUTF8(""), "Simple.ttf", 40);
	label3->setPosition(Vec2(150, 150));
	Scale9Sprite*sprite3 = Scale9Sprite::create("Normal.png");
	sprite3->setContentSize(Size(300, 300));
	sprite3->setPosition(Vec2(262, 433));
	sprite3->addChild(label3);
	this->addChild(sprite3);

	Label*label31 = Label::createWithSystemFont(FontToUTF8("设 置 难 度"), "Simple.ttf", 35);
	label31->setPosition(Vec2(150, 25));
	Scale9Sprite*sprite31 = Scale9Sprite::create("Normal.png");
	sprite31->setPosition(Vec2(262, 558));
	sprite31->setContentSize(Size(300, 50));
	sprite31->addChild(label31);
	this->addChild(sprite31);

	Label*label4 = Label::createWithTTF(FontToUTF8("自定义地图"), "Simple.ttf", 40);
	label4->setPosition(Vec2(150, 35));
	Scale9Sprite*sprite4 = Scale9Sprite::create("Normal.png");
	sprite4->setContentSize(Size(300, 70));
	sprite4->setPosition(Vec2(262, 233));
	sprite4->addChild(label4);
	this->addChild(sprite4);

	Label*label5 = Label::createWithTTF(FontToUTF8("删 除 地 图"), "Simple.ttf", 40);
	label5->setPosition(Vec2(150, 35));
	Scale9Sprite*sprite5 = Scale9Sprite::create("Normal.png");
	sprite5->setContentSize(Size(300, 70));
	sprite5->setPosition(Vec2(262, 148));
	sprite5->addChild(label5);
	this->addChild(sprite5);

	Label*label6 = Label::createWithTTF(FontToUTF8("  返   回  "), "Simple.ttf", 40);
	label6->setPosition(Vec2(150, 35));
	Scale9Sprite*sprite6 = Scale9Sprite::create("Normal.png");
	sprite6->setContentSize(Size(300, 70));
	sprite6->setPosition(Vec2(262, 63));
	sprite6->addChild(label6);
	this->addChild(sprite6);

	//新加
	Scale9Sprite*sprite7 = Scale9Sprite::create("Normal.png");
	sprite7->setContentSize(Size(400, 725));
	sprite7->setPosition(Vec2(762, 390));
	this->addChild(sprite7);


	_arrow = Scale9Sprite::create("SelectedRect.png");
	_arrow->setPosition(Vec2(262, 718));
	_arrow->setContentSize(Size(340, 110));
	this->addChild(_arrow);

	option1 = 5;
	option2 = 4;
	option3 = 0;
	this->setPosition(0, SCREEN_HEIGHT/2);
	auto moveDown = MoveTo::create(2.0f, Vec2(0, 0));
	auto elasticOut = EaseElasticOut::create(moveDown);
	this->runAction(elasticOut);

	this->scheduleUpdate();
	
		//加音效
	unsigned int randNum = rand() % 3;
	SimpleAudioEngine::getInstance()->playBackgroundMusic(String::createWithFormat("editScene%d.mp3",randNum)->getCString(), false);

	return true;
}

void EditScene::update(float dt) {
	moveArrow();
	if (g_keySelect) {
		g_keySelect = false;
		if (EnterSelectedDifficulty) {
			EnterSelectedDifficulty = false;
			option2 = 4;
			_arrow->getSprite()->setTexture("SelectedRect.png");
			_arrow->setPosition(Vec2(262, 558));
			_arrow->setContentSize(Size(340, 90));
			goto ENDIF;
		}

		if (EnterSelectedMap) {
			EnterSelectedMap = false;
			option1 = 5;
			option3 = 0;
			_arrow->getSprite()->setTexture("SelectedRect.png");
			_arrow->setPosition(Vec2(262, 718));
			_arrow->setContentSize(Size(340, 110));
			goto ENDIF;
		}
		this->unscheduleUpdate();
		removeAllChildren();
		SceneM::getInstance()->changeScene(kLevelScene);
		return;
	}
	ENDIF:
	//(0,2)
	if (g_keyStart) {
		g_keyStart = false;
		if (EnterSelectedMap == false && option1 == 2) {
			this->unscheduleUpdate();
			removeAllChildren();
			SceneM::getInstance()->changeScene(kEditorScene);
			return;
		}
		
		if (EnterSelectedMap == false && option1 == 0) {
			this->unscheduleUpdate();
			removeAllChildren();
			SceneM::getInstance()->changeScene(kLevelScene);
			return;
		}

		if (option1 == 5 && mapNumber >= 0) {
			DataM::getInstance()->setMapName(mapNames[mapNumber]);
			DataM::getInstance()->setEnemyDifficulty(enemyDifficulty);
			this->unscheduleUpdate();
			removeAllChildren();
			SceneM::getInstance()->changeScene(kSelectHeroScene);
		}

		//放最后
		if (EnterSelectedMap == false && option1 == 1) {
			_arrow->getSprite()->setTexture("shadowSelector.png");
			_arrow->setPosition(Vec2(762, 724));
			_arrow->setContentSize(Size(400, 54));
			EnterSelectedMap = true;
			return;
		}

		if (EnterSelectedMap == false && option1 == 4) {
			if (mapNumMax == 0)
			{

			}
			else
			{
				_arrow->getSprite()->setTexture("shadowSelector.png");
				_arrow->setPosition(Vec2(762, 724));
				_arrow->setContentSize(Size(400, 54));
				EnterSelectedMap = true;
				return;
			}
		}

		if (option1 == 3 && EnterSelectedDifficulty == true) {
			EnterSelectedDifficulty = false;

			for (int j = 0; j < 5; j++) {
				String * spriteName3 = String::createWithFormat("difficulty%d.png", j);
				difficulty[j]->setTexture(spriteName3->getCString());
			}
			_arrow->getSprite()->setTexture("SelectedRect.png");
			_arrow->setPosition(Vec2(262, 558));
			_arrow->setContentSize(Size(340, 90));

			String * spriteName2 = String::createWithFormat("difficulty%d&%d.png", (4-option2),(4-option2));
			difficulty[4-option2]->setTexture(spriteName2->getCString());

			enemyDifficulty = 4-option2;
			option2 = 4;
			return;
		}

		if (option1 == 3 && EnterSelectedDifficulty == false) {
			_arrow->getSprite()->setTexture("shadowSelector.png");
			_arrow->setPosition(Vec2(262, 508));
			_arrow->setContentSize(Size(300, 50));
			EnterSelectedDifficulty = true;
			return;
		}

		if (EnterSelectedDifficulty == false && EnterSelectedMap == true) {
			EnterSelectedMap = false;
			if (option1 == 1 && mapNumMax>0) {
				auto p = mapNames.begin();
				for (int i = 0; i < option3; i++)	p++;
				mapNames.erase(p);
				mapNumMax -= 1;
				mapNumber = -1;
				saveName();
				for (auto mName : mapChoice)
					mName->removeFromParent();
				mapChoice.clear();
				initMapChoice();
			}
			if (option1 == 4) {
				mapNumber = option3;
				updateMapChoice();
			}
			option1 = 5;
			option3 = 0;
			_arrow->getSprite()->setTexture("SelectedRect.png");
			_arrow->setPosition(Vec2(262, 718));
			_arrow->setContentSize(Size(340, 110));
			return;
		}
	}
	
		if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		//加音效
		unsigned int randNum = rand() % 3;
		SimpleAudioEngine::getInstance()->playBackgroundMusic(String::createWithFormat("editScene%d.mp3", randNum)->getCString(), false);
	}

	
}

Vec2 EditScene::getPosition(int x, int y) {
	switch (x * 10 + y) {
	case 0:
		return Vec2(262, 63);
		break;
	case 1:
		return Vec2(262, 163);
		break;
	case 2:
		return Vec2(262, 233);
		break;
	case 3:
		return Vec2(262, 433);
		break;
	case 4:
		return Vec2(262, 648);
		break;
	case 5:
		return Vec2(262, 718);
		break;
	case 10:
		return Vec2(762, 390);
		break;
	default:
		break;
	}
}

void EditScene::moveArrow() {
	if (g_keyRight) {
		g_keyRight = false;
	}
	if (g_keyLeft) {
		g_keyLeft = false;
	}
	if (g_keyDown) {
		g_keyDown = false;
		if (EnterSelectedDifficulty == false && EnterSelectedMap == false) {
			if (--option1 < 0) {
				option1 += 6;
			}
			if (option1 < 3) {
				_arrow->setContentSize(Size(340, 110));
				_arrow->setPosition(Vec2(262, 63 + option1 * 85));
			}
			if (option1 == 3) {
				_arrow->setContentSize(Size(340, 90));
				_arrow->setPosition(Vec2(262, 558));
			}
			if (option1 > 3) {
				_arrow->setContentSize(Size(340, 110));
				_arrow->setPosition(Vec2(262, 293 + option1 * 85));
			}
		}
		if (EnterSelectedDifficulty == true && EnterSelectedMap == false) {
			if (--option2 < 0) {
				option2 += 5;
			}
			_arrow->setContentSize(Size(300, 50));
			_arrow->setPosition(Vec2(262, 308 + option2 * 50));
		}
		if (EnterSelectedDifficulty == false && EnterSelectedMap == true) {
			option3 = (option3 + 1) % mapNumMax;
			_arrow->setContentSize(Size(400, 54));
			_arrow->setPosition(Vec2(762, mapChoice[option3]->getPosition().y + 6));
		}
	}
	if (g_keyUp) {
		g_keyUp = false;
		if (EnterSelectedDifficulty == false && EnterSelectedMap == false) {
			option1 = (option1 + 1) % 6;
			if (option1 < 3) {
				_arrow->setContentSize(Size(340, 110));
				_arrow->setPosition(Vec2(262, 63 + option1 * 85));
			}
			if (option1 == 3) {
				_arrow->setContentSize(Size(340, 90));
				_arrow->setPosition(Vec2(262, 558));
			}
			if (option1 > 3) {
				_arrow->setContentSize(Size(340, 110));
				_arrow->setPosition(Vec2(262, 293 + option1 * 85));
			}
		}
		if (EnterSelectedDifficulty == true && EnterSelectedMap == false) {
			option2 = (option2 + 1) % 5;
			_arrow->setContentSize(Size(300, 50));
			_arrow->setPosition(Vec2(262, 308 + option2 * 50));
		}
		if (EnterSelectedDifficulty == false && EnterSelectedMap == true) {
			if (--option3 < 0) {
				option3 += mapNumMax;
			}
			_arrow->setContentSize(Size(400, 54));
			_arrow->setPosition(Vec2(762, mapChoice[option3]->getPosition().y + 6));
		}
	}

}
void  EditScene::readName() {
	std::ifstream in("costumMap/mapNames.txt");
	in >> mapNumMax;
	std::string mapname;
	for (int i = 0; i < mapNumMax; i++) {
		in >> mapname;
		mapNames.push_back(mapname);
	}
}
void EditScene::saveName() {
	std::ofstream out("costumMap/mapNames.txt");
	out << mapNumMax << std::endl;
	for (auto name : mapNames)
		out << name << ' ';
	out.close();

}

void EditScene::initMapChoice() {
	for (int i = 0; i < mapNumMax; i++) {
		mapChoice.push_back(Sprite::create("mapItem.png"));
		mapChoice.back()->setPosition(Vec2(762, 716 - i * 54));
		this->addChild(mapChoice.back());
		auto label = Label::createWithTTF(FontToUTF8(mapNames[i].c_str()), "Simple.ttf", 40);
		mapChoice.back()->addChild(label, 1, 10);
		label->setAnchorPoint(Vec2(0, 0.5));
		label->setPosition(30, 27);
	}
}

void EditScene::updateMapChoice() {
	if (mapNumber < 0) {
		for (auto map : mapChoice) {
			map->getChildByTag(10)->setColor(Color3B(255, 255, 255));
		}
	}
	else {
		for (auto map : mapChoice) 
			map->getChildByTag(10)->setColor(Color3B(255, 255, 255));
			mapChoice[mapNumber]->getChildByTag(10)->setColor(Color3B(0, 0, 0));
	}
}