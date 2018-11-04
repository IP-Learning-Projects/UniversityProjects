//-----------------------------------------------------------------------------
// File:	Barrier.cpp
//
// Desc: This file stores the barrier object class. This class performs tasks
//	   such as barrier movement, some minor physics as well as rendering.
//

#include "Barrier.h"

//-----------------------------------------------------------------------------
// Name : CBarrier () (Constructor)
// Desc : CBarrier Class Constructor
//-----------------------------------------------------------------------------
CBarrier::CBarrier(const BackBuffer *pBackBuffer)
{
	// Animation frame crop rectangle
	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = 128;
	r.bottom = 128;

	m_pSpriteBarrier = new AnimatedSprite("data/barrier.bmp", "data/barrierMask.bmp", r, 16);
	m_pSpriteBarrier->setBackBuffer(pBackBuffer);
	m_pSpriteBarrier->mPosition.y = BARRIER_INITIAL_POSITION;
	m_bBarrier = false;
}

//-----------------------------------------------------------------------------
// Name : ~CBarrier () (Destructor)
// Desc : CBarrier Class Destructor
//-----------------------------------------------------------------------------
CBarrier::~CBarrier()
{
	delete m_pSpriteBarrier;
}

//-----------------------------------------------------------------------------
// Name : Draw()
// Desc : Draws the barrier
//-----------------------------------------------------------------------------
void CBarrier::Draw()
{
	if (m_bBarrier) {
		m_pSpriteBarrier->draw();
	}
}
//-----------------------------------------------------------------------------
// Name : MoveBarrier()
// Desc : Moves the barrier from right to left
//-----------------------------------------------------------------------------

void CBarrier::MoveBarrier() {
	m_pSpriteBarrier->mPosition.x -= 1;
}

//-----------------------------------------------------------------------------
// Name : barrierPosition()
// Desc : Returns the position of the barrier on X and Y axis
//-----------------------------------------------------------------------------
Vec2& CBarrier::barrierPosition()
{
	return m_pSpriteBarrier->mPosition;
}

//-----------------------------------------------------------------------------
// Name : RespawnBarrier()
// Desc : Inserts a new barrier after a while
//-----------------------------------------------------------------------------
void CBarrier::RespawnBarrier()
{
	m_pSpriteBarrier->mPosition.x = GetSystemMetrics(SM_CXSCREEN);
	m_pSpriteBarrier->mPosition.y = BARRIER_INITIAL_POSITION;
}