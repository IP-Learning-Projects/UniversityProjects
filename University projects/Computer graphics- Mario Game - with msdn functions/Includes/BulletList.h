#pragma once

#include <Vector>
#include <Vec2.h>
#include <BackBuffer.h>
#include <Bullet.h>

class BulletList
{
private:
	std::vector<Bullet> *player_bullets;
	const BackBuffer *m_pBuffer;

public:
	BulletList(const BackBuffer *pBackBuffer);
	~BulletList();

	void Shoot(Vec2 &coordinates, int bullet_direction, int bulletType);
	void BulletsAdvance();
	void Draw();

	bool Collision(Sprite* player);
	void BulletList::EraseFirstElement();
};