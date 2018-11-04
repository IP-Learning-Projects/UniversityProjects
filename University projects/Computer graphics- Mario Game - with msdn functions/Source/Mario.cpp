//-----------------------------------------------------------------------------
// File:	Enemy.cpp
//
// Desc: This file stores the main Player class. This class performs tasks
//	   such as player movement, some minor physics as well as rendering.
//

#include "Mario.h"

//-----------------------------------------------------------------------------
// Name : CEnemy () (Constructor)
// Desc : CEnemy Class Constructor
//-----------------------------------------------------------------------------
CMario::CMario(const BackBuffer *pBackBuffer)
{
	player_to_the_right = true;
	// Animation frame crop rectangle
	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = 128;
	r.bottom = 128;

	//m_pSprite = new Sprite("data/planeimg.bmp", "data/planemask.bmp");
	m_pSpriteMario = new Sprite("data/marioSp.bmp", RGB(0xff, 0x00, 0xff));
	m_pSpriteMario->setBackBuffer(pBackBuffer);
	m_eSpeedState = SPEED_STOP;
	m_fTimer = 0;
	// Mario
	m_pMarioSpriteAnimated = new AnimatedSprite("data/mario.bmp", "data/mario0.bmp", r, 16);
	m_pMarioSpriteAnimated->setBackBuffer(pBackBuffer);
	m_bMario = false;
	m_iMarioFrame = 0;
	m_bRotationState = true; //Mario merge spre dreapta
	marioPosition() = Vec2(100.0, PLAYER_INITIAL_POSITION);

	//---------------------Explosion Mario
	m_pExplosionSprite = new AnimatedSprite("data/ex.bmp", "data/exmask.bmp", r, 16);
	m_pExplosionSprite->setBackBuffer(pBackBuffer);
	m_bExplosion = false;
	m_iExplosionFrame = 0;

	//--------------------Replaced by a bullet List
	//m_pFireSprite = new AnimatedSprite("data/purple_fire.bmp", "data/purple_fire.bmp", r, 1);
	//m_pFireSprite->setBackBuffer(pBackBuffer);
	//m_bFire = false;

	m_lMarioBullets = new BulletList(pBackBuffer);
	m_iBulletType = 1;
	m_iNumberBulletSpecial = 10;
}

//-----------------------------------------------------------------------------
// Name : ~CMario () (Destructor)
// Desc : CMario Class Destructor
//-----------------------------------------------------------------------------
CMario::~CMario()
{
	delete m_pSpriteMario;
	delete m_pMarioSpriteAnimated;
}

void CMario::Update(float dt)
{
	// Update sprite
	m_pSpriteMario->update(dt);

	// Get velocity
	double v = m_pSpriteMario->mVelocity.Magnitude();

	// NOTE: for each async sound played Windows creates a thread for you
	// but only one, so you cannot play multiple sounds at once.
	// This creation/destruction of threads also leads to bad performance
	// so this method is not recommanded to be used in complex projects.

	// update internal time counter used in sound handling (not to overlap sounds)
	m_fTimer += dt;

	// A FSM is used for sound manager
	switch (m_eSpeedState) {
	case SPEED_STOP:
		if (v > 35.0f) {
			m_eSpeedState = SPEED_START;
			//PlaySound("data/jet-start.wav", NULL, SND_FILENAME | SND_ASYNC);
			m_fTimer = 0;
		}
		break;
	case SPEED_START:
		if (v < 25.0f) {
			m_eSpeedState = SPEED_STOP;
			//PlaySound("data/jet-stop.wav", NULL, SND_FILENAME | SND_ASYNC);
			m_fTimer = 0;
		}
		else
			if (m_fTimer > 1.f) {
				//PlaySound("data/jet-cabin.wav", NULL, SND_FILENAME | SND_ASYNC);
				m_fTimer = 0;
			}
		break;
	}

	// NOTE: For sound you also can use MIDI but it's Win32 API it is a bit hard
	// see msdn reference: http://msdn.microsoft.com/en-us/library/ms711640.aspx
	// In this case you can use a C++ wrapper for it. See the following article:
	// http://www.codeproject.com/KB/audio-video/midiwrapper.aspx (with code also)
}

//-----------------------------------------------------------------------------
// Name : Draw()
// Desc : Draws mario or the mario exposion and mario's bullets (more like lasers)
//-----------------------------------------------------------------------------
void CMario::Draw()
{
	if (m_bMario) {
		if (m_bExplosion) {
			m_pExplosionSprite->draw();
		}
		else {
			m_pMarioSpriteAnimated->draw();
		}
	}

	m_lMarioBullets->Draw();
}

//-----------------------------------------------------------------------------
// Name : MoveMario(ULONG ulDirection)
// Desc : Moves mario left or right(depending on his rotation) when left/right arrows are pressed
//-----------------------------------------------------------------------------
void CMario::MoveMario(ULONG ulDirection)
{
	Vec2 &constrain = marioPosition();

	int x_max = GetSystemMetrics(SM_CXSCREEN);
	int y_max = GetSystemMetrics(SM_CYSCREEN);

	if (ulDirection & CMario::DIR_LEFT && m_bRotationState == 0 && constrain.x > 0 + 100 / 2) {
		m_pSpriteMario->mVelocity.x -= .9;
	}
	else if (ulDirection & CMario::DIR_RIGHT && m_bRotationState == 1 && constrain.x < x_max - 143 / 2) {
		m_pSpriteMario->mVelocity.x += .9;
	}
	else
		m_pSpriteMario->mVelocity.x = 0;
}

//-----------------------------------------------------------------------------
// Name : MarioBulletMovement()
// Desc : Moves mario's bullets (more like lasers)
//-----------------------------------------------------------------------------
void CMario::MarioBulletMovement()
{
	//-------------------------Inlocuita cu replace din bullet

	/*int x_max = GetSystemMetrics(SM_CXSCREEN);
	if (m_bRotationState == true) {
	if (m_pFireSprite->mPosition.x < x_max + 300)
	m_pFireSprite->mPosition.x += 5;
	} else {
	if (m_pFireSprite->mPosition.x > 0)
	m_pFireSprite->mPosition.x -= 5;
	}*/

	m_lMarioBullets->BulletsAdvance();
}

//-----------------------------------------------------------------------------
// Name : Jump()
// Desc : Used for Mario's jump when the up arrow key is pressed and mario is on the ground
//-----------------------------------------------------------------------------
/*
void CMario::Jump()
{
	//jumping
	if (jump) {
		m_pSpriteMario->mPosition.y -= m_pSpriteMario->mVelocity.y;
		m_pSpriteMario->mVelocity.y -= gravity;
		if (m_bRotationState) {
			if (GetSystemMetrics(SM_CXSCREEN) > m_pSpriteMario->mPosition.x + 200) {
				m_pSpriteMario->mPosition.x += 200;
			}
			else m_pSpriteMario->mPosition.x += GetSystemMetrics(SM_CXSCREEN) - m_pSpriteMario->mPosition.x - 50;
		}
		else {
			if (0 < m_pSpriteMario->mPosition.x - 200) {
				m_pSpriteMario->mPosition.x -= 200;
			}
			else m_pSpriteMario->mPosition.x -= 0 + m_pSpriteMario->mPosition.x - 50;
		}
	}
	if (m_pSpriteMario->mPosition.y <= (GetSystemMetrics(SM_CXSCREEN) / 2.5) && m_pSpriteMario->mPosition.y>200) {
		jump = 0;
		gravity = 0;
	}
	else {
		m_pSpriteMario->mVelocity.y = 0;
	}
}

*/

void CMario::Jump() {
	if (jump) {
		if (m_pSpriteMario->mPosition.y > MAXIMUM_JUMP_HEIGHT)
		{
			m_pSpriteMario->mPosition.y -= 10;

			if (m_bRotationState) {
				if (GetSystemMetrics(SM_CXSCREEN) > m_pSpriteMario->mPosition.x + 5) {
					m_pSpriteMario->mPosition.x += 5;
				}
				else m_pSpriteMario->mPosition.x += GetSystemMetrics(SM_CXSCREEN) - m_pSpriteMario->mPosition.x - 50;
			}
			else {
				if (0 < m_pSpriteMario->mPosition.x - 5) {
					m_pSpriteMario->mPosition.x -= 5;
				}
				else m_pSpriteMario->mPosition.x -= 0 + m_pSpriteMario->mPosition.x - 50;
			}
		}
		else jump = 0;
	}
	else if (m_pSpriteMario->mPosition.y < PLAYER_INITIAL_POSITION && m_pSpriteMario->mPosition.y>MAXIMUM_JUMP_HEIGHT) {
		m_pSpriteMario->mPosition.y += 5;

		if (m_bRotationState) {
			if (GetSystemMetrics(SM_CXSCREEN) > m_pSpriteMario->mPosition.x + 5) {
				m_pSpriteMario->mPosition.x += 5;
			}
			else m_pSpriteMario->mPosition.x += GetSystemMetrics(SM_CXSCREEN) - m_pSpriteMario->mPosition.x - 50;
		}
		else {
			if (0 < m_pSpriteMario->mPosition.x - 5) {
				m_pSpriteMario->mPosition.x -= 5;
			}
			else m_pSpriteMario->mPosition.x -= 0 + m_pSpriteMario->mPosition.x - 50;
		}
	}
	else {
		m_pSpriteMario->mPosition.y = PLAYER_INITIAL_POSITION;
	}
}

//-----------------------------------------------------------------------------
// Name : MarioFire()
// Desc : Reinitialisez the bullet position whenever it is fired
//-----------------------------------------------------------------------------
void CMario::MarioFire()
{
	//---------------------------Inlocuita cu Shoot() din BulletList

	/*if (m_bRotationState == true) {
	m_pFireSprite->mPosition.x = m_pSpriteMario->mPosition.x + 60;
	m_pFireSprite->mPosition.y = m_pSpriteMario->mPosition.y + 50;
	} else {
	m_pFireSprite->mPosition.x = m_pSpriteMario->mPosition.x;
	m_pFireSprite->mPosition.y = m_pSpriteMario->mPosition.y + 60;
	}*/
	m_bFire = true;
	if (m_iBulletType == 2 && m_iNumberBulletSpecial > 0) {
		m_iNumberBulletSpecial--;
	}
	else {
		m_iBulletType = 1;
	}
	m_lMarioBullets->Shoot(m_pSpriteMario->mPosition, m_bRotationState, m_iBulletType);
}

//-----------------------------------------------------------------------------
// Name : marioPosition()
// Desc : Returns the position of mario on X and Y axis
//-----------------------------------------------------------------------------
Vec2& CMario::marioPosition()
{
	return m_pSpriteMario->mPosition;
}

//-----------------------------------------------------------------------------
// Name : Velocity()
// Desc : Returns the velocity of mario on X and Y axis
//-----------------------------------------------------------------------------
Vec2& CMario::Velocity()
{
	return m_pSpriteMario->mVelocity;
}

//-----------------------------------------------------------------------------
// Name : RotatePlayer()
// Desc : Rotates masrio with 180 degrees(on X)
//-----------------------------------------------------------------------------
void CMario::RotatePlayer(const BackBuffer *pBackBuffer)
{
	if (player_to_the_right == true) {
		player_to_the_right = false;
	}
	else {
		player_to_the_right = true;
	}
	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = 128;
	r.bottom = 128;

	if (m_bRotationState == true) {
		m_pMarioSpriteAnimated = new AnimatedSprite("data/mario2.bmp", "data/m.bmp", r, 16);
		m_pMarioSpriteAnimated->setBackBuffer(pBackBuffer);
		m_bMario = false;
		m_iMarioFrame = 0;
		m_bRotationState = false;
	}
	else {
		m_pMarioSpriteAnimated = new AnimatedSprite("data/mario.bmp", "data/mario0.bmp", r, 16);
		m_pMarioSpriteAnimated->setBackBuffer(pBackBuffer);
		m_bMario = false;
		m_iMarioFrame = 0;
		m_bRotationState = true;
	}

	Mario();
}

//-----------------------------------------------------------------------------
// Name : Mario()
// Desc : Initialises mario's walking animation
//-----------------------------------------------------------------------------
void CMario::Mario()
{
	m_pMarioSpriteAnimated->mPosition = m_pSpriteMario->mPosition;
	m_pMarioSpriteAnimated->SetFrame(0);
	//PlaySound("data/explosion.wav", NULL, SND_FILENAME | SND_ASYNC);
	m_bMario = true;
}

//-----------------------------------------------------------------------------
// Name : AdvanceMario()
// Desc : Goes to the next mario walking animation frame
//-----------------------------------------------------------------------------
bool CMario::AdvanceMario()
{
	if (m_bMario) {
		m_pMarioSpriteAnimated->mPosition = m_pSpriteMario->mPosition;
		if (m_iMarioFrame == 4)
			m_iMarioFrame = 0;
		m_pMarioSpriteAnimated->SetFrame(m_iMarioFrame++);
		if (m_iMarioFrame == m_pMarioSpriteAnimated->GetFrameCount()) {
			m_bMario = false;
			m_iMarioFrame = 0;
			m_pSpriteMario->mVelocity = Vec2(0, 0);
			m_eSpeedState = SPEED_STOP;
			return false;
		}
	}
	return true;
}

//-----------------------------------------------------------------------------
// Name : ExplodeMario()
// Desc : Initialises the mario explosion
//-----------------------------------------------------------------------------
void CMario::ExplodeMario()
{
	m_pExplosionSprite->mPosition = m_pSpriteMario->mPosition;
	m_pExplosionSprite->SetFrame(0);
	m_bExplosion = true;
}

//-----------------------------------------------------------------------------
// Name : AdvanceExplosionMario()
// Desc : Goes to the next mario explosion frame or stops the mario explosion animation
//-----------------------------------------------------------------------------
bool CMario::AdvanceExplosionMario()
{
	if (m_bExplosion) {
		m_pExplosionSprite->mPosition = m_pSpriteMario->mPosition;
		m_pExplosionSprite->SetFrame(m_iExplosionFrame++);
		if (m_iExplosionFrame == m_pExplosionSprite->GetFrameCount()) {
			m_bExplosion = false;
			m_iExplosionFrame = 0;
			m_pSpriteMario->mVelocity = Vec2(0, 0);
			m_eSpeedState = SPEED_STOP;
			return false;
		}
	}
	return true;
}