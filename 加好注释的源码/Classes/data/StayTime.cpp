/***********************************************

这是一个从游戏开始就一直记录秒数的计时器，
用来实现待机成就

***********************************************/

#include "StayTime.h"
#include "SuccessData.h"

#define SCHEDULE Director::getInstance()->getScheduler()

StayTime *p_mStayTime = nullptr;

void StayTime::start()
{
	new StayTime();
}

StayTime::StayTime()
{
	if (!SuccessData::getInstance()->isStayTimeFinished())
	{
		stayTime = 0;
		schedule(schedule_selector(StayTime::stayTimeUpdate), 1.0f, CC_REPEAT_FOREVER, 0.0f);
	}
	else
	{
		stayTime = 180;
	}
	this->onEnter();
	//此处可以用this
	p_mStayTime = this;

}

void StayTime::stayTimeUpdate(float dt)
{
	stayTime++;
	if (stayTime > 10800) //3小时
	{
		SuccessData::getInstance()->updateStayTime();
		unschedule(schedule_selector(StayTime::stayTimeUpdate));
	}
}

int StayTime::getStayTime()
{ 
	return p_mStayTime->stayTime;
}