/***********************************************

该类是游戏开始前选择英雄的页面，
主要功能包括技能页面和游戏运行页面的跳转管理，修改DataM中当前所选坦克类型

***********************************************/

#pragma once
#include "cocos2d.h"
USING_NS_CC;


class SelectHeroScene :public Layer
{
public:
	CREATE_FUNC(SelectHeroScene);
	virtual bool init();
	void update(float dt);

private:
	void onExit();
	void onEnterTransitionDidFinish() override;
	Sprite *selectedHero;
	int heroOption; // 选择英雄
};
