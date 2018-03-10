/***********************************************

这是一个实现了（不限于）26键的全键盘监听，
按键状态储存在Global中

***********************************************/

#include "keyboardInput.h"
#include "data\Global.h"

KeyboardInput::KeyboardInput()
{
	Layer::onEnter();
}

KeyboardInput::~KeyboardInput()
{
	Layer::onExit();
}

bool KeyboardInput::init()
{
	Layer::init();
	auto keyboardEventListener = EventListenerKeyboard::create();
	keyboardEventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event *_event)
	{
		this->setKeyState(keyCode, true);

		//方向键快速按键
		if (keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_S || keyCode == EventKeyboard::KeyCode::KEY_D)
		{
			schedule(ccSchedulerFunc([=](float dt)
			{
				this->setKeyState(keyCode, true);
			}
			), 0.08f, CC_REPEAT_FOREVER, 1.0f, String::createWithFormat("QuickPress%d", (int)keyCode)->getCString());
		}
	};
	keyboardEventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event *_event)
	{
		//关掉方向键快速按键

		if (keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_S || keyCode == EventKeyboard::KeyCode::KEY_D)
		{
			unschedule(String::createWithFormat("QuickPress%d", (int)keyCode)->getCString());
		}

		this->setKeyState(keyCode, false);

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardEventListener, this);

	return true;
}
//设置键盘状态
void KeyboardInput::setKeyState(EventKeyboard::KeyCode keyCode, bool state)
{
	switch(keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		g_keyUp = state;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		g_keyDown = state;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		g_keyLeft = state;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		g_keyRight = state;
		break;
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		g_keySelect = state;
		break;
	case EventKeyboard::KeyCode::KEY_ENTER:
		g_keyStart = state;
		break;
	case EventKeyboard::KeyCode::KEY_J:
		g_keyA = state;
		break;
	case EventKeyboard::KeyCode::KEY_K:
		g_keyB = state;
		break;
	case EventKeyboard::KeyCode::KEY_Q:
		g_keyQ = state;
		break;
	case EventKeyboard::KeyCode::KEY_E:
		g_keyE = state;
		break;
	case EventKeyboard::KeyCode::KEY_R:
		g_keyR = state;
		break;
	case EventKeyboard::KeyCode::KEY_T:
		g_keyT = state;
		break;
	case EventKeyboard::KeyCode::KEY_Y:
		g_keyY = state;
		break;
	case EventKeyboard::KeyCode::KEY_U:
		g_keyU = state;
		break;
	case EventKeyboard::KeyCode::KEY_I:
		g_keyI = state;
		break;
	case EventKeyboard::KeyCode::KEY_O:
		g_keyO = state;
		break;
	case EventKeyboard::KeyCode::KEY_P:
		g_keyP = state;
		break;
	case EventKeyboard::KeyCode::KEY_F:
		g_keyF = state;
		break;
	case EventKeyboard::KeyCode::KEY_G:
		g_keyG = state;
		break;
	case EventKeyboard::KeyCode::KEY_H:
		g_keyH = state;
		break;
	case EventKeyboard::KeyCode::KEY_L:
		g_keyL = state;
		break;
	case EventKeyboard::KeyCode::KEY_Z:
		g_keyZ = state;
		break;
	case EventKeyboard::KeyCode::KEY_X:
		g_keyX = state;
		break;
	case EventKeyboard::KeyCode::KEY_C:
		g_keyC = state;
		break;
	case EventKeyboard::KeyCode::KEY_V:
		g_keyV = state;
		break;
	case EventKeyboard::KeyCode::KEY_B:
		g_key_B = state;
		break;
	case EventKeyboard::KeyCode::KEY_N:
		g_keyN = state;
		break;
	case EventKeyboard::KeyCode::KEY_M:
		g_keyM = state;
		break;
	case EventKeyboard::KeyCode::KEY_BACKSPACE:
		g_keyBACK = state;
		break;
	case EventKeyboard::KeyCode::KEY_SHIFT:
		g_keyCAPSLOCK = state;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		g_keySPACE = state;
		break;
	case EventKeyboard::KeyCode::KEY_0:
		g_key0 = state;
		break;
	case EventKeyboard::KeyCode::KEY_1:
		g_key1 = state;
		break;
	case EventKeyboard::KeyCode::KEY_2:
		g_key2 = state;
		break;
	case EventKeyboard::KeyCode::KEY_3:
		g_key3 = state;
		break;
	case EventKeyboard::KeyCode::KEY_4:
		g_key4 = state;
		break;
	case EventKeyboard::KeyCode::KEY_5:
		g_key5 = state;
		break;
	case EventKeyboard::KeyCode::KEY_6:
		g_key6 = state;
		break;
	case EventKeyboard::KeyCode::KEY_7:
		g_key7 = state;
		break;
	case EventKeyboard::KeyCode::KEY_8:
		g_key8 = state;
		break;
	case EventKeyboard::KeyCode::KEY_9:
		g_key9 = state;
		break;
	default:
		break;
	}
}
