#pragma once
// ---------------------------------------------------------------------------- -
// File:	Barrier.cpp
//
// Desc: This file stores the barrier object class. This class performs tasks
//	   such as barrier movement, some minor physics as well as rendering.
//
#ifndef _BARRIER_H_
#define _BARRIER_H_

#include "Main.h"
#include"BackBuffer.h"
#include "Vec2.h"
#include "Sprite.h"
#include"windows.h"
#include <algorithm>
#include <math.h>

using namespace std;
#define BARRIER_INITIAL_POSITION  GetSystemMetrics(SM_CYSCREEN) / 1.25

class CBarrier
{
public:

	enum ESpeedStates
	{
		SPEED_START,
		SPEED_STOP
	};

	//-------------------------------------------------------------------------
	// Constructors & Destructors for This Class.
	//-------------------------------------------------------------------------
	CBarrier(const BackBuffer *pBackBuffer);
	virtual ~CBarrier();

	//-------------------------------------------------------------------------
	// Public Functions for This Class.
	//-------------------------------------------------------------------------
	void					MoveBarrier();
	void					Draw();
	void					Update(float dt);
	Vec2&					barrierPosition();
	void					RespawnBarrier();

	Sprite*					m_pSpriteBarrier;
	bool					m_bBarrier;

private:
	//-------------------------------------------------------------------------
	// Private Variables for This Class.
	//-------------------------------------------------------------------------

	ESpeedStates			m_eSpeedState;
	float					m_fTimer;

public:
};

#endif // _MARIO_H_