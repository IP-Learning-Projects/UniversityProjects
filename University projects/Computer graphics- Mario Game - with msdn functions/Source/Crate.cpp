

#include "Crate.h"
#include "CGameApp.h"

Crate::Crate(const BackBuffer *pBackBuffer,int _chanceOfApparition, int _type) {
	screen_width = GetSystemMetrics(SM_CXSCREEN);
	screen_height = GetSystemMetrics(SM_CYSCREEN);
	srand(time(NULL));
	type = _type;
	if (type == TYPE_LIFE) {
		m_pCrateSprite = new Sprite("data/cratelife.bmp", RGB(284, 16, 230));
	}
	if (type == TYPE_SCORE) {
		m_pCrateSprite = new Sprite("data/cratescore.bmp", RGB(284, 16, 230));
	}
	if (type == TYPE_AMMO) {
		m_pCrateSprite = new Sprite("data/cratebullet.bmp", RGB(284, 16, 230));
	}
	m_pCrateSprite->setBackBuffer(pBackBuffer);
	m_pCrateSprite->mPosition.y = CRATE_INITIAL_POSITION;
	m_bCrate = false;
	chanceOfApparition = _chanceOfApparition;
	

}

Crate::~Crate()
{
	delete m_pCrateSprite;
}
void Crate::CrateIsOnScreen() {
	if (CratePosition().x < screen_width && CratePosition().y < screen_height && CratePosition().x > 0 && CratePosition().y >0) {
		Draw();
	}
}
void Crate::Draw() {
	if (m_bCrate) {
		m_pCrateSprite->draw();

	}
}

void Crate::MoveCrate() {
	m_pCrateSprite->mPosition.x -= 4;
}

Vec2& Crate::CratePosition()
{
	return m_pCrateSprite->mPosition;
}

void Crate::RespawnCrate()
{
	
	CratePosition().y = CRATE_INITIAL_POSITION;

	if (type == TYPE_LIFE) {
		if (rand() % 800 == (chanceOfApparition)) {
			CratePosition().x = GetSystemMetrics(SM_CXSCREEN) + 50;
			m_bCrate = true;
			Draw();
		}
	}
	if (type == TYPE_SCORE) {
		if (rand() % 600 == (chanceOfApparition)) {
			CratePosition().x = GetSystemMetrics(SM_CXSCREEN) +100;
			m_bCrate = true;
			Draw();
			
		}
	}
	if (type == TYPE_AMMO) {
		if (rand() % 900 == (chanceOfApparition)) {
			CratePosition().x = GetSystemMetrics(SM_CXSCREEN) + 150;
			m_bCrate = true;
			Draw();
			
		}
	}

	///if (rand() % 100 <= (chanceOfApparition /** baseChance*/)) {
	//	m_bCrate = true;

	//	CrateIsOnScreen();
	//}
	

}
void Crate::CrateIsHit() {
	CratePosition().x = GetSystemMetrics(SM_CXSCREEN) + 500;
	m_bCrate = false;
}
bool Crate::CallMedic() {
	return m_bCrate;
}
void Crate::SetShowCrate(bool x) {
	m_bCrate = x;
}