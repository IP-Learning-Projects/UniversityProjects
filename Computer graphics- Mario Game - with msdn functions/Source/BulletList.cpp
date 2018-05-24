#include <BulletList.h>

//Constructor used to save the buffer for later use
//We are continuously adding new bullets
BulletList::BulletList(const BackBuffer * pBackBuffer)
{
	player_bullets = new std::vector<Bullet>;
	m_pBuffer = pBackBuffer;
}

//Destructor
BulletList::~BulletList()
{
	player_bullets->clear();
	m_pBuffer = NULL;
}

//Shoot function-> adds a new bullet to our list
void BulletList::Shoot(Vec2 &coordinates, int bullet_direction, int bulletType)
{
	player_bullets->push_back(Bullet(m_pBuffer, coordinates, bullet_direction, bulletType));
}

//Advances bullets on the screen and removes them when they exit the screen
//TO-DO: delete bullets whenever there a collision
void BulletList::BulletsAdvance()
{
	//Iterate trough the list

	for (auto i = player_bullets->begin(); i != player_bullets->end(); ++i) {
		//Check whether the bullet is on the screen
		if (i->isOnScreen()) {
			i->BulletAdvance();
			//Else delete it
		} else {
			assert(!player_bullets->empty());
			player_bullets->erase(i);
			break;
		}
	}
}

bool BulletList::Collision(Sprite* player) {
	int ok = 0;
	for (auto i = player_bullets->begin(); i != player_bullets->end(); ++i) {
		Vec2 bullet = i->bulletPosition();
		Vec2 pl = player->mPosition;

		double x = bullet.x - pl.x;
		double y = bullet.y - pl.y;

		//double vertical_gap = fabs(y) - Sprite1->height();
		//double horizontal_gap = fabs(x) - Sprite1->width();

		double vertical_gap = fabs(y) - 40;
		double horizontal_gap = fabs(x) - 40;

		if (vertical_gap < 0 && horizontal_gap < 0) {
			return true;
			ok = 1;
			break;
		}
	}
	if (ok == 0) return false;
}

//Draw function to print the bullets on the screen
void BulletList::Draw()
{
	//Exit if there is nothing to draw (empty list)
	if (player_bullets->empty()) {
		return;
	}

	for (std::vector<Bullet>::iterator i = player_bullets->begin(); i != player_bullets->end(); ++i) {
		i->Draw();
	}
}

void BulletList::EraseFirstElement() {
	player_bullets->erase(player_bullets->begin() + 0);
}