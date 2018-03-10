/***********************************************

该类管维护胜利弹出层的生命周期

***********************************************/

#pragma once
#include "cocos2d.h"

USING_NS_CC;

enum WinOption
{
	nextLevel = 0,
	winBack
};

class WinLayer :public Layer
{
public:
	CREATE_FUNC(WinLayer);
	virtual bool init();
	// 胜利选项
	CC_SYNTHESIZE(int, winOption, WinOption);
	// 读取分数
	int getScore() { return score; };
private:
	int score;  //最终分数
};
