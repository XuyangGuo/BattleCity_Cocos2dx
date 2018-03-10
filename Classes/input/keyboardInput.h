#pragma once
#include "cocos2d.h"
USING_NS_CC;

enum KeyTag
{
	kKeyUpTag,	//W¼ü
	kKeyRightTag, //D¼ü
	kKeyDownTag, //S¼ü
	kKeyLeftTag, //A¼ü
	kKeySelctTag,
	kKeyStartTag,
	kKeyBTag,  //K¼ü
	kKeyATag,  //J¼ü
	kKeyQTag,
	kKeyETag,
	kKeyRTag,
	kKeyTTag,
	kKeyYTag,
	kKeyUTag,
	kKeyITag,
	kKeyOTag,
	kKeyPTag,
	kKeyFTag,
	kKeyGTag,
	kKeyHTag,
	kKeyLTag,
	kKeyZTag,
	kKeyXTag,
	kKeyCTag,
	kKeyVTag,
	kKey_BTag,
	kKeyNTag,
	kKeyMTag,
};

class KeyboardInput :public Layer
{
public:
	KeyboardInput();
	~KeyboardInput();
	CREATE_FUNC(KeyboardInput);
	virtual bool init();

private:
	/* ÉèÖÃ°´¼ü×´Ì¬ */
	void setKeyState(EventKeyboard::KeyCode keyCode, bool state);
};
