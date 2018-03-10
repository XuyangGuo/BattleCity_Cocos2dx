#pragma once
#ifndef __AUDIO_M_H__
#define __AUDIO_M_H__

#include "cocos2d.h"
#include "AudioEngine.h"

USING_NS_CC;
using namespace experimental;


/* 声音管理类 */
class AudioM : public AudioEngine
{
public:
	/* 预加载声音 */
	static void preloadAllAudio();
	/* 重写父类play2d函数，添加游戏自己的逻辑 */
	//static int play2d(const std::string& filePath, bool loop = false, float volume = 1.0f, const AudioProfile *profile = nullptr);

private:

};

#endif