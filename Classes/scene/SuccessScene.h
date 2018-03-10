#pragma once
#include<iostream>
#include"cocos2d.h"
USING_NS_CC;

/*³É¾Í³¡¾°*/
class SuccessScene : public Layer {
public:
	CREATE_FUNC(SuccessScene);
	virtual bool init();
private:
	void onExit();
	void onEnterTransitionDidFinish();
	void update(float dt);
};
