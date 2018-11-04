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
	//m_pSprite = new Sprite("data/planeimg.bmp", "data/planemask.bmp");
	m_pSprite = new Sprite("data/planeimgandmask.bmp", RGB(0xff,0x00, 0xff));
	
	m_pSprite->setBackBuffer( pBackBuffer );
	m_eSpeedState = SPEED_STOP;
	m_fTimer = 0;

	// Animation frame crop rectangle
	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = 128;
	r.bottom = 128;

	left = 1;

	m_pExplosionSprite	= new AnimatedSprite("data/explosion.bmp", "data/explosionmask.bmp", r, 16);
	m_pExplosionSprite->setBackBuffer( pBackBuffer );
	m_bExplosion		= false;
	m_iExplosionFrame	= 0;

	q_pExplosionSprite = new AnimatedSprite("data/ex.bmp", "data/exmask.bmp", r, 16);
	q_pExplosionSprite->setBackBuffer(pBackBuffer);
	q_bExplosion = false;
	q_iExplosionFrame = 0;
	
	m_pFireSprite = new AnimatedSprite("data/red_fire.bmp", "data/red_fire.bmp", r, 1);
	m_pFireSprite->setBackBuffer(pBackBuffer);
	m_bFire = false;


	
}

//-----------------------------------------------------------------------------
// Name : ~CPlayer () (Destructor)
// Desc : CPlayer Class Destructor
//-----------------------------------------------------------------------------
CPlayer::~CPlayer()
{
	delete m_pSprite;
	delete m_pExplosionSprite;
	delete q_pExplosionSprite;
	
}

void CPlayer::Update(float dt)
{
	// Update sprite
	m_pSprite->update(dt);
	

	// Get velocity
	double v = m_pSprite->mVelocity.Magnitude();

	// NOTE: for each async sound played Windows creates a thread for you
	// but only one, so you cannot play multiple sounds at once.
	// This creation/destruction of threads also leads to bad performance
	// so this method is not recommanded to be used in complex projects.

	// update internal time counter used in sound handling (not to overlap sounds)
	m_fTimer += dt;

	// A FSM is used for sound manager 
	switch(m_eSpeedState)
	{
	case SPEED_STOP:
		if(v > 35.0f)
		{
			m_eSpeedState = SPEED_START;
			PlaySound("data/jet-start.wav", NULL, SND_FILENAME | SND_ASYNC);
			m_fTimer = 0;
		}
		break;
	case SPEED_START:
		if(v < 25.0f)
		{
			m_eSpeedState = SPEED_STOP;
			PlaySound("data/jet-stop.wav", NULL, SND_FILENAME | SND_ASYNC);
			m_fTimer = 0;
		}
		else
			if(m_fTimer > 1.f)
			{
				PlaySound("data/jet-cabin.wav", NULL, SND_FILENAME | SND_ASYNC);
				m_fTimer = 0;
			}
		break;
	}

	// NOTE: For sound you also can use MIDI but it's Win32 API it is a bit hard
	// see msdn reference: http://msdn.microsoft.com/en-us/library/ms711640.aspx
	// In this case you can use a C++ wrapper for it. See the following article:
	// http://www.codeproject.com/KB/audio-video/midiwrapper.aspx (with code also)
}

void CPlayer::Draw()
{
	if (!m_bExplosion) {
		m_pSprite->draw();
	}
	else {
		m_pExplosionSprite->draw();
	}

	if (m_bFire) {
		m_pFireSprite->draw();
	}

}

void CPlayer::Move(ULONG ulDirection, const BackBuffer *pBackBuffer)
{
	Vec2 &constrain = Position();
	int x_max = GetSystemMetrics(SM_CXSCREEN);
	int y_max = GetSystemMetrics(SM_CYSCREEN);
	if( ulDirection & CPlayer::DIR_LEFT && constrain.x >0+100/2 )
		m_pSprite->mVelocity.x -= 10;
	else if( ulDirection & CPlayer::DIR_RIGHT && constrain.x <x_max-143/2 )
		m_pSprite->mVelocity.x += 10;
	else 
		m_pSprite->mVelocity.x = 0;
	
	if( ulDirection & CPlayer::DIR_FORWARD && constrain.y >0 + 143/2)
		m_pSprite->mVelocity.y -= 10;

	else if( ulDirection & CPlayer::DIR_BACKWARD  && constrain.y <y_max - 143)
		m_pSprite->mVelocity.y += 10;
	else 
		m_pSprite->mVelocity.y = 0;


	if (m_pFireSprite->mPosition.x < x_max
		&& m_pFireSprite->mPosition.x > 0
		&& m_pFireSprite->mPosition.y > 0
		&& m_pFireSprite->mPosition.y < y_max) {
		switch (spriteState) {
			
			case 2: {
				
				m_pFireSprite->mPosition.x += 5;
				break;
			}
			case 3: {
				
				m_pFireSprite->mPosition.y += 5;
				break;
			}
			case 4: {
				
				m_pFireSprite->mPosition.x -= 5;
				break;
			}
			case 1: {
				
				m_pFireSprite->mPosition.y -= 5;
				break;
			}
		}
	}
		
	

}


Vec2& CPlayer::Position()
{
	return m_pSprite->mPosition;
}

Vec2& CPlayer::qPosition()
{
	return q_pSprite->mPosition;
}

Vec2& CPlayer::Velocity()
{
	return m_pSprite->mVelocity;
}

void CPlayer::Explode()
{
	m_pExplosionSprite->mPosition = m_pSprite->mPosition;
	m_pExplosionSprite->SetFrame(0);
	PlaySound("data/explosion.wav", NULL, SND_FILENAME | SND_ASYNC);
	m_bExplosion = true;
}

bool CPlayer::AdvanceExplosion()
{
	if(m_bExplosion)
	{
		m_pExplosionSprite->SetFrame(m_iExplosionFrame++);
		if(m_iExplosionFrame==m_pExplosionSprite->GetFrameCount())
		{
			m_bExplosion = false;
			m_iExplosionFrame = 0;
			m_pSprite->mVelocity = Vec2(0,0);
			m_eSpeedState = SPEED_STOP;
			return false;
		}
	}

	return true;
}


void CPlayer::QExplode()
{
	q_pExplosionSprite->mPosition = m_pSprite->mPosition;
	q_pExplosionSprite->SetFrame(0);
	PlaySound("data/explosion.wav", NULL, SND_FILENAME | SND_ASYNC);
	q_bExplosion = true;
}

bool CPlayer::QAdvanceExplosion()
{
	if (m_bExplosion)
	{
		q_pExplosionSprite->SetFrame(q_iExplosionFrame++);
		if (q_iExplosionFrame == q_pExplosionSprite->GetFrameCount())
		{
			q_bExplosion = false;
			q_iExplosionFrame = 0;
			m_pSprite->mVelocity = Vec2(0, 0);
			m_eSpeedState = SPEED_STOP;
			return false;
		}
	}

	return true;
}

void CPlayer::Fire() {
	if (spriteState == 1) {
		m_pFireSprite->mPosition.x = m_pSprite->mPosition.x + 50;
		m_pFireSprite->mPosition.y = m_pSprite->mPosition.y + 30 ;
		m_pFireSprite->SetFrame(0);
		m_bFire = true;
	}
	else if (spriteState == 2) {
		m_pFireSprite->mPosition.x = m_pSprite->mPosition.x + 50;
		m_pFireSprite->mPosition.y = m_pSprite->mPosition.y + 50;
		m_pFireSprite->SetFrame(0);
		m_bFire = true;
	}
	else if (spriteState == 3) {
		m_pFireSprite->mPosition.x = m_pSprite->mPosition.x + 50;
		m_pFireSprite->mPosition.y = m_pSprite->mPosition.y + 30;
		m_pFireSprite->SetFrame(0);
		m_bFire = true;
	}
	else {
		m_pFireSprite->mPosition.x = m_pSprite->mPosition.x - 60;
		m_pFireSprite->mPosition.y = m_pSprite->mPosition.y + 50;
		m_pFireSprite->SetFrame(0);
		m_bFire = true;
	}
	
}


/*	void CPlayer::CollisionDetection() {
	if (m_pEnemyFireSprite->mPosition.x < m_pSprite->mPosition.x + 100
		&& m_pEnemyFireSprite->mPosition.x > m_pSprite->mPosition.x - 30
		&& m_pEnemyFireSprite->mPosition.y < m_pSprite->mPosition.y + 50
		&& m_pEnemyFireSprite->mPosition.y > m_pSprite->mPosition.y - 50)
		EnemyHit = true;

	if (m_pFireSprite->mPosition.x < q_pSprite->mPosition.x + 70
		&& m_pFireSprite->mPosition.x > q_pSprite->mPosition.x - 70
		&& m_pFireSprite->mPosition.y < q_pSprite->mPosition.y + 50
		&& m_pFireSprite->mPosition.y > q_pSprite->mPosition.y - 50)
		PlayerHit = true;

	Vec2 rect1 = m_pSprite->mPosition;
	Vec2 rect2 = q_pSprite->mPosition;

	double length = rect1.x - rect2.x;
	double width = rect1.y - rect2.y;
	double vertical_gap = abs(width) - 140;
	double horisontal_gap = abs(length) - 100;
	if (horisontal_gap <= 0 && vertical_gap <= 0 && !col)
		col = true;

}
*/

Vec2 CPlayer::BulletPosition() {
	return m_pFireSprite->mPosition;
}
Vec2 CPlayer::PlayerPosition() {
	return m_pSprite->mPosition;
}

void CPlayer::Rotate(const BackBuffer *pBackBuffer) {
	int x = m_pSprite->mPosition.x;
	int y = m_pSprite->mPosition.y;


	switch (spriteState) {
		case 1: {
			m_pSprite = new Sprite("data/planeimgandmaskR.bmp", RGB(0xff, 0x00, 0xff));
			m_pSprite->setBackBuffer(pBackBuffer);
			spriteState++;
			m_pSprite->mPosition.x = x;
			m_pSprite->mPosition.y = y;
			break;
		}
		case 2: {
			m_pSprite = new Sprite("data/planeimgandmaskQ.bmp", RGB(0xff, 0x00, 0xff));
			m_pSprite->setBackBuffer(pBackBuffer);
			spriteState++;
			m_pSprite->mPosition.x = x;
			m_pSprite->mPosition.y = y;
			break;
		}
		case 3: {
			m_pSprite = new Sprite("data/planeimgandmaskL.bmp", RGB(0xff, 0x00, 0xff));
			m_pSprite->setBackBuffer(pBackBuffer);
			spriteState++;
			m_pSprite->mPosition.x = x;
			m_pSprite->mPosition.y = y;
			break;
		}
		case 4: {
			m_pSprite = new Sprite("data/planeimgandmask.bmp", RGB(0xff, 0x00, 0xff));
			m_pSprite->setBackBuffer(pBackBuffer);
			spriteState = 1;
			m_pSprite->mPosition.x = x;
			m_pSprite->mPosition.y = y;
			break;
		}
	}
}

void CPlayer::DrawScore(int x,int y, const BackBuffer *pBackBuffer) {
	sprintf(scoreChr, "%d", score);
	sprintf(lifeChr, "%d", lives);

	HFONT hFont;
	hFont = CreateFont(36, 20, -300, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Times New Roman"));
	SelectObject(pBackBuffer->getDC(), hFont);



	TextOut(pBackBuffer->getDC(), x, y, "Score", 5);
	TextOut(pBackBuffer->getDC(), x+100, y, scoreChr, strlen(scoreChr));
	TextOut(pBackBuffer->getDC(), x, y+100, "Life", 4);
	TextOut(pBackBuffer->getDC(), x+100, y+100, lifeChr, strlen(lifeChr));

}