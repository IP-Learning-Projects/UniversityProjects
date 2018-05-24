#pragma once
// ---------------------------------------------------------------------------- -
// File:	Mario.cpp
//
// Desc: This file stores the mario object class. This class performs tasks
//	   such as enemy movement, some minor physics as well as rendering.
//
#ifndef _MARIO_H_
#define _MARIO_H_

#include "Main.h"
#include"BackBuffer.h"
#include "Vec2.h"
#include "Sprite.h"
#include"windows.h"
#include <algorithm>
#include <math.h>
#include "BulletList.h"
using namespace std;
#define PLAYER_INITIAL_POSITION  GetSystemMetrics(SM_CYSCREEN) / 1.4
#define MAXIMUM_JUMP_HEIGHT GetSystemMetrics(SM_CYSCREEN) / 1.9
class CMario
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
	CMario(const BackBuffer *pBackBuffer);
	virtual ~CMario();

	//-------------------------------------------------------------------------
	// Public Functions for This Class.
	//-------------------------------------------------------------------------
	void					MoveMario(ULONG ulDirection);
	void					MarioBulletMovement();
	void CMario::Jump();
	void					Draw();
	void					Update(float dt);
	void					MarioFire();
	Vec2&					marioPosition();
	Vec2&					Velocity();
	void RotatePlayer(const BackBuffer *pBackBuffer);

	BackBuffer*				sm_pBBuffer;

	void					Mario();
	bool					AdvanceMario();

	void					ExplodeMario();
	bool					AdvanceExplosionMario();
	bool					AdvanceFire();
	Sprite*					m_pSpriteMario;
	AnimatedSprite*			m_pFireSprite;
	AnimatedSprite*			m_pMarioSpriteAnimated;
	bool				   jump = 0;
	BulletList             *m_lMarioBullets;
	int						m_iBulletType;
	int						m_iNumberBulletSpecial;
	float					gravity = 0;
	bool					player_to_the_right;
private:
	//-------------------------------------------------------------------------
	// Private Variables for This Class.
	//-------------------------------------------------------------------------

	ESpeedStates			m_eSpeedState;
	float					m_fTimer;

	bool					m_bMario;
	int						m_iMarioFrame;

	bool					m_bExplosion;
	AnimatedSprite*			m_pExplosionSprite;
	int						m_iExplosionFrame;

	bool m_bFire;

	bool m_bRotationState; // true - dreapta, false - stanga

public:
};

#endif // _MARIO_H_