//-----------------------------------------------------------------------------
// File: CPlayer.cpp
//
// Desc: This file stores the player object class. This class performs tasks
//	   such as player movement, some minor physics as well as rendering.
//
// Original design by Adam Hoult & Gary Simmons. Modified by Mihai Popescu.
//-----------------------------------------------------------------------------

#ifndef _CPLAYER_H_
#define _CPLAYER_H_

//-----------------------------------------------------------------------------
// CPlayer Specific Includes
//-----------------------------------------------------------------------------
#include "Main.h"
#include"BackBuffer.h"
#include "Vec2.h"
#include "Sprite.h"
#include"windows.h"
#include <algorithm>
#include <math.h>
#include <list>
#include "BulletList.h"
#include "Mario.h"
#include "Enemy.h"
using namespace std;
#define PLAYER_INITIAL_POSITION 600.0

//-----------------------------------------------------------------------------
// Main Class Definitions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Name : CPlayer (Class)
// Desc : Player class handles all player manipulation, update and management.
//-----------------------------------------------------------------------------
class CPlayer
{
public:
	//-------------------------------------------------------------------------
	// Enumerators
	//-------------------------------------------------------------------------
	enum DIRECTION
	{
		DIR_FORWARD = 1,
		DIR_LEFT = 4,
		DIR_RIGHT = 8,
	};

	enum ESpeedStates
	{
		SPEED_START,
		SPEED_STOP
	};

	//-------------------------------------------------------------------------
	// Constructors & Destructors for This Class.
	//-------------------------------------------------------------------------
	CPlayer(const BackBuffer *pBackBuffer);
	virtual ~CPlayer();

	//-------------------------------------------------------------------------
	// Public Functions for This Class.
	//-------------------------------------------------------------------------

	bool CollisionDetection(Sprite *Sprite1, Sprite *Sprite2);
	void					DrawEndGame();

	BackBuffer*				sm_pBBuffer;
	AnimatedSprite*	 m_pPlayerLivesSprite;
	int						m_iPlayerLifeFrame = 0;
	int lives;
	int points;
	int rotationDirection;
	//	bool EnemyHit = false;
	//	bool PlayerHit = false;
	//	bool col = false;
	//	bool left;
	//	int count = 0;

	bool gameOver;

	//void					Explode();
	//bool					AdvanceExplosion();

	void					CollisionDetection();

	Sprite*					gameOver1;
	Sprite*					gameOver2;
	Sprite*					endgame;
	Sprite*					aux; //retinere pozitie rotatie
	CMario*					mario;
	bool isGmaeOver();
	bool					m_bStartGame = false;

private:
	//-------------------------------------------------------------------------
	// Private Variables for This Class.
	//-------------------------------------------------------------------------

	ESpeedStates			m_eSpeedState;
	float					m_fTimer;
	bool					m_bExplosion;
	AnimatedSprite*			m_pExplosionSprite;
	int						m_iExplosionFrame;
	bool m_bFire;

public:
	//Pt a incepe jocul trebuie apasat enter
};

#endif // _CPLAYER_H_