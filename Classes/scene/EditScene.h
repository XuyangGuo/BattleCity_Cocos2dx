/***********************************************

该类用来制作自定义地图选项页。
包括自定义地图选项页面按钮布局、按键跳转、动画和音效管理

***********************************************/

#pragma once
#include"cocos2d.h"
#include<iostream>
#include "ui\UIScale9Sprite.h"//cocos2d的九宫精灵类
#include <vector>//向量容器库
#include <fstream>//c++的文件读写库

USING_NS_CC;
using namespace ui;


class EditScene :public Layer {
public:
	CREATE_FUNC(EditScene);
	virtual bool init();
	Vec2 getPosition(int x, int y);//根据页面按钮的相对坐标，返回它在父节点的绝对位置
private:
	void update(float dt);//帧刷新
	void moveArrow();//光标移动
	void readName();//文件读取
	void saveName();//文件储存
	void initMapChoice();//初始化文件储存的UI系统
	void updateMapChoice();//文件储存的UI系统的更新

	int mapNumMax = 0;//当前储存的地图数
	Scale9Sprite*_arrow;//光标
	/* 指示按钮间相对坐标的参数*/
	int option1;//左半边按钮的相对位置
	int option2;//右半边按钮的相对位置
	int option3;//难度选择按钮
	int option4;
	Sprite* difficulty[5];//难度UI的存储器
	
	std::vector<Sprite*> mapChoice;//文件储存的UI系统
	int enemyDifficulty=0;//游戏难度
	std::vector<std::string> mapNames;//地图名称
	int mapNumber=-1;//地图选择
};
