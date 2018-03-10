/***********************************************

这是一个实现了（不限于）26键的全键盘监听，
按键状态储存在Global中

***********************************************/

#pragma once
#include "cocos2d.h"
USING_NS_CC;

enum KeyTag
{
	kKeyUpTag,	//W键
	kKeyRightTag, //D键
	kKeyDownTag, //S键
	kKeyLeftTag, //A键
	kKeySelctTag,
	kKeyStartTag,
	kKeyBTag,  //K键
	kKeyATag,  //J键
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
	/* 设置按键状态 */
	void setKeyState(EventKeyboard::KeyCode keyCode, bool state);
};
