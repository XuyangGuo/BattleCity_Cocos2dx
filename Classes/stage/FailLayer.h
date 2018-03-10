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
	// Ê§°ÜÑ¡Ïî
	CC_SYNTHESIZE(int, failOption, FailOption);

};
