/***********************************************

该类用来制作自定义地图，是自定义地图内页的功能类。
包括自定义地图内页的场布局、按键移动、后台管理

***********************************************/

#include "EditorScene.h"
#include <fstream>
#include "data\ChineseFonts.h"
#include "SceneM.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
//加音效,方便复制，故而注释在此
//SimpleAudioEngine::getInstance()->playBackgroundMusic("menu_levelScene.mp3", true);


bool EditorScene::init() {
	bgInit();
	pos = (getButtonPos(0,1));
	//init selector
	selector = Scale9Sprite::create("SelectedRect.png");
	selector->setContentSize(Size(48, 48));
	selector->setPosition(pos);
	this->addChild(selector, 9);
	selector2 = Sprite::create();
	this->addChild(selector2, 10);
	selector2->setVisible(false);

	readName();

	// init backmenu
	backMenu = Sprite::create("backmenu1.png");
	backMenu->setPosition(1024 / 2, 768 / 2);
	this->addChild(backMenu, 11);
	backMenu->setVisible(false);
	backMenuNum = 0;
	auto label = Label::createWithTTF(FontToUTF8("确定返回吗？"), "Simple.TTF", 45);
	backMenu->addChild(label);
	label->setPosition(1024 / 2, 768 / 2 + 50);
	//init savemenu
	saveMenu = Sprite::create("backmenu1.png");
	saveMenu->setPosition(1024 / 2, 768 / 2);
	this->addChild(saveMenu, 11);
	saveMenu->setVisible(false);
	saveMenuNum = 0;
	label = Label::createWithTTF(FontToUTF8("保存后即返回主菜\n单，确定返回吗？"), "Simple.TTF", 45);
	saveMenu->addChild(label);
	label->setPosition(1024 / 2, 768 / 2 + 50);
	//init change name menu
	nameMenu = Sprite::create("namemenu.png");
	nameMenu->setPosition(1024 / 2, 768 / 2);
	this->addChild(nameMenu, 11);
	nameMenu->setVisible(false);
	nameMenuNum = 0;
	auto inputPosition = Sprite::create("inputPosition.png");
	nameMenu->addChild(inputPosition, 0);
	inputPosition->setPosition(1024 / 2, 768 / 2+50);
	inputLabel = Label::createWithTTF("", "Simple.ttf", 40);
	inputLabel->setColor(Color3B(0, 0, 0));
	nameMenu->addChild(inputLabel,1);
	inputLabel -> setAnchorPoint(Vec2(0,0.5));
	inputLabel->setPosition(327+10, 768 / 2+50);



	//inputLabel->setAnchorPoint(Vec2(0.5, 0.5));
	//indentifier = Sprite::create("indentifier.png");
	//this->addChild(indentifier,3);
	//indentifier->setPosition(inputLabel->getPosition().x*2, inputLabel->getPosition().y);
	//log("%f,%f", inputLabel->getPosition().x * 2, inputLabel->getPosition().y);

	//EditBox* text = EditBox::create(Size(200, 200), "grass.png");
	//text->setPosition(Vec2(500, 500));
	//this->addChild(text);
	//cocos2d::Director::getInstance()->getOpenGLView()->handleTouchesBegin(1,1,);

	intMap[1][13] = 8;
	intMap[1][14] = intMap[0][13] = intMap[0][14] = 9;

	type = mLAND;

	this->scheduleUpdate();
	return true;
}

Vec2 EditorScene::getButtonPos(int x, int y) {
	switch (x*10+y)
	{
	case 1:
		return Vec2(96 + 24 + 80 * 0, 22 + 24 + 48);
	case 11:
		return Vec2(96 + 24 + 80 * 1, 22 + 24 + 48);
	case 21:
		return Vec2(96 + 24 + 80 * 2, 22 + 24 + 48);
	case 0:
		return Vec2(96 + 24 + 80 * 0, 11 + 24);
	case 10:
		return Vec2(96 + 24 + 80 * 1, 11 + 24);
	case 20:
		return Vec2(96 + 24 + 80 * 2, 11 + 24);
	case 30:
		return Vec2(96 + 24 + 80 * 3, 11 + 24);
	case 31:
		return Vec2(96 + 24 + 80 * 3, 22 + 24 + 48);
	case 50:
		return Vec2(1024 - 64 * 2 - 80, 11 + 24);
	case 40:
		return Vec2(1024 - 64 * 3 - 80 - 160, 11 + 24);
	case 41:
		return Vec2(1024 - 64 * 3 - 80 - 160, 22 + 24 + 48);
	case 51:
		return Vec2(1024 - 64 * 2 - 80, 22 + 24 + 48);
	}
}

void EditorScene::bgInit() {
	_bg = LayerColor::create(Color4B(254, 184, 137, 255));
	_bg->setPosition(Vec2::ZERO);
	this->addChild(_bg, 0);
	// 边框
	for (int i = 0; i < 16; ++i)
	{
		Sprite* borderSprite1 = Sprite::create("Border.png");
		borderSprite1->setPosition(Vec2(i * 64 + 32, SCREEN_HEIGHT - 32));
		this->addChild(borderSprite1, 1);
	}

	for (int i = 0; i < 11; ++i)
	{
		Sprite* borderSprite2 = Sprite::create("Border.png");
		borderSprite2->setPosition(Vec2(32, i * 64 + 32));
		this->addChild(borderSprite2, 1);
		Sprite* borderSprite3 = Sprite::create("Border.png");
		borderSprite3->setPosition(Vec2(SCREEN_WIDTH - 32, i * 64 + 32));
		this->addChild(borderSprite3, 1);
	}
	//editor at bottom
	Sprite* bottom = Sprite::create("editorBottom.png");
	bottom->setAnchorPoint(Vec2(0, 0));
	this->addChild(bottom,2);
	bottom->setPosition(64, 0);

	for (auto i = MAP_ROW - 1; i >= 0; --i)
	{
		for (auto j = 0; j < MAP_COL; j++)
		{
			map[i][j] = Sprite::create();
			map[i][j]->setPosition(getPos(i, j));
			this->addChild(map[i][j]);
		}
	}

	auto home = Sprite::create("Home1.png");
	home->setPosition(getPos(1, 13).x+16, getPos(1, 13).y - 16);
	this->addChild(home);

	cell.pushBack(Sprite::create("brick.png"));   //(0,1)
	cell.back()->setPosition(getButtonPos(0,1));
	cell.back()->setScale(1.5);
	cell9.pushBack(Scale9Sprite::create("editElement.png"));
	cell9.back()->setPosition(getButtonPos(0, 1));
	cell9.back()->setContentSize(Size(48, 48));

	cell.pushBack(Sprite::create("grass.png"));   //(1,1)
	cell.back()->setPosition(getButtonPos(1, 1));
	cell.back()->setScale(1.5);
	cell9.pushBack(Scale9Sprite::create("editElement.png"));
	cell9.back()->setPosition(getButtonPos(1, 1));
	cell9.back()->setContentSize(Size(48, 48));

	cell.pushBack(Sprite::create("Water1.png"));   //(2,1)
	cell.back()->setPosition(getButtonPos(2, 1));
	cell.back()->setScale(1.5);
	cell9.pushBack(Scale9Sprite::create("editElement.png"));
	cell9.back()->setPosition(getButtonPos(2, 1));
	cell9.back()->setContentSize(Size(48, 48));

	cell.pushBack(Sprite::create("Grid1.png"));	  //(0,0)
	cell.back()->setPosition(getButtonPos(0, 0));
	cell.back()->setScale(1.5);
	cell9.pushBack(Scale9Sprite::create("editElement.png"));
	cell9.back()->setPosition(getButtonPos(0, 0));
	cell9.back()->setContentSize(Size(48, 48));

	cell.pushBack(Sprite::create("Grid2.png"));   //(1,0)
	cell.back()->setPosition(getButtonPos(1, 0));
	cell.back()->setScale(1.5);
	cell9.pushBack(Scale9Sprite::create("editElement.png"));
	cell9.back()->setPosition(getButtonPos(1, 0));
	cell9.back()->setContentSize(Size(48, 48));

	cell.pushBack(Sprite::create("Grid3.png"));   //(2,0)
	cell.back()->setPosition(getButtonPos(2, 0));
	cell.back()->setScale(1.5);
	cell9.pushBack(Scale9Sprite::create("editElement.png"));
	cell9.back()->setPosition(getButtonPos(2, 0));
	cell9.back()->setContentSize(Size(48, 48));

	cell.pushBack(Sprite::create("Grid4.png"));   //(3,0)
	cell.back()->setPosition(getButtonPos(3, 0));
	cell.back()->setScale(1.5);
	cell9.pushBack(Scale9Sprite::create("editElement.png"));
	cell9.back()->setPosition(getButtonPos(3, 0));
	cell9.back()->setContentSize(Size(48, 48));

	cell.pushBack(Sprite::create("eraser.png"));   //(3,1)
	cell.back()->setPosition(getButtonPos(3, 1));
	cell.back()->setScale(1.5);
	cell9.pushBack(Scale9Sprite::create("editElement.png"));
	cell9.back()->setPosition(getButtonPos(3, 1));
	cell9.back()->setContentSize(Size(48, 48));
	
	cell9.pushBack(Scale9Sprite::create("Normal.png"));		//(5,0)
	cell9.back()->setPosition(getButtonPos(5, 0));
	cell9.back()->setContentSize(Size(160, 48));
	auto label = Label::createWithTTF(FontToUTF8("返  回"), "Simple.TTF", 32);
	label->setPosition(80, 24);
	cell9.back()->addChild(label);

	cell9.pushBack(Scale9Sprite::create("Normal.png"));		//(4,0)
	cell9.back()->setPosition(getButtonPos(4, 0));
	cell9.back()->setContentSize(Size(200, 48));
	label = Label::createWithTTF(FontToUTF8("重命名地图"), "Simple.TTF", 32);
	label->setPosition(100, 24);
	cell9.back()->addChild(label);

	cell9.pushBack(Scale9Sprite::create("Normal.png"));		//(4,1)
	cell9.back()->setPosition(getButtonPos(4, 1));
	cell9.back()->setContentSize(Size(200, 48));
	label = Label::createWithTTF(FontToUTF8("清空画布"), "Simple.TTF", 32);
	label->setPosition(100, 24);
	cell9.back()->addChild(label);

	cell9.pushBack(Scale9Sprite::create("Normal.png"));		//(5,1)
	cell9.back()->setPosition(getButtonPos(5, 1));
	cell9.back()->setContentSize(Size(160, 48));
	label = Label::createWithTTF(FontToUTF8("保  存"), "Simple.TTF", 32);
	label->setPosition(80, 24);
	cell9.back()->addChild(label);

	for (auto p = cell.begin(); p != cell.end();p++)
		this->addChild(*p,3);
	for (auto p = cell9.begin(); p != cell9.end(); p++)
		this->addChild(*p,4);
}
	

void EditorScene::moveSelector1() {
	if (g_keyUp) {
		g_keyUp = false;
		if (pos.y == getPos(17, 1).y)	pos.y = getPos(0, 1).y;
		else pos.y += 32;
		//避开home
		if (getRowNumberFromPosition(pos.y) == 0 && (getColNumberFromPosition(pos.x) == 13 || getColNumberFromPosition(pos.x) == 14))	pos.y += 64;
	}
	if (g_keyDown) {
		g_keyDown = false;
		if (pos.y == getPos(0, 1).y)	pos.y = getPos(17, 1).y;
		else pos.y -= 32;
		//避开home
		if (getRowNumberFromPosition(pos.y) == 1 && (getColNumberFromPosition(pos.x) == 13 || getColNumberFromPosition(pos.x) == 14))	pos.y = getPos(17,1).y;
	}
	if (g_keyLeft) {
		g_keyLeft = false;
		if (pos.x == getPos(1, 0).x)	pos.x = getPos(1, 27).x;
		else pos.x -= 32;
		//避开home
		if ((getRowNumberFromPosition(pos.y) == 0 || getRowNumberFromPosition(pos.y) == 1) && getColNumberFromPosition(pos.x) == 14)	pos.x -= 64;
	}
	if (g_keyRight) {
		g_keyRight = false;
		if (pos.x == getPos(1, 27).x)	pos.x = getPos(1, 0).x;
		else pos.x += 32;
		//避开home
		if ((getRowNumberFromPosition(pos.y) == 0 || getRowNumberFromPosition(pos.y) == 1) && getColNumberFromPosition(pos.x) == 13)	pos.x += 64;
	}

	if (g_keySelect) {
		g_keySelect = false;
		//selector-(1.5);
		oldpos = pos;
		pos = Vec2(getButtonPos(0,0));
		_y = _x = 0;
		selector2->setVisible(false);
		selector->setVisible(true);
		selector->setContentSize(Size(48+40, 48+40));
	}

}

void EditorScene::moveSelector2() {
	if (g_keyUp) {
		g_keyUp = false;
		_y ^= 1;
	}
	if (g_keyDown) {
		g_keyDown = false;
		_y ^= 1;
	}
	if (g_keyLeft) {
		g_keyLeft = false;
		if (_x == 0)	_x = 5;
		else _x -= 1;
	}
	if (g_keyRight) {
		g_keyRight = false;
		if (_x == 5)	_x = 0;
		else _x += 1;
	}

	if (_x == 4)		selector->setContentSize(Size(200+40, 48+40));
	if (_x == 5)		selector->setContentSize(Size(160+40, 48+40));
	if (_x < 4)		selector->setContentSize(Size(48+40, 48+40));

	pos = getButtonPos(_x, _y);
}

void EditorScene::update(float dt) {
	if (isInputing) {
		char c=getAChar();
		if (c == '~')	goto SKIPIF;
		if (c == '|')
			if (index != 0) name[--index] = '\0';
			else;
		else if (index != 31)	name[index++] = c;
		log("index:%d", index);
		log(c);
		inputLabel->setString(name);
	}
	SKIPIF:
	if (pos.y > 128 && (backMenuNum | saveMenuNum | nameMenuNum)==0) {
		moveSelector1();
		if (g_keyStart) {
			g_keyStart = false;
			if (type!=mLAND)
				map[getRowNumberFromPosition(pos.y)][getColNumberFromPosition(pos.x)]->setTexture(getSpriteName(type).getCString());
			else map[getRowNumberFromPosition(pos.y)][getColNumberFromPosition(pos.x)]->setTexture("");
			intMap[getRowNumberFromPosition(pos.y)][getColNumberFromPosition(pos.x)] = int(type);
		}
	}

	if (pos.y < 128 && (backMenuNum | saveMenuNum | nameMenuNum) == 0) {
		moveSelector2();

		if (g_keyStart && _x<=3) {
			g_keyStart = false;
			if (_y == 0)	type = (mapType)(_x + 4);
			if (_y == 1 && _x != 3)	type = (mapType)(_x + 1);
			if (_y == 1 && _x == 3) type = mLAND;
			pos = oldpos;
			selector->setVisible(false);
			selector2->setVisible(true);
			selector2->setTexture(getSpriteName(type).getCString());
			selector2->setOpacity(150);
		}

		if (g_keyStart && _x == 5 && _y == 0) {
			g_keyStart = false;
			backMenu->setVisible(true);
			backMenuNum = 2;
			backMenu->setTexture(String::createWithFormat("backmenu%d.png", backMenuNum)->getCString());
		}

		if (g_keyStart && _x == 5 && _y == 1) {
			g_keyStart = false;
			saveMenu->setVisible(true);
			saveMenuNum = 1;
			saveMenu->setTexture(String::createWithFormat("backmenu%d.png", saveMenuNum)->getCString());
		}

		if (g_keyStart && _x == 4 && _y == 0) {
			g_keyStart = false;
			nameMenu->setVisible(true);
			nameMenuNum = 1;
			isInputing = true;
		}

		if (g_keyStart && _x == 4 && _y == 1) {
			g_keyStart = false;
			for (auto i = MAP_ROW - 1; i >= 0; --i)	{
				for (auto j = 0; j < MAP_COL; j++) {
					intMap[i][j] = 0;
					map[i][j]->setTexture("");
				}

			}
		}
	}

	selector2->setPosition(pos);
	selector->setPosition(pos);
	//deal backmenu
	if (backMenuNum) {
		if (g_keyLeft || g_keyRight) {
			g_keyLeft = g_keyRight = false;
			backMenuNum ^= 3;
			backMenu->setTexture(String::createWithFormat("backmenu%d.png", backMenuNum)->getCString());
		}
		if (g_keyStart) {
			g_keyStart = false;
			switch (backMenuNum)
			{
			case 1:
				this->unscheduleUpdate();
				removeAllChildren();
				SceneM::getInstance()->changeScene(kCustomScene);
				break;
			case 2:
				backMenu->setVisible(false);
				backMenuNum = 0;
				break;
			}
		}
	}
	//deal savemenu
	if (saveMenuNum) {
		if (g_keyLeft || g_keyRight) {
			g_keyLeft = g_keyRight = false;
			saveMenuNum ^= 3;
			saveMenu->setTexture(String::createWithFormat("backmenu%d.png", saveMenuNum)->getCString());
		}
		if (g_keyStart) {
			g_keyStart = false;
			switch (saveMenuNum)
			{
			case 1: {

				mapNumMax++;
				std::string sname = std::string(name);
				if (sname == "")	sname = std::string(String::createWithFormat("new_map%d", mapNumMax)->getCString());
				std::ofstream out(String::createWithFormat("costumMap/%s.txt", sname.c_str())->getCString());
				for (auto i = MAP_ROW - 1; i >= 0; --i) {
					for (auto j = 0; j < MAP_COL; j++)	out << intMap[i][j] << ' ';
					out << std::endl;
				}
				out.close();
				mapNames.push_back(sname);
				saveName();
				this->unscheduleUpdate();
				removeAllChildren();
				SceneM::getInstance()->changeScene(kCustomScene);
				break;
			}
			case 2:
				saveMenu->setVisible(false);
				saveMenuNum = 0;
				break;
			}
		}
	}
	//deal namemenu
	if (nameMenuNum) {
		if(g_keyStart){
			g_keyStart = false;
			nameMenuNum = 0;
			nameMenu->setVisible(false);
			isInputing = false;
		}
	}

	if (g_keySelect) {
		g_keySelect = false;
		if (nameMenuNum !=0) {
			nameMenuNum = 0;
			nameMenu->setVisible(false);
			isInputing = false;
			return;
		}
		if (saveMenuNum !=0) {
			saveMenu->setVisible(false);
			saveMenuNum = 0;
			return;
		}
		backMenuNum = 2;
		backMenu->setVisible(true);
		backMenu->setTexture(String::createWithFormat("backmenu%d.png", backMenuNum)->getCString());
	}
	
		if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		//加音效
		unsigned int randNum = rand() % 3;
		SimpleAudioEngine::getInstance()->playBackgroundMusic(String::createWithFormat("editScene%d.mp3", randNum)->getCString(), false);
	}

	
}

String EditorScene::getSpriteName(int type)
{
	String name;
	switch (type & 0x0f)
	{
	case mLAND:
		name = "eraser.png";
		break;
	case mGRID1:
		name = "Grid1.png";
		break;
	case mGRID2:
		name = "Grid2.png";
		break;
	case mGRID3:
		name = "Grid3.png";
		break;
	case mGRID4:
		name = "Grid4.png";
		break;
	case mGRASS:
		name = "Grass.png";
		break;
	case mBRICK:
		{int t = getRowNumberFromPosition(pos.y) + getColNumberFromPosition(pos.x);
		t %= 2;
		if (t == 0)	name = "Brick0.png";
		else name = "Brick1.png"; }
		break;
	case mWATER:
		name = "Water1.png";
		break;
	}
	return name;
}

char EditorScene::getAChar() {
	if (g_keyLeft == true) {
		g_keyLeft = false;
		if (g_keyCAPSLOCK == true)	return 'A';
		else return 'a';
	}
	if (g_key_B == true) {
		g_key_B = false;
		if (g_keyCAPSLOCK == true)	return 'B';
		else return 'b';
	}
	if (g_keyC == true) {
		g_keyC = false;
		if (g_keyCAPSLOCK == true)	return 'C';
		else return 'c';
	}
	if (g_keyRight == true) {
		g_keyRight = false;
		if (g_keyCAPSLOCK == true)	return 'D';
		else return 'd';
	}
	if (g_keyE == true) {
		g_keyE = false;
		if (g_keyCAPSLOCK == true)	return 'E';
		else return 'e';
	}
	if (g_keyF == true) {
		g_keyF = false;
		if (g_keyCAPSLOCK == true)	return 'F';
		else return 'f';
	}
	if (g_keyG == true) {
		g_keyG = false;
		if (g_keyCAPSLOCK == true)	return 'G';
		else return 'g';
	}
	if (g_keyH == true) {
		g_keyH = false;
		if (g_keyCAPSLOCK == true)	return 'H';
		else return 'h';
	}
	if (g_keyI == true) {
		g_keyI = false;
		if (g_keyCAPSLOCK == true)	return 'I';
		else return 'i';
	}
	if (g_keyA == true) {
		g_keyA = false;
		if (g_keyCAPSLOCK == true)	return 'J';
		else return 'j';
	}
	if (g_keyB == true) {
		g_keyB = false;
		if (g_keyCAPSLOCK == true)	return 'K';
		else return 'k';
	}
	if (g_keyL == true) {
		g_keyL = false;
		if (g_keyCAPSLOCK == true)	return 'L';
		else return 'l';
	}
	if (g_keyM == true) {
		g_keyM = false;
		if (g_keyCAPSLOCK == true)	return 'M';
		else return 'm';
	}
	if (g_keyN == true) {
		g_keyN = false;
		if (g_keyCAPSLOCK == true)	return 'N';
		else return 'n';
	}
	if (g_keyO == true) {
		g_keyO = false;
		if (g_keyCAPSLOCK == true)	return 'O';
		else return 'o';
	}
	if (g_keyP == true) {
		g_keyP = false;
		if (g_keyCAPSLOCK == true)	return 'P';
		else return 'p';
	}
	if (g_keyQ == true) {
		g_keyQ = false;
		if (g_keyCAPSLOCK == true)	return 'Q';
		else return 'q';
	}
	if (g_keyR == true) {
		g_keyR = false;
		if (g_keyCAPSLOCK == true)	return 'R';
		else return 'r';
	}
	if (g_keyDown == true) {
		g_keyDown = false;
		if (g_keyCAPSLOCK == true)	return 'S';
		else return 's';
	}
	if (g_keyT == true) {
		g_keyT = false;
		if (g_keyCAPSLOCK == true)	return 'T';
		else return 't';
	}
	if (g_keyU == true) {
		g_keyU = false;
		if (g_keyCAPSLOCK == true)	return 'U';
		else return 'u';
	}
	if (g_keyV == true) {
		g_keyV = false;
		if (g_keyCAPSLOCK == true)	return 'V';
		else return 'v';
	}
	if (g_keyUp == true) {
		g_keyUp = false;
		if (g_keyCAPSLOCK == true)	return 'W';
		else return 'w';
	}
	if (g_keyX == true) {
		g_keyX = false;
		if (g_keyCAPSLOCK == true)	return 'X';
		else return 'x';
	}
	if (g_keyY == true) {
		g_keyY = false;
		if (g_keyCAPSLOCK == true)	return 'Y';
		else return 'y';
	}
	if (g_keyZ == true) {
		g_keyZ = false;
		if (g_keyCAPSLOCK == true)	return 'Z';
		else return 'z';
	}
	if (g_keyBACK == true) {
		g_keyBACK = false;
		return '|';
	}
	if (g_key0 == true) {
		g_key0 = false;
		return '0';
	}
	if (g_key1 == true) {
		g_key1 = false;
		return '1';
	}
	if (g_key2 == true) {
		g_key2 = false;
		return '2';
	}
	if (g_key3 == true) {
		g_key3 = false;
		return '3';
	}
	if (g_key4 == true) {
		g_key4 = false;
		return '4';
	}
	if (g_key5 == true) {
		g_key5 = false;
		return '5';
	}
	if (g_key6 == true) {
		g_key6 = false;
		return '6';
	}
	if (g_key7 == true) {
		g_key7 = false;
		return '7';
	}
	if (g_key8 == true) {
		g_key8 = false;
		return '8';
	}
	if (g_key9 == true) {
		g_key9 = false;
		return '9';
	}
	return'~';
}


void EditorScene::saveName() {
	std::ofstream out("costumMap/mapNames.txt");
	out << mapNumMax << std::endl;
	for (auto name : mapNames)
		out << name << ' ';
	out.close();

}

void  EditorScene::readName() {
	std::ifstream in("costumMap/mapNames.txt");
	in >> mapNumMax;
	std::string mapname;
	for (int i = 0; i < mapNumMax; i++) {
		in >> mapname;
		mapNames.push_back(mapname);
	}
}