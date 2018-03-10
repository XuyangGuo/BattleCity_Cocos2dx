#pragma once
#include "cocos2d.h"

USING_NS_CC;

class StayTime :public Node
{
public:
	static void start();
	//返回时间 单位 秒
	static int getStayTime();
private:
	//构造函数私有化，只能通过start启动
	StayTime();
	void stayTimeUpdate(float dt);

	int stayTime;
};
