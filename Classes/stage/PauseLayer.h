/***********************************************

该类管维护暂停弹出层的生命周期

***********************************************/

#pragma once
#include "cocos2d.h"
USING_NS_CC;

enum PauseOption
{
	ReStart,
	Back
};

class PauseLayer :public Layer
{
public:
	CREATE_FUNC(PauseLayer);
	virtual bool init();
	CC_SYNTHESIZE(int, pauseOption, PauseOption);
};