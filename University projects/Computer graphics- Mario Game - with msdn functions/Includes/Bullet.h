#pragma once
#include <BackBuffer.h>
#include <Sprite.h>

//Define the 4 cardinal points
#define NORTH 2
#define SOUTH 3
#define WEST 0
#define EAST 1

//Bullet speed
#define BULLET_MOVEMENT_RATE 5.0

//Sprite offsets (sprite dimensions ex 100x140)
#define X_OFFSET 40
#define Y_OFFSET 40

class Bullet
{
private:
	Sprite * m_pBullet;
	Sprite * m_pBulletSpecial;
	int direction;

	//Screen variables
	int screen_width;
	int screen_height;
public:
	//Constructor
	Bullet(const BackBuffer *pBackBuffer, Vec2 &starting_position, int bullet_direction, int bulletType);
	//Advancing bullets
	void BulletAdvance();

	//Checks whether a bullet is on screen or not
	bool isOnScreen();

	//Draw function to print on the screen
	void Draw();

	//== operator used by STL list
	bool operator==(const Bullet &b1);

	Vec2& bulletPosition();
};