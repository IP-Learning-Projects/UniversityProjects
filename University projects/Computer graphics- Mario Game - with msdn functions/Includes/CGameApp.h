//-----------------------------------------------------------------------------
// File: CGameApp.h
//
// Desc: Game Application class, this is the central hub for all app processing
//
// Original design by Adam Hoult & Gary Simmons. Modified by Mihai Popescu.
//-----------------------------------------------------------------------------

#ifndef _CGAMEAPP_H_
#define _CGAMEAPP_H_

//-----------------------------------------------------------------------------
// CGameApp Specific Includes
//-----------------------------------------------------------------------------
#include "Main.h"
#include<iostream>
#include <fstream>
#include "CTimer.h"
#include "CPlayer.h"
#include "Enemy.h"
#include "BackBuffer.h"
#include "ImageFile.h"
#include "windows.h"
#include "Mario.h"
#include "Crate.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <Barrier.h>

using namespace std;

//-----------------------------------------------------------------------------
// Forward Declarations
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Main Class Declarations
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Name : CGameApp (Class)
// Desc : Central game engine, initialises the game and handles core processes.
//-----------------------------------------------------------------------------
class CGameApp
{
public:

	//-------------------------------------------------------------------------
	// Constructors & Destructors for This Class.
	//-------------------------------------------------------------------------
	CGameApp();
	virtual ~CGameApp();

	//-------------------------------------------------------------------------
	// Public Functions for This Class
	//-------------------------------------------------------------------------
	LRESULT	 DisplayWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
	bool		InitInstance(LPCTSTR lpCmdLine, int iCmdShow);
	int		 BeginGame();
	bool		ShutDown();
	void LoadGame();
	void SaveGame();
	void Scrolling();

private:

	//-------------------------------------------------------------------------
	// Private Functions for This Class
	//-------------------------------------------------------------------------
	bool		BuildObjects();
	void		ReleaseObjects();
	void		FrameAdvance();
	bool		CreateDisplay();
	void		ChangeDevice();
	void		SetupGameState();
	void		AnimateObjects();
	void		DrawObjects();
	void		ProcessInput();
	void		GameAdvance();
	void		UpdateLivesAndScore();
	bool		MarioWasShot = 0;
	bool		MarioWasHit = 0;
	bool		MarioWasHitByBarrier = 0;
	bool MarioWasHitByBarrier1 = 0;
	//-------------------------------------------------------------------------
	// Private Static Functions For This Class
	//-------------------------------------------------------------------------
	static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);

	//-------------------------------------------------------------------------
	// Private Variables For This Class
	//-------------------------------------------------------------------------
	CTimer				  m_Timer;			// Game timer
	ULONG				   m_LastFrameRate;	// Used for making sure we update only when fps changes.

	HWND					m_hWnd;			 // Main window HWND
	HICON				   m_hIcon;			// Window Icon
	HMENU				   m_hMenu;			// Window Menu

	bool					m_bActive;		  // Is the application active ?

	ULONG				   m_nViewX;		   // X Position of render viewport
	ULONG				   m_nViewY;		   // Y Position of render viewport
	ULONG				   m_nViewWidth;	   // Width of render viewport
	ULONG				   m_nViewHeight;	  // Height of render viewport

	POINT				   m_OldCursorPos;	 // Old cursor position for tracking
	HINSTANCE				m_hInstance;

	CImageFile				m_imgBackground;
	CImageFile				m_imgBackground1;

	BackBuffer*				m_pBBuffer;
	CPlayer*				m_pPlayer;
	CEnemy*					m_pEnemy;
	CMario*					m_pMario;
	CBarrier*				m_pBarrier;
	CBarrier*				m_pBarrier1;
	Crate*					m_pCrateScore;
	Crate*					m_pCrateLife;
	Crate*					m_pCrateAmmo;
	

	int m_iNewEnemyCounter;
	bool m_bEnemyOnTheScreen = true;
	float y_bg1 = 1;
	float y_bg2 = 1152;
	int enemyFireCount = 0;
	double readable;
	char life[100] = "";
	char score[100] = "";
	char level[100] = "";
	int barrierCounter = 0;
	int randomNumber = 3000; // un nr de frameuri care apoi va fi generat aleatoriu prin functia rand() pt a sti cand se respawneaza bariera
	int m_iLevel;
};

#endif // _CGAMEAPP_H_