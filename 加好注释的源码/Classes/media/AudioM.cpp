/***********************************************

该接口预留出来，但是已废弃，并没有使用
这是一个用来存储音效的类

***********************************************/

#include "AudioM.h"

void AudioM::preloadAllAudio()
{
	const char* audio[] = {""};
	for (auto name : audio)
	{
		AudioEngine::preload(name);
	}
}

//int AudioM::play2d(const std::string& filePath, bool loop, float volume, const AudioProfile *profile)
//{
//	///* 关卡开场音效期间，除了爆炸和暂停音效除外，其余音效均不播放 */
//	//if (_startAudioPlaying == true && filePath != A_PAUSE && filePath != A_ENEMY_BOMB && filePath != A_PLAYER_BOMB) return INVALID_AUDIO_ID;
//	//auto audioID = AudioEngine::play2d(filePath, loop, volume, profile);
//	//if (filePath == A_START)
//	//{
//	//	_startAudioPlaying = true;
//	//	AudioM::setFinishCallback(audioID, [&](int id, const std::string& filePath) {
//	//		_startAudioPlaying = false;
//	//		NotificationCenter::getInstance()->postNotification("start_audio_end");
//	//	});
//	//}
//	//return audioID;
//	
//	//AudioM::setFinishCallback(,)
//}