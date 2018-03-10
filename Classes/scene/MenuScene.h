/***********************************************

该类是游戏主菜单的页面，
主要功能包括各个功能页面的跳转、音效的管理

***********************************************/

#pragma once
#include "cocos2d.h"
USING_NS_CC;

//对选项的枚举
enum Option
{
	start = 0,
	hero,
	success
};

class MenuScene :public Layer
{
public:
	CREATE_FUNC(MenuScene);
	virtual bool init();

private:
	Sprite *gear;
	Sprite *background;
	int option;

	void onExit();//场景切换函数
	void onEnterTransitionDidFinish();//场景切换函数
	void update(float dt);
};
