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

	int heroOption; // —°‘Ò”¢–€
};
