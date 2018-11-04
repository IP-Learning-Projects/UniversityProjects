//-----------------------------------------------------------------------------
// File:	Enemy.cpp
//
// Desc: This file stores the enemy object class. This class performs tasks
//	   such as enemy movement, some minor physics as well as rendering.
//

#include "Enemy.h"

//-----------------------------------------------------------------------------
// Name : CEnemy () (Constructor)
// Desc : CEnemy Class Constructor
//-----------------------------------------------------------------------------
CEnemy::CEnemy(const BackBuffer *pBackBuffer)
{
	// Animation frame crop rectangle
	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = 128;
	r.bottom = 128;

	m_pSpriteEnemy = new Sprite("data/marioSp.bmp", RGB(0xff, 0x00, 0xff));
	m_pSpriteEnemy->setBackBuffer(pBackBuffer);

	//Enemy
	m_iEnemyType = 1;
	m_pEnemySpriteAnimated = new AnimatedSprite("data/2.bmp", "data/2m.bmp", r, 16);
	m_pEnemySpriteAnimated->setBackBuffer(pBackBuffer);
	m_bEnemy = false;
	m_iEnemyFrame = 0;
	m_pSpriteEnemy->mPosition.y = 100;

	//Explosion Enemy
	m_pExplosionSpriteEnemy = new AnimatedSprite("data/ex.bmp", "data/exmask.bmp", r, 16);
	m_pExplosionSpriteEnemy->setBackBuffer(pBackBuffer);
	m_bExplosionEnemy = false;
	m_iExplosionFrameEnemy = 0;

	m_pEnemyFireSprite = new AnimatedSprite("data/green_fire.bmp", "data/green_fire.bmp", r, 1);
	m_pEnemyFireSprite->setBackBuffer(pBackBuffer);
	m_bEnemyFire = false;

	m_iEnemyLives = 2;
}

//-----------------------------------------------------------------------------
// Name : ~CEnemy () (Destructor)
// Desc : CEnemy Class Destructor
//-----------------------------------------------------------------------------
CEnemy::~CEnemy()
{
	delete m_pSpriteEnemy;
	delete m_pEnemySpriteAnimated;
}

void CEnemy::Update(float dt)
{
	// Update sprite
	m_pSpriteEnemy->update(dt);

	// Get velocity
	double v = m_pSpriteEnemy->mVelocity.Magnitude();

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

void CEnemy::Jump()
{
	if (enemyJump) {
		if (m_pSpriteEnemy->mPosition.y > MAX_JUMP)
		{
			m_pSpriteEnemy->mPosition.y -= 10;
			if (GetSystemMetrics(SM_CXSCREEN) > m_pSpriteEnemy->mPosition.x - 5) {
				m_pSpriteEnemy->mPosition.x -= 5;
			}
			else m_pSpriteEnemy->mPosition.x -= GetSystemMetrics(SM_CXSCREEN) - m_pSpriteEnemy->mPosition.x - 50;
		}
		else enemyJump = 0;
	}
	else if (m_pSpriteEnemy->mPosition.y < ENEMY_POSITION && m_pSpriteEnemy->mPosition.y>MAX_JUMP) {
		m_pSpriteEnemy->mPosition.y += 5;
		if (GetSystemMetrics(SM_CXSCREEN) > m_pSpriteEnemy->mPosition.x - 5) {
			m_pSpriteEnemy->mPosition.x -= 5;
		}
		else m_pSpriteEnemy->mPosition.x += GetSystemMetrics(SM_CXSCREEN) - m_pSpriteEnemy->mPosition.x - 50;
	}
	else {
		m_pSpriteEnemy->mPosition.y = ENEMY_POSITION;
	}
}

//-----------------------------------------------------------------------------
// Name : Draw()
// Desc : Draws the anemy or the enemy exposion and the enemy bullet
//-----------------------------------------------------------------------------
void CEnemy::Draw()
{
	if (m_bEnemy) {
		if (m_bExplosionEnemy)
			m_pExplosionSpriteEnemy->draw();
		else m_pEnemySpriteAnimated->draw();
	}

	if (m_bEnemyFire)
		m_pEnemyFireSprite->draw();
}

//-----------------------------------------------------------------------------
// Name : MoveEnemy()
// Desc : Moves the enemy from right to left
//-----------------------------------------------------------------------------

void CEnemy::MoveEnemy(int level)
{
	if (m_bStartGame == 1) {
		if (level > 2)
			m_pSpriteEnemy->mPosition.x -= 4;
		else
			m_pSpriteEnemy->mPosition.x -= 2;
	}
}

//-----------------------------------------------------------------------------
// Name : EnemyBulletMovement()
// Desc : Moves the enemy bullet from right to left
//-----------------------------------------------------------------------------
void CEnemy::EnemyBulletMovement()
{
	m_pEnemyFireSprite->mPosition.x -= 5;
}

//-----------------------------------------------------------------------------
// Name : EnemyFre()
// Desc : Reinitialisez the enemy bullet position whenever it is fired
//-----------------------------------------------------------------------------
void CEnemy::EnemyFire()
{
	m_pEnemyFireSprite->mPosition.x = m_pSpriteEnemy->mPosition.x + 60;
	m_pEnemyFireSprite->mPosition.y = m_pSpriteEnemy->mPosition.y + 60;

	//m_pFireSprite->SetFrame(0);
	m_bEnemyFire = true;
}

//-----------------------------------------------------------------------------
// Name : enemyPosition()
// Desc : Returns the position of the enemy on X and Y axis
//-----------------------------------------------------------------------------
Vec2& CEnemy::enemyPosition()
{
	return m_pSpriteEnemy->mPosition;
}

//-----------------------------------------------------------------------------
// Name : ExplodeEnemy()
// Desc : Initialises the enemy explosion
//-----------------------------------------------------------------------------
void CEnemy::ExplodeEnemy()
{
	m_pExplosionSpriteEnemy->mPosition = m_pSpriteEnemy->mPosition;
	m_pExplosionSpriteEnemy->SetFrame(0);
	m_bExplosionEnemy = true;
}

//-----------------------------------------------------------------------------
// Name : AdvanceExplosionEnemy()
// Desc : Goes to the next enemy explosion frame or stops the enemy explosion animation
//-----------------------------------------------------------------------------
bool CEnemy::AdvanceExplosionEnemy()
{
	if (m_bExplosionEnemy) {
		m_pExplosionSpriteEnemy->mPosition = m_pSpriteEnemy->mPosition;
		m_pExplosionSpriteEnemy->SetFrame(m_iExplosionFrameEnemy++);
		if (m_iExplosionFrameEnemy == m_pExplosionSpriteEnemy->GetFrameCount()) {
			m_bExplosionEnemy = false;
			m_iExplosionFrameEnemy = 0;
			m_pSpriteEnemy->mVelocity = Vec2(0, 0);
			m_eSpeedState = SPEED_STOP;
			return false;
		}
	}
	return true;
}

//-----------------------------------------------------------------------------
// Name : Enemy()
// Desc : Initialises the enemy animation
//-----------------------------------------------------------------------------
void CEnemy::Enemy()
{
	m_pEnemySpriteAnimated->mPosition = m_pSpriteEnemy->mPosition;
	m_pEnemySpriteAnimated->SetFrame(0);
	//PlaySound("data/explosion.wav", NULL, SND_FILENAME | SND_ASYNC);
	m_bEnemy = true;
}

//-----------------------------------------------------------------------------
// Name : AdvanceEnemy()
// Desc : Goes to the next enemy animation frame
//-----------------------------------------------------------------------------
bool CEnemy::AdvanceEnemy()
{
	if (m_bEnemy) {
		m_pEnemySpriteAnimated->mPosition = m_pSpriteEnemy->mPosition;
		if (m_iEnemyFrame == 3)
			m_iEnemyFrame = 0;
		m_pEnemySpriteAnimated->SetFrame(m_iEnemyFrame++);
		if (m_iEnemyFrame == m_pEnemySpriteAnimated->GetFrameCount()) {
			m_bEnemy = false;
			m_iEnemyFrame = 0;
			m_pSpriteEnemy->mVelocity = Vec2(0, 0);
			m_eSpeedState = SPEED_STOP;
			return false;
		}
	}

	return true;
}

//-----------------------------------------------------------------------------
// Name : InsertNewPlayer(const BackBuffer *pBackBuffer)
// Desc : Inserts a new enemy with a different animation sprite
//-----------------------------------------------------------------------------
void CEnemy::InsertNewPlayer(const BackBuffer *pBackBuffer)
{
	m_pSpriteEnemy->mPosition.x = GetSystemMetrics(SM_CXSCREEN);
	m_pSpriteEnemy->mPosition.y = ENEMY_POSITION;

	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = 128;
	r.bottom = 128;

	m_iEnemyType++;
	if (m_iEnemyType == 9) //8 adversari diferiti
		m_iEnemyType = 1;

	switch (m_iEnemyType) {
	case 1:
		m_pEnemySpriteAnimated = new AnimatedSprite("data/2.bmp", "data/2m.bmp", r, 16);
		m_pEnemySpriteAnimated->setBackBuffer(pBackBuffer);
		m_bEnemy = false;
		m_iEnemyFrame = 0;
		break;
	case 2:
		m_pEnemySpriteAnimated = new AnimatedSprite("data/5.bmp", "data/5m.bmp", r, 16);
		m_pEnemySpriteAnimated->setBackBuffer(pBackBuffer);
		m_bEnemy = false;
		m_iEnemyFrame = 0;
		break;
	case 3:
		m_pEnemySpriteAnimated = new AnimatedSprite("data/3.bmp", "data/3m.bmp", r, 16);
		m_pEnemySpriteAnimated->setBackBuffer(pBackBuffer);
		m_bEnemy = false;
		m_iEnemyFrame = 0;
		break;
	case 4:
		m_pEnemySpriteAnimated = new AnimatedSprite("data/7.bmp", "data/7m.bmp", r, 16);
		m_pEnemySpriteAnimated->setBackBuffer(pBackBuffer);
		m_bEnemy = false;
		m_iEnemyFrame = 0;
		break;
	case 5:
		m_pEnemySpriteAnimated = new AnimatedSprite("data/1.bmp", "data/1m.bmp", r, 16);
		m_pEnemySpriteAnimated->setBackBuffer(pBackBuffer);
		m_bEnemy = false;
		m_iEnemyFrame = 0;
		break;
	case 6:
		m_pEnemySpriteAnimated = new AnimatedSprite("data/4.bmp", "data/4m.bmp", r, 16);
		m_pEnemySpriteAnimated->setBackBuffer(pBackBuffer);
		m_bEnemy = false;
		m_iEnemyFrame = 0;
		break;
	case 7:
		m_pEnemySpriteAnimated = new AnimatedSprite("data/6.bmp", "data/6m.bmp", r, 16);
		m_pEnemySpriteAnimated->setBackBuffer(pBackBuffer);
		m_bEnemy = false;
		m_iEnemyFrame = 0;
		break;
	case 8:
		m_pEnemySpriteAnimated = new AnimatedSprite("data/8.bmp", "data/8m.bmp", r, 16);
		m_pEnemySpriteAnimated->setBackBuffer(pBackBuffer);
		m_bEnemy = false;
		m_iEnemyFrame = 0;
		break;
	}
	m_iEnemyLives = 2;
	Enemy();
}