#pragma once
#include "cocos2d.h"
USING_NS_CC;

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

	void onExit();
	void onEnterTransitionDidFinish();
	void update(float dt);
};
