/***********************************************

该类管维护失败弹出层的生命周期

***********************************************/

#pragma once
#include "cocos2d.h"
USING_NS_CC;

enum FailOption
{
	reBegin,
	back
};

class FailLayer :public Layer
{
public:
	CREATE_FUNC(FailLayer);
	virtual bool init();
	// 失败选项
	CC_SYNTHESIZE(int, failOption, FailOption);

};
