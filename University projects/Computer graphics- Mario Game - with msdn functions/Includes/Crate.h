#pragma once
#include <BackBuffer.h>
#include <Sprite.h>
#include <time.h>

#define CRATE_INITIAL_POSITION  GetSystemMetrics(SM_CYSCREEN) /1.7
#define	TYPE_AMMO 2
#define	TYPE_SCORE 1
#define	TYPE_LIFE 0


class Crate {
private:
	
	

	//Screen variables
	int															screen_width;
	int															screen_height;
	bool														m_bCrate;

public:
	Sprite * m_pCrateSprite2;

	Sprite*														m_pCrateSprite;
	//Constructor
	Crate(const BackBuffer *pBackBuffer, int _chanceOfApparition, int type);
	//destructor
	virtual														~Crate();
	//Advancing crates
	void														MoveCrate();
	//Respawn crates with a chance
	void														RespawnCrate();
	//Draw function to print on the screen
	void														Draw();
	//
	Vec2&														CratePosition();
	//base chance of apparition
	float														baseChance = 0.1;
	int															chanceOfApparition;
	int															type;
	//crate is on screen
	void														CrateIsOnScreen();
	void														CrateIsHit();
	bool														CallMedic();
	void														SetShowCrate(bool x);

};