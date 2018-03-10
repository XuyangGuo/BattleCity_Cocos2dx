/***********************************************

该类是游戏开始运行之前的预加载页面，
主要功能包括图片、plist、json、音效的预加载，计时器的开启

***********************************************/

#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

/* 加载场景类 */
class LoadingScene : public Layer
{
public:
	CREATE_FUNC(LoadingScene);
    virtual bool init();  
};

#endif