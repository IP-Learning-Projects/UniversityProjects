//-----------------------------------------------------------------------------
// File:	Enemy.cpp
//
// Desc: This file stores the enemy object class. This class performs tasks
//	   such as enemy movement, some minor physics as well as rendering.
//
#ifndef _ENEMY_H_
#define _ENEMY_H_
# define MAX_JUMP 500
#include "Main.h"
#include"BackBuffer.h"
#include "Vec2.h"
#include "Sprite.h"
#include"windows.h"
#include <algorithm>
#include <math.h>
using namespace std;

#define ENEMY_POSITION GetSystemMetrics(SM_CYSCREEN) / 1.37
class CEnemy
{
public:
	//-------------------------------------------------------------------------
	// Enumerators
	//-------------------------------------------------------------------------

	enum ESpeedStates
	{
		SPEED_START,
		SPEED_STOP
	};

	//-------------------------------------------------------------------------
	// Constructors & Destructors for This Class.
	//-------------------------------------------------------------------------
	CEnemy(const BackBuffer *pBackBuffer);
	virtual ~CEnemy();

	//-------------------------------------------------------------------------
	// Public Functions for This Class.
	//-------------------------------------------------------------------------

	void					EnemyBulletMovement();
	void					Update(float dt);
	void					Draw();
	void					MoveEnemy(int level);
	void					EnemyFire();
	Vec2&					enemyPosition();
	Vec2&					Velocity();

	BackBuffer*				sm_pBBuffer;

	void					Enemy();
	bool					AdvanceEnemy();

	void					ExplodeEnemy();
	bool					AdvanceExplosionEnemy();

	Sprite*					m_pSpriteEnemy;
	AnimatedSprite*			m_pEnemyFireSprite;
	AnimatedSprite*			m_pEnemySpriteAnimated;

	void					Jump();
	int						m_iEnemyLives;

	void					InsertNewPlayer(const BackBuffer *pBackBuffer);

	bool enemyJump = 0;

private:
	//-------------------------------------------------------------------------
	// Private Variables for This Class.
	//-------------------------------------------------------------------------

	ESpeedStates			m_eSpeedState;
	float					m_fTimer;

	bool					m_bEnemy;
	int						m_iEnemyFrame;
	int						m_iEnemyType;

	//bool					m_bExplosionEnemy;
	AnimatedSprite*			m_pExplosionSpriteEnemy;
	int						m_iExplosionFrameEnemy;

	void					CollisionDetection();
	bool					CollisionDetection(Sprite *Sprite1, Sprite *Sprite2);

public:
	//Pt a incepe jocul trebuie apasat enter
	bool					m_bStartGame = false;
	bool					m_bEnemyFire;
	bool					m_bExplosionEnemy;
};
#endif // _ENEMY_H_