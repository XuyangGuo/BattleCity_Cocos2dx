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
	int heroOption; // —°‘Ò”¢–€
};
