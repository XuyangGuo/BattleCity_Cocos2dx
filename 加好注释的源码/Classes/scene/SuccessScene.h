/***********************************************

该类管维护成就页面的生命周期，主要包括成就页面的前端信息，
从SuccessData中获得当前成就的进度数据

***********************************************/

#pragma once
#include<iostream>
#include"cocos2d.h"
USING_NS_CC;

/*成就场景*/
class SuccessScene : public Layer {
public:
	CREATE_FUNC(SuccessScene);
	virtual bool init();
private:
	void onExit();
	void onEnterTransitionDidFinish();
	void update(float dt);
};
