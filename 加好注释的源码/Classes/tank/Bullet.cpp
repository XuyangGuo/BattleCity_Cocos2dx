#include "Bullet.h"
#include "scene/GameScene.h"
#include "stage\Stage.h"
#include "data\TankData.h"
#include "data\SuccessData.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
/*该类为子弹类，主要的函数有创建子弹的函数，还有子弹移动过程中的碰撞检测，
有与地图边界、地图障碍物、子弹、坦克这四种判断检测*/

//加音效,方便复制，故而注释在此
//SimpleAudioEngine::getInstance()->playBackgroundMusic("menu_levelScene.mp3", true);


Bullet::Bullet(){}

Bullet::~Bullet()
{
}
//创建子弹
Bullet* Bullet::create(void* owner, float speed, int power, Vec2 pos, Direction direction, int distance)
{

	Bullet *pRet = new Bullet();
	if (pRet && pRet->init(owner, speed, power, pos, direction, distance))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
//根据坦克类型进行创建，不同的坦克子弹类型不同，并得到坦克的速度、位置、方向、射程等参数
bool Bullet::init(void* owner, float speed, int power, Vec2 pos, Direction direction, int distance)
{
	bool bRet = false;
	do
	{
		this->Sprite::init();  //为了程序稳定，调用父类方法

		Sprite *bulletImage;//当前的子弹
		HeroType currentHType = DataM::getInstance()->getHType();
		if (owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
		{
			if (TypeATK == currentHType)
			{
				if (TankData::getInstance()->isAOE())
				{
					bulletImage = Sprite::create("Bullet1.png");
				}
				else //!isAOE
				{
					bulletImage = Sprite::create("Bullet0.png");
				}
			}
			else if (TypeDEF == currentHType)
			{
				bulletImage = Sprite::create("Bullet0.png");
			}
			else if (TypeSPE == currentHType)
			{
				bulletImage = Sprite::create("Bullet2.png");
				auto rotateAction = RotateBy::create(0.5f, -900);
				auto rotateForever = RepeatForever::create(rotateAction);
				bulletImage->runAction(rotateForever);
			}
		}
		else  //敌方坦克
		{
			bulletImage = Sprite::create("Bullet0.png");
		}

		this->addChild(bulletImage);

		_owner = owner;//子弹归属的坦克
		_power = power;//子弹的力量
		_speed = speed;//子弹的速度
		_distance = distance;//子弹的射程
		_direction = direction;//子弹的方向
		atk = static_cast<Tank*>(owner)->getATK();  //该子弹的攻击力
		this->setPosition(pos);//设置位置
		this->setRotation((direction - 1) * 90);//设置方向
		_newPos = pos;//位置
		this->move();//开始移动

		Bullet_p_x = this->getPositionX();
		Bullet_p_y = this->getPositionY();

		this->scheduleUpdate();

		bRet = true;
	} while (false);
	return bRet;
}
//对子弹进行判断碰撞检测，超出射程则设置不可见，并爆炸
void Bullet::update(float dt)
{
	_dt = dt;
	if (_visible)
	{
		this->move();
		this->collide();
	}

	if (abs(_newPos.y - Bullet_p_y) >_distance || abs(_newPos.x - Bullet_p_x)>_distance) {
		this->setVisible(false);
		this->_bomb = true;
	}

	if (_visible)
	{
		this->setPosition(_newPos);
	}
	else
	{
		/*
		if (_bomb)
		{
			GameScene::getBombM()->createBomb(kBulletBomb, _bombPos);
		}*/
		this->removeFromParent();
	}
}
//子弹的移动函数
void Bullet::move()
{
	if (_direction == UP)//方向向上
	{
		_newPos.y = _position.y + _speed;
	}
	else if (_direction == DOWN)//方向向下
	{
		//_newPos.y = _position.y - _speed * 60 * _dt;
		_newPos.y = _position.y - _speed;
	}
	else if (_direction == LEFT)//方向向左
	{
		//_newPos.x = _position.x - _speed * 60 * _dt;
		_newPos.x = _position.x - _speed;
	}
	else if (_direction == RIGHT)//方向向右
	{
		//_newPos.x = _position.x + _speed * 60 * _dt;
		_newPos.x = _position.x + _speed;
	}
}
void Bullet::collide()//总的碰撞检测
{
	this->collideMap();			// 与地图的碰撞检测 
	this->collideBullet();		// 与子弹的碰撞检测 
	this->collideTank();		// 与坦克的碰撞检测 
}
void Bullet::collideMap()//与地图的碰撞检测
{
	collideBorder();
	collideObstacle();
}

void Bullet::collideObstacle()//与障碍物的碰撞检测
{
	if (!_visible) return;
	auto col = getColNumberFromPosition(_newPos.x);
	auto row = getRowNumberFromPosition(_newPos.y);
	auto grid = false;
	auto stage = GameScene::getStage();
	int(*map)[MAP_COL] = NULL;
	stage->getMap(map);
	auto dx = 0.0f, dy = 0.0f;
	if (_direction == UP || _direction == DOWN)
	{
		if (!stage->isCanHit(row, col) && !stage->isCanHit(row, col - 1)) return;
		_bomb = true;
		if (_power == 1)	// 可打破铁，可打破整块砖 
		{
			if ((map[row][col] <= GRID4 && map[row][col] >=GRID1) || (map[row][col] & 0x0f) == BRICK)
			{
				//加音效
				if(((map[row][col] & 0x0f) == BRICK))
				{
					//加音效,方便复制，故而注释在此
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//加音效,方便复制，故而注释在此
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}

				map[row][col] = LAND;

				//子弹成就，子弹检测
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}

			}

			if ((map[row][col - 1] <= GRID4 && map[row][col - 1] >= GRID1) || (map[row][col - 1] & 0x0f) == BRICK)
			{

				//加音效
				if (((map[row][col-1] & 0x0f) == BRICK))
				{
					//加音效,方便复制，故而注释在此
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//加音效,方便复制，故而注释在此
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}

				map[row][col - 1] = LAND;

				//子弹成就，子弹检测
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}


		}
		else if (_power == 0) // 不可打破铁，可打破半块砖 
		{
			if ((map[row][col] <= GRID4 && map[row][col] >= GRID1) || (map[row][col - 1] <= GRID4 && map[row][col - 1] >= GRID1))
			{
				grid = true;
			}

			if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()) && TankData::getInstance()->isAOE())
			{ 

				//加音效,方便复制，故而注释在此
				unsigned int randNum = rand() % 4;
				SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);

				if ((map[row][col] & 0x0f) == BRICK)
				{

					map[row][col] = LAND;

					//子弹成就，子弹检测
					if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
					{
						SuccessData::getInstance()->updateBrickNum();
					}
				}
				if ((map[row][col - 1] & 0x0f) == BRICK)
				{

					map[row][col - 1] = LAND;

					//子弹成就，子弹检测
					if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
					{
						SuccessData::getInstance()->updateBrickNum();
					}
				}
			}
			else
			{

				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					//加音效,方便复制，故而注释在此
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}


				if (_direction == UP && ((map[row][col] & 0x30) != 0 || (map[row][col - 1] & 0x30) != 0)) // 子弹向上且两边有砖下半部不为空 
				{
					map[row][col] &= 0xcf;		// 消除砖块下半部分 
					map[row][col - 1] &= 0xcf;
				}
				else if (_direction == DOWN && ((map[row][col] & 0xc0) != 0 || (map[row][col - 1] & 0xc0) != 0)) // 子弹向下且两边有砖上半部不为空 
				{
					map[row][col] &= 0x3f;		// 消除砖块上半部分 
					map[row][col - 1] &= 0x3f;
				}
				else
				{
					if (!grid) // 左右两边其中有一边是铁的话，没法打到后半块砖 
					{
						/* 打破后面半块砖的时候，修改子弹爆炸的位置 */
						if (_direction == UP)
						{
							dy = CELL_HEIGHT / 2;
						}
						else
						{
							dy = -CELL_HEIGHT / 2;
						}
						/* 打破后面半块砖（因为前半块砖已打破才能打到后半块砖，所以相当于该砖全部打破） */
						map[row][col] &= 0x0f;
						map[row][col - 1] &= 0x0f;
					}
				}
				/* 砖四角全破的时候，修改类型为地 */
				if (map[row][col] == BRICK)
				{
					map[row][col] = LAND;

					//子弹成就，子弹检测
					if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
					{
						SuccessData::getInstance()->updateBrickNum();
					}
				}
				if (map[row][col - 1] == BRICK)
				{
					map[row][col - 1] = LAND;

					//子弹成就，子弹检测
					if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
					{
						SuccessData::getInstance()->updateBrickNum();
					}
				}
			}
		}

		if (map[row][col] == HOME3 || map[row][col] == HOME4 || map[row][col - 1] == HOME3 || map[row][col - 1] == HOME4)
		{
			map[1][13] = HOME2;
			map[1][14] = HOME1;
			map[0][13] = HOME1;
			map[0][14] = HOME1;
			/*AudioM::play2d(A_PLAYER_BOMB);*/
			GameScene::getStage()->updateMapCell(1, 13);
			/*GameScene::getBombM()->createBomb(kStrongholdBomb, getPos(25, 13));*/

			//拆家成就 爆家成就
			SuccessData::getInstance()->updateHomeBreakTime();

			//加音效
			SimpleAudioEngine::getInstance()->playEffect("homeBroken.mp3", false);
			SimpleAudioEngine::getInstance()->playEffect("homeBroken_1.mp3", false);

			// 家被打破，宣告失败
			NotificationCenter::getInstance()->postNotification("game_fail");
		
		}
		GameScene::getStage()->updateMapCell(row, col);
		GameScene::getStage()->updateMapCell(row, col - 1);
		//AOE检测
		checkAOE();
	}
	else if (_direction == LEFT || _direction == RIGHT)
	{
		if (!stage->isCanHit(row, col) && !stage->isCanHit(row - 1, col)) return;
		_bomb = true;
		if (_power == 1)
		{
			if ((map[row][col] <= GRID4 && map[row][col] >= GRID1) || (map[row][col] & 0x0f) == BRICK)
			{
				//加音效
				if (((map[row][col] & 0x0f) == BRICK))
				{
					//加音效,方便复制，故而注释在此
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//加音效,方便复制，故而注释在此
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}

				map[row][col] = LAND;

				//子弹成就，子弹检测
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
			if ((map[row - 1][col] <= GRID4 && map[row - 1][col] >= GRID1) || (map[row - 1][col] & 0x0f) == BRICK)
			{

				//加音效
				if (((map[row-1][col] & 0x0f) == BRICK))
				{
					//加音效,方便复制，故而注释在此
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//加音效,方便复制，故而注释在此
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}

				map[row - 1][col] = LAND;

				//子弹成就，子弹检测
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
		}
		else if (_power == 0)
		{
			if ((map[row][col] <= GRID4 && map[row][col] >= GRID1) || (map[row - 1][col] <= GRID4 && map[row - 1][col] >= GRID1))
			{
				grid = true;
			}

			if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()) && TankData::getInstance()->isAOE())
			{

				//加音效,方便复制，故而注释在此
				unsigned int randNum = rand() % 4;
				SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);


				if ((map[row][col] & 0x0f) == BRICK)
				{
					map[row][col] = LAND;

					//子弹成就，子弹检测
					if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
					{
						SuccessData::getInstance()->updateBrickNum();
					}
				}
				if ((map[row - 1][col] & 0x0f) == BRICK)
				{
					map[row - 1][col] = LAND;

					//子弹成就，子弹检测
					if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
					{
						SuccessData::getInstance()->updateBrickNum();
					}
				}
			}
			else
			{
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					//加音效,方便复制，故而注释在此
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);

				}

				if (_direction == RIGHT && ((map[row][col] & 0xa0) != 0 || (map[row - 1][col] & 0xa0) != 0))
				{
					map[row][col] &= 0x5f;		// 消除砖块左半部分 
					map[row - 1][col] &= 0x5f;
				}
				else if (_direction == LEFT && ((map[row][col] & 0x50) != 0 || (map[row - 1][col] & 0x50) != 0))
				{
					map[row][col] &= 0xaf;		// 消除砖块右半部分 
					map[row - 1][col] &= 0xaf;
				}
				else
				{
					if (!grid)
					{
						if (_direction == RIGHT)
						{
							dx = CELL_WIDTH / 2;
						}
						else
						{
							dx = -CELL_WIDTH / 2;
						}
						map[row][col] &= 0x0f;
						map[row - 1][col] &= 0x0f;
					}
				}
				if (map[row][col] == BRICK)  //无前四位了，所以是空砖块
				{
					map[row][col] = LAND;

					//子弹成就，子弹检测
					if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
					{
						SuccessData::getInstance()->updateBrickNum();
					}
				}
				if (map[row - 1][col] == BRICK)  //无前四位了，所以是空砖块
				{
					map[row - 1][col] = LAND;

					//子弹成就，子弹检测
					if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
					{
						SuccessData::getInstance()->updateBrickNum();
					}
				}
			}
		}
		if (map[row][col] == HOME3 || map[row][col] == HOME4 || map[row - 1][col] == HOME3 || map[row - 1][col] == HOME4)
		{
			map[1][13] = HOME2;
			map[1][14] = HOME1;
			map[0][13] = HOME1;
			map[0][14] = HOME1;
			/*AudioM::play2d(A_PLAYER_BOMB);*/
			GameScene::getStage()->updateMapCell(1, 13);
			/*GameScene::getBombM()->createBomb(kStrongholdBomb, getPos(25, 13));*/

			//拆家成就 爆家成就
			SuccessData::getInstance()->updateHomeBreakTime();

			//加音效
			SimpleAudioEngine::getInstance()->playEffect("homeBroken.mp3", false);
			SimpleAudioEngine::getInstance()->playEffect("homeBroken_1.mp3", false);

			// 家被打破，宣告失败
			NotificationCenter::getInstance()->postNotification("game_fail");
		}

		GameScene::getStage()->updateMapCell(row, col);
		GameScene::getStage()->updateMapCell(row - 1, col);
		//AOE检测
		checkAOE();
	}

	if (_bomb)
	{
		this->setVisible(false);
		_bombPos.x = _newPos.x + dx;
		_bombPos.y = _newPos.y + dy;
	}
	//if (_owner == GameScene::getTankM()->getPlayerTank())
	//{
	//	if (_power == 0 && grid)
	//	{
	//		/* 打到铁上且打不破时的音效 */
	//		/*AudioM::play2d(A_HIT_OBSTACLE);*/
	//	}
	//	else
	//	{
	//		/* 打破砖或铁时的音效 */
	//		/*AudioM::play2d(A_OBSTACLE_BOMB);*/
	//	}
	//}
}

//边界的碰撞检测
void Bullet::collideBorder()
{
	int(*map)[MAP_COL] = NULL;
	GameScene::getStage()->getMap(map);
	if (_newPos.x <= LEFT_EAGE || _newPos.x >= RIGHT_EAGE ||
		_newPos.y <= BOTTOM_EAGE|| _newPos.y >= TOP_EAGE)
	{
		//if (_owner == GameScene::getTankM()->getPlayerTank())
		//{
		//	AudioM::play2d(A_HIT_OBSTACLE);
		//}
		_bomb = true;
		this->setVisible(false);
		if (_newPos.x < 0)
		{
			_bombPos.x = 0;
		}
		else if (_newPos.x > MAP_WIDTH)
		{
			_bombPos.x = MAP_WIDTH;
		}
		else
		{
			_bombPos.x = _newPos.x;
		}

		if (_newPos.y < 0)
		{
			_bombPos.y = 0;
		}
		else if (_newPos.y > MAP_HEIGHT)
		{
			_bombPos.y = MAP_HEIGHT;
		}
		else
		{
			_bombPos.y = _newPos.y;
		}
	}
}
//与坦克的碰撞检测
void Bullet::collideTank()
{
	Vector<Tank*> &tanks = GameScene::getTankM()->getAllTanks();//获取所有坦克
	PlayerTank* playerTank = GameScene::getTankM()->getPlayerTank();//获取玩家坦克
	for (auto tank : tanks)
	{
		/* 判断是否是玩家坦克子弹打到敌人坦克或敌人坦克子弹打到玩家坦克的情况 */
		if ((_owner == playerTank && tank != playerTank) || (_owner != playerTank && tank == playerTank))
		{
			auto otherPos = tank->getPosition();  //坦克中点
			if (_newPos.x <= otherPos.x + CELL_WIDTH && _position.x >= otherPos.x - CELL_WIDTH &&
				_newPos.y <= otherPos.y + CELL_HEIGHT && _position.y >= otherPos.y - CELL_HEIGHT)
			{
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()) && TankData::getInstance()->isAOE())
				{
					checkAOE();  //AOE检测,其中包括所有hit结算
				}
				else
				{
					tank->hit(atk);
				}

				this->setVisible(false);
				_bomb = true;
				_bombPos.x = _newPos.x;
				_bombPos.y = _newPos.y;
				break;
			}
		}
	}
}
//与子弹类的碰撞检测
void Bullet::collideBullet()
{
	auto &bullets = GameScene::getBulletM()->getChildren();
	for (auto bullet : bullets)
	{
		auto collide = false;
		if (bullet == this || !bullet->isVisible()) continue;
		auto playTank = GameScene::getTankM()->getPlayerTank();
		/* 两个子弹都不是玩家坦克发射的，即都是敌人坦克发射的子弹，敌人坦克的子弹互相之间不消除 */
		if (((Bullet*)bullet)->getOwner() != playTank && _owner != playTank) continue;
		/* 判断两个子弹是否相交 */
		if (this->getBoundingBox().intersectsRect(bullet->getBoundingBox()))  //getBoundingBox考虑缩放 
		{
			collide = true;
		}
		else
		{
			/* 对面相向的子弹可能没相交直接穿过，所以根据两帧之间的坐标关系判断 */  //???????? 不懂
			auto otherPos = bullet->getPosition();
			if (abs(_newPos.x - otherPos.x) < 1)  // 判断是否同列（float由于精度问题，当相差小于很小的一个数的时候认为相等）  
			{
				if (_position.y < otherPos.y && _newPos.y >= otherPos.y)
				{
					collide = true;
				}
				else if (_position.y > otherPos.y && _newPos.y <= otherPos.y)
				{
					collide = true;
				}
			}
			if (abs(_newPos.y - otherPos.y) < 1)  // 判断是否同行 
			{
				if (_position.x < otherPos.x && _newPos.x >= otherPos.x)
				{
					collide = true;
				}
				else if (_position.x > otherPos.x && _newPos.x <= otherPos.x)
				{
					collide = true;
				}
			}
		}
		if (collide)
		{
			this->setVisible(false);
			bullet->setVisible(false);
		}
	}
}

//旭阳写
void Bullet::checkAOE()
{
	if (_owner != static_cast<void *>(GameScene::getTankM()->getPlayerTank()) || TankData::getInstance()->isAOE() == false)
	{
		return;
	}

	auto col = getColNumberFromPosition(_newPos.x);
	auto row = getRowNumberFromPosition(_newPos.y);
	auto stage = GameScene::getStage();
	int(*map)[MAP_COL] = NULL;
	stage->getMap(map);
	//此处可以利用diriction的枚举值只写上下和左右两种情况，但是为了更加直观，改用4种情况判定
	if (row + 1 < MAP_ROW && UP == _direction)
	{
		//和障碍物的检测
		if (1 == _power)
		{
			if ((map[row + 1][col] <= GRID4 &&map[row + 1][col] >= GRID1) || (map[row + 1][col] & 0x0f) == BRICK)
			{

				//加音效
				if (((map[row+1][col] & 0x0f) == BRICK))
				{
					//加音效,方便复制，故而注释在此
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//加音效,方便复制，故而注释在此
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}

				map[row + 1][col] = LAND;

				//子弹成就，子弹检测
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
			if ((map[row + 1][col - 1] <= GRID4 &&map[row + 1][col - 1] >= GRID1) || (map[row + 1][col - 1] & 0x0f) == BRICK)
			{

				//加音效
				if (((map[row+1][col-1] & 0x0f) == BRICK))
				{
					//加音效,方便复制，故而注释在此
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//加音效,方便复制，故而注释在此
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}


				map[row + 1][col - 1] = LAND;

				//子弹成就，子弹检测
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
		}
		else if(0 == _power)
		{
			if ((map[row + 1][col] & 0x0f) == BRICK)
			{

				//加音效,方便复制，故而注释在此
				unsigned int randNum = rand() % 4;
				SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);

				map[row + 1][col] = LAND;

				//子弹成就，子弹检测
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
			if ((map[row + 1][col - 1] & 0x0f) == BRICK)
			{

				//加音效,方便复制，故而注释在此
				unsigned int randNum = rand() % 4;
				SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);

				map[row + 1][col - 1] = LAND;

				//子弹成就，子弹检测
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
		}


		//和坦克的检测
		Vector<EnemyTank *> enemytanks = GameScene::getTankM()->getEnemyTanks();
		for (auto tank : enemytanks)
		{
			auto tankPos = tank->getPosition(); //坦克中点
			if (_newPos.x <= tankPos.x + CELL_WIDTH && _newPos.x >= tankPos.x - CELL_WIDTH &&
				_newPos.y <= tankPos.y && _newPos.y >= tankPos.y - 2*CELL_HEIGHT)
			{
				tank->hit(atk);
			}
		}

		if (map[row + 1][col] == HOME3 || map[row + 1][col] == HOME4 || map[row + 1][col - 1] == HOME3 || map[row + 1][col - 1] == HOME4)
		{
			map[1][13] = HOME2;
			map[1][14] = HOME1;
			map[0][13] = HOME1;
			map[0][14] = HOME1;
			/*AudioM::play2d(A_PLAYER_BOMB);*/
			GameScene::getStage()->updateMapCell(1, 13);
			/*GameScene::getBombM()->createBomb(kStrongholdBomb, getPos(25, 13));*/

			//拆家成就 爆家成就
			SuccessData::getInstance()->updateHomeBreakTime();

			//加音效
			SimpleAudioEngine::getInstance()->playEffect("homeBroken.mp3", false);
			SimpleAudioEngine::getInstance()->playEffect("homeBroken_1.mp3", false);

			// 家被打破，宣告失败
			NotificationCenter::getInstance()->postNotification("game_fail");

		}
		GameScene::getStage()->updateMapCell(row + 1, col);
		GameScene::getStage()->updateMapCell(row + 1, col - 1);
	}

	if (row - 1 >= 0 && DOWN == _direction)
	{
		//和障碍物的检测
		if (1 == _power)
		{
			if ((map[row - 1][col] <= GRID4 &&map[row - 1][col] >= GRID1) || (map[row - 1][col] & 0x0f) == BRICK)
			{

				//加音效
				if (((map[row-1][col] & 0x0f) == BRICK))
				{
					//加音效,方便复制，故而注释在此
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//加音效,方便复制，故而注释在此
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}

				map[row - 1][col] = LAND;

				//子弹成就，子弹检测
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
			if ((map[row - 1][col - 1] <= GRID4 &&map[row - 1][col - 1] >= GRID1) || (map[row - 1][col - 1] & 0x0f) == BRICK)
			{

				//加音效
				if (((map[row-1][col-1] & 0x0f) == BRICK))
				{
					//加音效,方便复制，故而注释在此
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//加音效,方便复制，故而注释在此
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}

				map[row - 1][col - 1] = LAND;

				//子弹成就，子弹检测
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
		}
		else if (0 == _power)
		{
			if ((map[row - 1][col] & 0x0f) == BRICK)
			{

				//加音效,方便复制，故而注释在此
				unsigned int randNum = rand() % 4;
				SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);

				map[row - 1][col] = LAND;

				//子弹成就，子弹检测
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
			if ((map[row - 1][col - 1] & 0x0f) == BRICK)
			{

				//加音效,方便复制，故而注释在此
				unsigned int randNum = rand() % 4;
				SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);

				map[row - 1][col - 1] = LAND;

				//子弹成就，子弹检测
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
		}

		if (map[row -1][col] == HOME3 || map[row -1][col] == HOME4 || map[row - 1][col - 1] == HOME3 || map[row - 1][col - 1] == HOME4)
		{
			map[1][13] = HOME2;
			map[1][14] = HOME1;
			map[0][13] = HOME1;
			map[0][14] = HOME1;
			/*AudioM::play2d(A_PLAYER_BOMB);*/
			GameScene::getStage()->updateMapCell(1, 13);
			/*GameScene::getBombM()->createBomb(kStrongholdBomb, getPos(25, 13));*/

			//拆家成就 爆家成就
			SuccessData::getInstance()->updateHomeBreakTime();

			//加音效
			SimpleAudioEngine::getInstance()->playEffect("homeBroken.mp3", false);
			SimpleAudioEngine::getInstance()->playEffect("homeBroken_1.mp3", false);

			// 家被打破，宣告失败
			NotificationCenter::getInstance()->postNotification("game_fail");

		}
		GameScene::getStage()->updateMapCell(row - 1, col);
		GameScene::getStage()->updateMapCell(row - 1, col - 1);

		//和坦克的检测
		Vector<EnemyTank *> enemytanks = GameScene::getTankM()->getEnemyTanks();
		for (auto tank : enemytanks)
		{
			auto tankPos = tank->getPosition(); //坦克中点
			if (_newPos.x <= tankPos.x + CELL_WIDTH && _newPos.x >= tankPos.x - CELL_WIDTH &&
				_newPos.y <= tankPos.y + 2 * CELL_HEIGHT && _newPos.y >= tankPos.y)
			{
				tank->hit(atk);
			}
		}
	}

	if (col - 1 >= 0 && LEFT == _direction)
	{
		//和障碍物的检测
		if (1 == _power)
		{
			if ((map[row][col - 1] <= GRID4 &&map[row][col - 1] >= GRID1) || (map[row][col - 1] & 0x0f) == BRICK)
			{

				//加音效
				if (((map[row][col-1] & 0x0f) == BRICK))
				{
					//加音效,方便复制，故而注释在此
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//加音效,方便复制，故而注释在此
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}

				map[row][col - 1] = LAND;

				//子弹成就，子弹检测
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
			if ((map[row - 1][col - 1] <= GRID4 &&map[row - 1][col - 1] >= GRID1) || (map[row - 1][col - 1] & 0x0f) == BRICK)
			{

				//加音效
				if (((map[row-1][col-1] & 0x0f) == BRICK))
				{
					//加音效,方便复制，故而注释在此
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//加音效,方便复制，故而注释在此
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}

				map[row - 1][col - 1] = LAND;

				//子弹成就，子弹检测
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
		}
		else if (0 == _power)
		{
			if ((map[row][col - 1] & 0x0f) == BRICK)
			{

				//加音效,方便复制，故而注释在此
				unsigned int randNum = rand() % 4;
				SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);

				map[row][col-1] = LAND;

				//子弹成就，子弹检测
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
			if ((map[row - 1][col - 1] & 0x0f) == BRICK)
			{

				//加音效,方便复制，故而注释在此
				unsigned int randNum = rand() % 4;
				SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);

				map[row - 1][col - 1] = LAND;

				//子弹成就，子弹检测
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
		}
		if (map[row][col - 1] == HOME3 || map[row][col - 1] == HOME4 || map[row - 1][col - 1] == HOME3 || map[row - 1][col - 1] == HOME4)
		{
			map[1][13] = HOME2;
			map[1][14] = HOME1;
			map[0][13] = HOME1;
			map[0][14] = HOME1;
			/*AudioM::play2d(A_PLAYER_BOMB);*/
			GameScene::getStage()->updateMapCell(1, 13);
			/*GameScene::getBombM()->createBomb(kStrongholdBomb, getPos(25, 13));*/

			//拆家成就 爆家成就
			SuccessData::getInstance()->updateHomeBreakTime();

			//加音效
			SimpleAudioEngine::getInstance()->playEffect("homeBroken.mp3", false);
			SimpleAudioEngine::getInstance()->playEffect("homeBroken_1.mp3", false);

			// 家被打破，宣告失败
			NotificationCenter::getInstance()->postNotification("game_fail");
		}
		GameScene::getStage()->updateMapCell(row, col - 1);
		GameScene::getStage()->updateMapCell(row - 1, col - 1);

		//和坦克的检测
		Vector<EnemyTank *> enemytanks = GameScene::getTankM()->getEnemyTanks();
		for (auto tank : enemytanks)
		{
			auto tankPos = tank->getPosition(); //坦克中点
			if (_newPos.x <= tankPos.x + 2 * CELL_WIDTH&& _newPos.x >= tankPos.x  &&
				_newPos.y <= tankPos.y + CELL_HEIGHT && _newPos.y >= tankPos.y - CELL_HEIGHT)
			{
				tank->hit(atk);
			}
		}
	}

	if (col + 1 < MAP_COL && RIGHT == _direction)
	{
		//和障碍物的检测
		if (1 == _power)
		{
			if ((map[row][col + 1] <= GRID4 &&map[row][col + 1] >= GRID1) || (map[row][col + 1] & 0x0f) == BRICK)
			{

				//加音效
				if (((map[row][col+1] & 0x0f) == BRICK))
				{
					//加音效,方便复制，故而注释在此
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//加音效,方便复制，故而注释在此
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}


				map[row][col + 1] = LAND;

				//子弹成就，子弹检测
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
			if ((map[row - 1][col + 1] <= GRID4 &&map[row - 1][col + 1] >= GRID1) || (map[row - 1][col + 1] & 0x0f) == BRICK)
			{

				//加音效
				if (((map[row-1][col+1] & 0x0f) == BRICK))
				{
					//加音效,方便复制，故而注释在此
					unsigned int randNum = rand() % 4;
					SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);
				}
				else
				{
					//加音效,方便复制，故而注释在此
					SimpleAudioEngine::getInstance()->playEffect("gridBroken.mp3", false);
				}

				map[row - 1][col + 1] = LAND;

				//子弹成就，子弹检测
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
		}
		else if (0 == _power)
		{
			if ((map[row][col + 1] & 0x0f) == BRICK)
			{

				//加音效,方便复制，故而注释在此
				unsigned int randNum = rand() % 4;
				SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);

				map[row][col + 1] = LAND;

				//子弹成就，子弹检测
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
			if ((map[row - 1][col + 1] & 0x0f) == BRICK)
			{

				//加音效,方便复制，故而注释在此
				unsigned int randNum = rand() % 4;
				SimpleAudioEngine::getInstance()->playEffect(String::createWithFormat("brickBroken%d.mp3", randNum)->getCString(), false);

				map[row - 1][col + 1] = LAND;

				//子弹成就，子弹检测
				if (_owner == static_cast<void *>(GameScene::getTankM()->getPlayerTank()))
				{
					SuccessData::getInstance()->updateBrickNum();
				}
			}
		}

		if (map[row][col + 1] == HOME3 || map[row][col + 1] == HOME4 || map[row - 1][col + 1] == HOME3 || map[row - 1][col + 1] == HOME4)
		{
			map[1][13] = HOME2;
			map[1][14] = HOME1;
			map[0][13] = HOME1;
			map[0][14] = HOME1;
			/*AudioM::play2d(A_PLAYER_BOMB);*/
			GameScene::getStage()->updateMapCell(1, 13);
			/*GameScene::getBombM()->createBomb(kStrongholdBomb, getPos(25, 13));*/

			//拆家成就 爆家成就
			SuccessData::getInstance()->updateHomeBreakTime();

			//加音效
			SimpleAudioEngine::getInstance()->playEffect("homeBroken.mp3", false);
			SimpleAudioEngine::getInstance()->playEffect("homeBroken_1.mp3", false);

			// 家被打破，宣告失败
			NotificationCenter::getInstance()->postNotification("game_fail");
		}
		GameScene::getStage()->updateMapCell(row, col + 1);
		GameScene::getStage()->updateMapCell(row - 1, col + 1);

		//和坦克的检测
		Vector<EnemyTank *> enemytanks = GameScene::getTankM()->getEnemyTanks();
		for (auto tank : enemytanks)
		{
			auto tankPos = tank->getPosition(); //坦克中点
			if (_newPos.x <= tankPos.x && _newPos.x >= tankPos.x - 2 * CELL_WIDTH  &&
				_newPos.y <= tankPos.y + CELL_HEIGHT && _newPos.y >= tankPos.y - CELL_HEIGHT)
			{
				tank->hit(atk);
			}
		}
	}
}