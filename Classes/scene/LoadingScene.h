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