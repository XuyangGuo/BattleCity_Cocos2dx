/***********************************************

该类用来制作自定义地图，是自定义地图内页的功能类。
包括自定义地图内页的场布局、按键移动、后台管理

***********************************************/

#pragma once
#include "input\keyboardInput.h"
#include "cocos2d.h"
#include "data\Global.h"
#include "ui\UIScale9Sprite.h"
#include "ui\CocosGUI.h"
#include "EditScene.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace ui;

USING_NS_CC;
enum mapType // 地图元素类型 
{
	mLAND,	// 地       0
	mBRICK,	// 砖		1
	mGRASS,  // 草		2
	mWATER,  // 水		3
	mGRID1,  // 铁1 左上	4
	mGRID2,  // 铁2 右上	5
	mGRID3,  // 铁3 左下	6
	mGRID4,	// 铁4 右下	7
};

class EditorScene :public Layer
{
public:
	CREATE_FUNC(EditorScene);
	virtual bool init();
	void moveSelector1();	//移动在地图编辑区内的选框
	void moveSelector2();	//移动在菜单区内的选框
	void update(float dt);

private:
	void bgInit();//初始化画布
	Vec2 getButtonPos(int x, int y);//根据按钮的相对位置，得到绝对位置
	String getSpriteName(int type);//地图元素的选择器
	char getAChar();//文件存储的输入装置
	void saveName();//保存文件

	void  readName();//读取文件

	LayerColor *_bg;//画布
	Scale9Sprite *selector;//菜单栏的光标
	Sprite* selector2;//画布内的光标
	mapType type;//地图元素的分类
	Vector<Sprite *> cell;//地图元素的UI呈现
	Vector<Scale9Sprite*> cell9;//菜单元素的UI呈现
	Sprite*  map[MAP_ROW][MAP_COL];//画布单元UI
	int  intMap[MAP_ROW][MAP_COL] = { 0 };//文件存储的地图
	/* 各种菜单以及其是否被激活的指示器*/
	Sprite* backMenu;//
	Sprite* saveMenu;
	Sprite* nameMenu;
	int backMenuNum=0;
	int saveMenuNum=0;
	int nameMenuNum=0;
	Label* inputLabel;
	Sprite* indentifier;

	/*坐标相关的参数*/
	Vec2 pos;
	Vec2 oldpos=getPos(0,0);
	int _x = 0;
	int _y = 0;
	/*输入法相关参数*/
	bool isInputing = false;
	char name[31] = { '\0' };
	int index = 0;
	/*地图相关参数*/
	int mapNumMax;
	std::vector<std::string> mapNames;
};