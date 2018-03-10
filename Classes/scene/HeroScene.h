/***********************************************

该类是主菜单角色选项下面的角色按钮的跳转页面，
主要功能包括音效管理、按钮管理、主菜单和技能页面的跳转

***********************************************/

#pragma once

#include "cocos2d.h"

USING_NS_CC;


class HeroScene :public Layer
{
public:
	CREATE_FUNC(HeroScene);
	virtual bool init();
	void update(float dt);

private:
	void onExit();

	void onEnterTransitionDidFinish();
	Sprite *bigCircle0;
	Sprite *bigCircle1;
	Sprite *bigCircle2;

	int heroOption; // 选择英雄
};
