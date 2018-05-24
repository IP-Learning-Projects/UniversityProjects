//-----------------------------------------------------------------------------
// File: CPlayer.cpp
//
// Desc: This file stores the player object class. This class performs tasks
//       such as player movement, some minor physics as well as rendering.
//
// Original design by Adam Hoult & Gary Simmons. Modified by Mihai Popescu.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// CPlayer Specific Includes
//-----------------------------------------------------------------------------
#include "CPlayer.h"

//-----------------------------------------------------------------------------
// Name : CPlayer () (Constructor)
// Desc : CPlayer Class Constructor
//-----------------------------------------------------------------------------
CPlayer::CPlayer(const BackBuffer *pBackBuffer)
{
	// Animation frame crop rectangle
	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = 128;
	r.bottom = 128;

	gameOver1 = new Sprite("data/GameOver1.bmp", RGB(0xff, 0x00, 0xff));
	gameOver1->setBackBuffer(pBackBuffer);
	gameOver2 = new Sprite("data/GameOver2.bmp", RGB(0xff, 0x00, 0xff));
	gameOver2->setBackBuffer(pBackBuffer);

	endgame = new Sprite("data/game_over_mario.bmp", RGB(0, 0, 0));
	endgame->mPosition = Vec2(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN) / 2);

	endgame->setBackBuffer(pBackBuffer);

	m_bFire = false;
	gameOver = false;
}

//-----------------------------------------------------------------------------
// Name : ~CPlayer () (Destructor)
// Desc : CPlayer Class Destructor
//-----------------------------------------------------------------------------
CPlayer::~CPlayer()
{
	delete gameOver1;
	delete gameOver2;
}

//-----------------------------------------------------------------------------
// Name : Draw()
// Desc : Draws the objects if the game is over (so far)
//-----------------------------------------------------------------------------
void CPlayer::DrawEndGame()
{
	endgame->draw();
}

//-----------------------------------------------------------------------------
// Name : CollisionDetection(Sprite *Sprite1, Sprite *Sprite2)
// Desc : It shoul detect if any 2 sprites collide (but it does NOT work so far)
//-----------------------------------------------------------------------------

bool CPlayer::CollisionDetection(Sprite *Sprite1, Sprite *Sprite2)
{
	Vec2 avion1 = Sprite1->mPosition;
	Vec2 avion2 = Sprite2->mPosition;

	double x = avion1.x - avion2.x;
	double y = avion1.y - avion2.y;

	double vertical_gap = fabs(y) - Sprite1->height();
	double horizontal_gap = fabs(x) - Sprite1->width();

	if (vertical_gap < 0 && horizontal_gap < 0)
		return true;
	else return false;
}

// Name : CollisionDetection()
// Desc : Redundant code from when this used to be a game with airplanes. Maybe we'll need it again. Maybe not. Who knows?
//-----------------------------------------------------------------------------