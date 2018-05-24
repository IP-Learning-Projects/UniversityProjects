#include "Bullet.h"
#include "CGameApp.h"
//Constructor
Bullet::Bullet(const BackBuffer *pBackBuffer, Vec2 &starting_position, int bullet_direction, int bulletType)
{
	switch (bulletType) {
	case 1:
		m_pBullet = new Sprite("data/player_laser.bmp", RGB(0, 0, 0));
		break;
	case 2:
		if (bullet_direction == EAST) {
			m_pBullet = new Sprite("data/rocketRight.bmp", RGB(0, 0, 0));
		}
		else {
			m_pBullet = new Sprite("data/rocketLeft.bmp", RGB(0, 0, 0));
		}
		break;
	}

	m_pBullet->mPosition = starting_position;
	m_pBullet->setBackBuffer(pBackBuffer);

	this->direction = bullet_direction;

	screen_width = GetSystemMetrics(SM_CXSCREEN);
	screen_height = GetSystemMetrics(SM_CYSCREEN);
}

//Moves the bullets on the screen
void Bullet::BulletAdvance()
{
	assert(direction <= 3 && direction >= 0);
	//Direction to move
	switch (direction) {
	case NORTH: {
		m_pBullet->mPosition.y -= BULLET_MOVEMENT_RATE;
		break;
	}

	case SOUTH: {
		m_pBullet->mPosition.y += BULLET_MOVEMENT_RATE;
		break;
	}

	case EAST: {
		m_pBullet->mPosition.x += BULLET_MOVEMENT_RATE;
		break;
	}

	case WEST: {
		m_pBullet->mPosition.x -= BULLET_MOVEMENT_RATE;
		break;
	}

	default: {
		exit(-2);
	}
	}//end direction switch
}

//Checks whether the bullet is on the screen or not
bool Bullet::isOnScreen()
{
	//if(m_pBullet->mPosition.x > 0 && m_pBullet->mPosition.x < screen_width  && m_pBullet->mPosition.y > 0 && m_pBullet->mPosition.y < screen_height)
	return m_pBullet->mPosition.x > 0 && m_pBullet->mPosition.x < screen_width  && m_pBullet->mPosition.y > 0 && m_pBullet->mPosition.y < screen_height;
}

void Bullet::Draw()
{
	m_pBullet->draw();
}

bool Bullet::operator==(const Bullet & b1)
{
	return this->m_pBullet == b1.m_pBullet;
}

Vec2& Bullet::bulletPosition()
{
	return m_pBullet->mPosition;
}