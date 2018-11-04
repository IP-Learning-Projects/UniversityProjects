//-----------------------------------------------------------------------------
// File: CGameApp.cpp
//
// Desc: Game Application class, this is the central hub for all app processing
//
// Original design by Adam Hoult & Gary Simmons. Modified by Mihai Popescu.
//-----------------------------------------------------------------------------
#include <iostream>
#include <fstream>
using namespace std;

//-----------------------------------------------------------------------------
// CGameApp Specific Includes
//-----------------------------------------------------------------------------
#include "CGameApp.h"
extern HINSTANCE g_hInst;
// Globals.

//-----------------------------------------------------------------------------
// CGameApp Member Functions
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Name : CGameApp () (Constructor)
// Desc : CGameApp Class Constructor
//-----------------------------------------------------------------------------
CGameApp::CGameApp()
{
	// Reset / Clear all required values
	m_hWnd = NULL;
	m_hIcon = NULL;
	m_hMenu = NULL;
	m_pBBuffer = NULL;
	m_pPlayer = NULL;
	m_pEnemy = NULL;
	m_LastFrameRate = 0;

	m_iLevel = 1;
	barrierCounter = 0;
	srand(time(NULL));
}

//-----------------------------------------------------------------------------
// Name : ~CGameApp () (Destructor)
// Desc : CGameApp Class Destructor
//-----------------------------------------------------------------------------
CGameApp::~CGameApp()
{
	// Shut the engine down
	ShutDown();
}

//-----------------------------------------------------------------------------
// Name : InitInstance ()
// Desc : Initialises the entire Engine here.
//-----------------------------------------------------------------------------
bool CGameApp::InitInstance(LPCTSTR lpCmdLine, int iCmdShow)
{
	// Create the primary display device
	if (!CreateDisplay()) {
		ShutDown(); return false;
	}

	// Build Objects
	if (!BuildObjects()) {
		MessageBox(0, _T("Failed to initialize properly. Reinstalling the application may solve this problem.\nIf the problem persists, please contact technical support."), _T("Fatal Error"), MB_OK | MB_ICONSTOP);
		ShutDown();
		return false;
	}

	// Set up all required game states
	SetupGameState();

	// Success!
	return true;
}

//-----------------------------------------------------------------------------
// Name : CreateDisplay ()
// Desc : Create the display windows, devices etc, ready for rendering.
//-----------------------------------------------------------------------------
bool CGameApp::CreateDisplay()
{
	LPTSTR			WindowTitle = _T("GameFramework");
	LPCSTR			WindowClass = _T("GameFramework_Class");
	USHORT			Width = 800;
	USHORT			Height = 1600;
	RECT			rc;
	WNDCLASSEX		wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = CGameApp::StaticWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = g_hInst;
	wcex.hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_ICON));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = WindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON));

	if (RegisterClassEx(&wcex) == 0)
		return false;

	// Retrieve the final client size of the window
	::GetClientRect(m_hWnd, &rc);
	m_nViewX = rc.left;
	m_nViewY = rc.top;
	m_nViewWidth = rc.right - rc.left;
	m_nViewHeight = rc.bottom - rc.top;

	m_hWnd = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, Width, Height, NULL, NULL, g_hInst, this);

	if (!m_hWnd)
		return false;
	/////////////////////////////////////////////////////////////////////////////////////////
	// Show the window
	ShowWindow(m_hWnd, SW_SHOWMAXIMIZED);

	// Success!!
	return true;
}

//-----------------------------------------------------------------------------
// Name : Scrolling()
// Desc : Create the scrolling background
//-----------------------------------------------------------------------------
void CGameApp::Scrolling()
{
	y_bg1 = y_bg1 - 1;
	y_bg2 = y_bg2 - 1;
	if (y_bg2 == 0) {
		y_bg1 = 1152;
	}
	if (y_bg1 == 0) {
		y_bg2 = 1152;
	}
}

//-----------------------------------------------------------------------------
// Name : UpdateLivesAndScore()
// Desc : Decrements Mario's lives when hit
//-----------------------------------------------------------------------------
void CGameApp::UpdateLivesAndScore() {
	static UINT			fTimer;

	//detectare ciocnire player si enemy
	if (m_pPlayer->CollisionDetection(m_pMario->m_pSpriteMario, m_pEnemy->m_pSpriteEnemy)) {
		MarioWasHit = 1;
	}
	if (MarioWasHit && !m_pPlayer->CollisionDetection(m_pMario->m_pSpriteMario, m_pEnemy->m_pSpriteEnemy)) {
		MarioWasHit = 0;
		m_bEnemyOnTheScreen = false;
		m_pPlayer->lives--;
		m_pPlayer->points++;
	}

	//detectare ciocnire player si bariera
	if (m_pPlayer->CollisionDetection(m_pMario->m_pSpriteMario, m_pBarrier->m_pSpriteBarrier)) {
		MarioWasHitByBarrier = 1;
	}
	if (MarioWasHitByBarrier && (!m_pPlayer->CollisionDetection(m_pMario->m_pSpriteMario, m_pBarrier->m_pSpriteBarrier))) {
		MarioWasHitByBarrier = 0;
		m_pPlayer->lives--;
	}
	if (m_pPlayer->CollisionDetection(m_pMario->m_pSpriteMario, m_pBarrier1->m_pSpriteBarrier)) {
		MarioWasHitByBarrier1 = 1;
	}
	if (MarioWasHitByBarrier1 && !m_pPlayer->CollisionDetection(m_pMario->m_pSpriteMario, m_pBarrier1->m_pSpriteBarrier)) {
		MarioWasHitByBarrier1 = 0;
		m_pPlayer->lives--;
	}
	//detectare si ciocnire cu crate
	if (m_pPlayer->CollisionDetection(m_pMario->m_pSpriteMario, m_pCrateLife->m_pCrateSprite)) {
		m_pPlayer->lives++;
		m_pCrateLife->CrateIsHit();
		m_pCrateLife->RespawnCrate();
	}
	if (m_pPlayer->CollisionDetection(m_pMario->m_pSpriteMario, m_pCrateScore->m_pCrateSprite)) {
		m_pPlayer->points++;
		m_pCrateScore->CrateIsHit();
		m_pCrateScore->RespawnCrate();
	}
	if (m_pPlayer->CollisionDetection(m_pMario->m_pSpriteMario, m_pCrateAmmo->m_pCrateSprite)) {
		m_pMario->m_iNumberBulletSpecial++;
		m_pCrateAmmo->CrateIsHit();
		m_pCrateAmmo->RespawnCrate();
	}
	//detectare ciocnire player si bullet enemy
	if (m_pPlayer->CollisionDetection(m_pMario->m_pSpriteMario, m_pEnemy->m_pEnemyFireSprite)) {
		MarioWasShot = 1;
	}
	if (MarioWasShot && !m_pPlayer->CollisionDetection(m_pMario->m_pSpriteMario, m_pEnemy->m_pEnemyFireSprite)) {
		MarioWasShot = 0;
		if (!MarioWasHit) {
			m_pPlayer->lives--;
			m_pEnemy->m_bEnemyFire = false;
		}
	}

	if (m_pMario->m_lMarioBullets->Collision(m_pEnemy->m_pSpriteEnemy)) {
		if (m_pMario->m_iBulletType == 1) {
			m_pEnemy->m_iEnemyLives--;
			m_pPlayer->points++;
		} else {
			m_pEnemy->m_iEnemyLives -= 2;
			m_pPlayer->points += 2;
		}
		if (m_pEnemy->m_iEnemyLives <= 0)
			m_bEnemyOnTheScreen = false;
		m_pMario->m_lMarioBullets->EraseFirstElement();
	}

	if (m_pPlayer->points >= 10 && m_pPlayer->points < 20) m_iLevel = 2;
	if (m_pPlayer->points >= 20) m_iLevel = 3;
}

//-----------------------------------------------------------------------------
// Name : GameAdvance()
// Desc : Implements things that must be checked/done at each frame
//-----------------------------------------------------------------------------
void CGameApp::GameAdvance() {
	if (m_iLevel > 1) {
		enemyFireCount++;
		//the enemy fires a bullet once every 200 frames
		if (enemyFireCount == 200) {
			m_pEnemy->EnemyFire();
			enemyFireCount = 0;
		}
	}

	//------------------
	//daca inamicul iese din ecran sau daca e impuscat
	if (m_pEnemy->m_pSpriteEnemy->mPosition.x < 0) {
		m_bEnemyOnTheScreen = false;
	}
	/*
	if (m_bEnemyOnTheScreen == false) {
		m_iNewEnemyCounter++;
		if (m_iNewEnemyCounter == 100) {
			->InsertNewPlayer(m_pBBuffer);
			m_bEnemyOnTheScreen = true;
			m_iNewEnemyCounter = 0;
		}
	}*/

	if (m_bEnemyOnTheScreen == false) {
		m_pEnemy->InsertNewPlayer(m_pBBuffer);
		m_bEnemyOnTheScreen = true;
	}

	barrierCounter++;
	if (barrierCounter == randomNumber) {
		barrierCounter = 0;
		randomNumber = rand() % 100 + 2800;//NR RANDOM INTRE 1400 SI 1500
		m_pBarrier->RespawnBarrier();
	}
	if (barrierCounter == randomNumber / 2) {
		m_pBarrier1->RespawnBarrier();
	}

	if ((m_pEnemy->m_pSpriteEnemy->mPosition.x == m_pBarrier1->m_pSpriteBarrier->mPosition.x) || (m_pEnemy->m_pSpriteEnemy->mPosition.x == m_pBarrier->m_pSpriteBarrier->mPosition.x)) {
		m_pEnemy->enemyJump = 1;
	}
	if (m_pCrateAmmo->CallMedic() == false) {
		m_pCrateAmmo->RespawnCrate();
	}
	if (m_pCrateScore->CallMedic() == false) {
		m_pCrateScore->RespawnCrate();
	}
	if (m_pCrateLife->CallMedic() == false) {
		m_pCrateLife->RespawnCrate();
	}

}

//-----------------------------------------------------------------------------
// Name : BeginGame ()
// Desc : Signals the beginning of the physical post-initialisation stage.
//		From here on, the game engine has control over processing.
//-----------------------------------------------------------------------------
int CGameApp::BeginGame()
{	
	MSG		msg;
	static UINT			fTimer;

	// Start main loop
	while (true) {
		// Did we recieve a message, or are we idling ?

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			if (m_pPlayer->lives == 0) {
				m_pPlayer->gameOver = true;
			}
			// Advance Game Frame.
			FrameAdvance();
			GameAdvance();
			UpdateLivesAndScore();
		} // End If messages waiting
	} // Until quit message is receieved

	return 0;
}

//-----------------------------------------------------------------------------
// Name : ShutDown ()
// Desc : Shuts down the game engine, and frees up all resources.
//-----------------------------------------------------------------------------
bool CGameApp::ShutDown()
{
	// Release any previously built objects
	ReleaseObjects();

	// Destroy menu, it may not be attached
	if (m_hMenu) DestroyMenu(m_hMenu);
	m_hMenu = NULL;

	// Destroy the render window
	SetMenu(m_hWnd, NULL);
	if (m_hWnd) DestroyWindow(m_hWnd);
	m_hWnd = NULL;

	// Shutdown Success
	return true;
}

//-----------------------------------------------------------------------------
// Name : StaticWndProc () (Static Callback)
// Desc : This is the main messge pump for ALL display devices, it captures
//		the appropriate messages, and routes them through to the application
//		class for which it was intended, therefore giving full class access.
// Note : It is VITALLY important that you should pass your 'this' pointer to
//		the lpParam parameter of the CreateWindow function if you wish to be
//		able to pass messages back to that app object.
//-----------------------------------------------------------------------------
LRESULT CALLBACK CGameApp::StaticWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	// If this is a create message, trap the 'this' pointer passed in and store it within the window.
	if (Message == WM_CREATE) SetWindowLong(hWnd, GWL_USERDATA, (LONG)((CREATESTRUCT FAR *)lParam)->lpCreateParams);

	// Obtain the correct destination for this message
	CGameApp *Destination = (CGameApp*)GetWindowLong(hWnd, GWL_USERDATA);

	// If the hWnd has a related class, pass it through
	if (Destination) return Destination->DisplayWndProc(hWnd, Message, wParam, lParam);

	// No destination found, defer to system...
	return DefWindowProc(hWnd, Message, wParam, lParam);
}

// Name : LoadGame()
// Desc : Loads the last version of the game that was saved. Function is activated by pressing the "L" button
//-----------------------------------------------------------------------------
void CGameApp::LoadGame()
{
	ifstream myfile;
	myfile.open("data/save.txt");
	myfile >> readable;
	m_pMario->m_pSpriteMario->mPosition.x = readable;
	myfile >> readable;
	m_pMario->m_pSpriteMario->mPosition.y = readable;
	myfile >> readable;
	m_pEnemy->m_pSpriteEnemy->mPosition.x = readable;
	myfile >> readable;
	m_pEnemy->m_pSpriteEnemy->mPosition.x = readable;
	myfile >> readable;
	m_pPlayer->lives = readable;
	myfile >> readable;
	m_pPlayer->points = readable;
	myfile >> readable;
	m_iLevel = readable;
	myfile >> readable;
	m_pMario->m_iNumberBulletSpecial = readable;
}

// Name : SaveGame()
// Desc : Saves in a file the data needed in order to be able to recreate the exact same game conditions as from this moment.
//Function is activated by pressing the "I" button
//-----------------------------------------------------------------------------
void CGameApp::SaveGame()
{
	ofstream myfile;
	myfile.open("data/save.txt");
	myfile << m_pMario->m_pSpriteMario->mPosition.x << endl;
	myfile << m_pMario->m_pSpriteMario->mPosition.y << endl;
	myfile << m_pEnemy->m_pSpriteEnemy->mPosition.x << endl;
	myfile << m_pEnemy->m_pSpriteEnemy->mPosition.x << endl;
	myfile << m_pPlayer->lives << endl;
	myfile << m_pPlayer->points << endl;
	myfile << m_iLevel << endl;
	myfile << m_pMario->m_iNumberBulletSpecial << endl;
}
//-----------------------------------------------------------------------------
// Name : DisplayWndProc ()
// Desc : The display devices internal WndProc function. All messages being
//		passed to this function are relative to the window it owns.
//-----------------------------------------------------------------------------
LRESULT CGameApp::DisplayWndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	static UINT			fTimer;

	// Determine message type
	switch (Message) {
	case WM_CREATE: {
		break;
	}

	case WM_CLOSE: {
		PostQuitMessage(0);
		break;
	}

	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}

	case WM_SIZE: {
		if (wParam == SIZE_MINIMIZED) {
			// App is inactive
			m_bActive = false;
		} // App has been minimized
		else {
			// App is active
			m_bActive = true;

			// Store new viewport sizes
			m_nViewWidth = LOWORD(lParam);
			m_nViewHeight = HIWORD(lParam);
		} // End if !Minimized

		break;
	}

	case WM_LBUTTONDOWN: {
		// Capture the mouse
		SetCapture(m_hWnd);
		GetCursorPos(&m_OldCursorPos);

		break;
	}

	case WM_LBUTTONUP: {
		// Release the mouse
		ReleaseCapture();
		break;
	}

	case WM_KEYDOWN: {
		switch (wParam) {
			//Esc button. Shuts down the game
		case VK_ESCAPE: {
			PostQuitMessage(0);
			break;
		}
						//Return/Enter key. It must be pressed at the beginning of the game in order to animate the player and enemies
		case VK_RETURN: {
			fTimer = SetTimer(m_hWnd, 1, 250, NULL);
			m_pMario->Mario();
			m_pEnemy->Enemy();
			m_pPlayer->m_bStartGame = true;
			m_pEnemy->m_bStartGame = true;
			m_pBarrier->m_bBarrier = true;
			m_pBarrier1->m_bBarrier = true;
			break;
		}

						// Q button. Explodes the player
		case 0x51: {
			fTimer = SetTimer(m_hWnd, 1, 50, NULL);
			m_pMario->ExplodeMario();
			m_pMario->Mario();
			break;
		}
				   // Space button. Used for shooting
		case VK_SPACE: {
			m_pMario->MarioFire();
			break;
		}

					   //L button. Load the last Game version that has been saved.

		case 0x4C: {
			LoadGame();
			break;
		}
				   //I buttton. Save current game.
		case 0x49: {
			SaveGame();
			break;
		}

				   // Up button. Used for Jumping
		case 0x26: {
			if (m_pMario->m_pSpriteMario->mPosition.y >= PLAYER_INITIAL_POSITION) {
				m_pMario->jump = 1;
				m_pMario->gravity = -9.8;
				m_pMario->m_pSpriteMario->mVelocity.y = 200;
			}
			break;
		}

				   //R button. Rotates the player 180 degrees
		case 0x52: {
			m_pMario->RotatePlayer(m_pBBuffer);
			break;
		}

				   //N button. New Game
		case 0x4E: {
			//starts a new game
			m_pPlayer->gameOver = 0;
			SetupGameState();
			break;
		}
				   //B button: switch bullet type
		case 0x42: {
			if (m_pMario->m_iBulletType == 2) m_pMario->m_iBulletType = 1;
			else m_pMario->m_iBulletType++;
		}
		}

		break;
	}

	case WM_TIMER: {
		switch (wParam) {
		case 1:
			if (!m_pMario->AdvanceMario())
				KillTimer(m_hWnd, 1);
			if (!m_pEnemy->AdvanceEnemy())
				KillTimer(m_hWnd, 1);
			if (!m_pEnemy->AdvanceExplosionEnemy())
				KillTimer(m_hWnd, 1);
			if (!m_pMario->AdvanceExplosionMario())
				KillTimer(m_hWnd, 1);
		}
		break;
	}

	case WM_COMMAND: {
		break;
	}

	default: {
		return DefWindowProc(hWnd, Message, wParam, lParam);
	}
	} // End Message Switch
}

//-----------------------------------------------------------------------------
// Name : BuildObjects ()
// Desc : Build our demonstration meshes, and the objects that instance them
//-----------------------------------------------------------------------------
bool CGameApp::BuildObjects()
{
	m_pBBuffer = new BackBuffer(m_hWnd, m_nViewWidth, m_nViewHeight);
	m_pPlayer = new CPlayer(m_pBBuffer);
	m_pEnemy = new CEnemy(m_pBBuffer);
	m_pBarrier = new CBarrier(m_pBBuffer);
	m_pBarrier1 = new CBarrier(m_pBBuffer);
	m_pCrateLife = new Crate(m_pBBuffer, 2, TYPE_LIFE);
	m_pCrateScore = new Crate(m_pBBuffer,99, TYPE_SCORE);
	m_pCrateAmmo = new Crate(m_pBBuffer, 40, TYPE_AMMO);

	m_pMario = new CMario(m_pBBuffer);
	//m_hBMP = (HBITMAP)LoadImage(g_hInst, szFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	if (!m_imgBackground.LoadBitmapFromFile("data/background.bmp", GetDC(m_hWnd)) || !m_imgBackground1.LoadBitmapFromFile("data/background.bmp", GetDC(m_hWnd)))
		//return false;

	// Success!
		return true;
}

//-----------------------------------------------------------------------------
// Name : SetupGameState ()
// Desc : Sets up all the initial states required by the game.
//-----------------------------------------------------------------------------
void CGameApp::SetupGameState()
{
	m_pMario->m_pSpriteMario->mVelocity.y = 0;
	m_pMario->marioPosition() = Vec2(100.0, (PLAYER_INITIAL_POSITION));

	m_pEnemy->m_pSpriteEnemy->mVelocity.y = 0;
	m_pEnemy->enemyPosition() = Vec2(double(GetSystemMetrics(SM_CXSCREEN)), ENEMY_POSITION);

	m_pPlayer->lives = 3;
	m_pPlayer->points = 0;
	m_pBarrier->m_pSpriteBarrier->mPosition.x = GetSystemMetrics(SM_CXSCREEN);
	m_pBarrier1->m_pSpriteBarrier->mPosition.x = GetSystemMetrics(SM_CXSCREEN) + GetSystemMetrics(SM_CXSCREEN) / 2;
	int initialCrate = rand() % 99;
	if (initialCrate <= 0) {
		m_pCrateLife->SetShowCrate(true);
		m_pCrateScore->CrateIsHit();
		m_pCrateAmmo->CrateIsHit();
	}
	else if (initialCrate <= 99) {
		m_pCrateAmmo->SetShowCrate(true);
		m_pCrateLife->CrateIsHit();
		m_pCrateScore->CrateIsHit();
	}
		else {
			m_pCrateScore->SetShowCrate(true);
			m_pCrateLife->CrateIsHit();
			m_pCrateAmmo->CrateIsHit();
		}
	m_pCrateLife->CratePosition().x = GetSystemMetrics(SM_CXSCREEN) + 50;
	m_pCrateAmmo->CratePosition().x = GetSystemMetrics(SM_CXSCREEN) + 70;
	m_pCrateScore->CratePosition().x = GetSystemMetrics(SM_CXSCREEN) + 90;
	m_pPlayer->gameOver1->mPosition.x = 750;
	m_pPlayer->gameOver1->mPosition.y = 350;
	m_pPlayer->gameOver2->mPosition.x = 750;
	m_pPlayer->gameOver2->mPosition.y = 350;
}

//-----------------------------------------------------------------------------
// Name : ReleaseObjects ()
// Desc : Releases our objects and their associated memory so that we can
//		rebuild them, if required, during our applications life-time.
//-----------------------------------------------------------------------------
void CGameApp::ReleaseObjects()
{
	if (m_pPlayer != NULL) {
		delete m_pPlayer;
		m_pPlayer = NULL;
	}

	if (m_pEnemy != NULL) {
		delete m_pEnemy;
		m_pEnemy = NULL;
	}

	if (m_pBBuffer != NULL) {
		delete m_pBBuffer;
		m_pBBuffer = NULL;
	}

	if (m_pBarrier != NULL) {
		delete m_pBarrier;
		m_pBarrier = NULL;
	}
	/*if (m_pCrateAmmo != NULL) {
		delete m_pCrateAmmo;
		m_pCrateAmmo = NULL;
	}
	if (m_pCrateLife != NULL) {
		delete m_pCrateLife;
		m_pCrateLife = NULL;
	}
	if (m_pCrateScore != NULL) {
		delete m_pCrateScore;
		m_pCrateScore = NULL;
	}*/
}

//-----------------------------------------------------------------------------
// Name : FrameAdvance () (Private)
// Desc : Called to signal that we are now rendering the next frame.
//-----------------------------------------------------------------------------
void CGameApp::FrameAdvance()
{
	static TCHAR FrameRate[50];
	static TCHAR TitleBuffer[255];

	// Advance the timer
	m_Timer.Tick();

	// Skip if app is inactive
	if (!m_bActive) return;

	// Get / Display the framerate
	if (m_LastFrameRate != m_Timer.GetFrameRate()) {
		m_LastFrameRate = m_Timer.GetFrameRate(FrameRate, 50);
		sprintf_s(TitleBuffer, _T("Game : %s"), FrameRate);
		SetWindowText(m_hWnd, TitleBuffer);
	} // End if Frame Rate Altered

	// Poll & Process input devices
	ProcessInput();

	// Animate the game objects
	AnimateObjects();

	// Drawing the game objects
	DrawObjects();
}

//-----------------------------------------------------------------------------
// Name : ProcessInput () (Private)
// Desc : Simply polls the input devices and performs basic input operations
//-----------------------------------------------------------------------------
void CGameApp::ProcessInput()
{
	static UCHAR pKeyBuffer[256];
	ULONG		Direction = 0;
	ULONG		DirectionEnemy = 0;

	POINT		CursorPos;
	float		X = 0.0f, Y = 0.0f;

	// Retrieve keyboard state
	if (!GetKeyboardState(pKeyBuffer)) return;

	// Check the relevant keys

	if (pKeyBuffer[VK_LEFT] & 0xF0) {
		if (m_pMario->player_to_the_right == true) {
			m_pMario->RotatePlayer(m_pBBuffer);
		}

		Direction |= CPlayer::DIR_LEFT;

	}
	if (pKeyBuffer[VK_RIGHT] & 0xF0) {
		if (m_pMario->player_to_the_right == false) {
			m_pMario->RotatePlayer(m_pBBuffer);
		}
		Direction |= CPlayer::DIR_RIGHT;
	}

	// Move the player
	m_pMario->MoveMario(Direction);
	//Move the Enemy
	m_pEnemy->MoveEnemy(m_iLevel);
	//Jump
	m_pMario->Jump();

	m_pEnemy->Jump();
	//Make the bullet move after fire
	m_pMario->MarioBulletMovement();
	//Make the enemy bullet move after fire
	m_pEnemy->EnemyBulletMovement();
	//Move the barrier
	m_pBarrier->MoveBarrier();
	m_pBarrier1->MoveBarrier();
	m_pCrateScore->MoveCrate();
	m_pCrateAmmo->MoveCrate();
	m_pCrateLife->MoveCrate();
	
		
	// Now process the mouse (if the button is pressed)
	if (GetCapture() == m_hWnd) {
		// Hide the mouse pointer
		SetCursor(NULL);

		// Retrieve the cursor position
		GetCursorPos(&CursorPos);

		// Reset our cursor position so we can keep going forever :)
		SetCursorPos(m_OldCursorPos.x, m_OldCursorPos.y);
	} // End if Captured
}

//-----------------------------------------------------------------------------
// Name : AnimateObjects () (Private)
// Desc : Animates the objects we currently have loaded.
//-----------------------------------------------------------------------------
void CGameApp::AnimateObjects()
{
	m_pMario->Update(m_Timer.GetTimeElapsed());
	//m_pEnemy->Update(m_Timer.GetTimeElapsed());
}

//-----------------------------------------------------------------------------
// Name : DrawObjects () (Private)
// Desc : Draws the game objects
//-----------------------------------------------------------------------------
void CGameApp::DrawObjects()
{
	m_pBBuffer->reset();

	Scrolling();

	m_imgBackground.Paint(m_pBBuffer->getDC(), y_bg1, 0);
	m_imgBackground1.Paint(m_pBBuffer->getDC(), y_bg2, 0);
	if (m_pPlayer->gameOver) {
		m_pPlayer->DrawEndGame();
		m_pBBuffer->present();
		return;
	}
	if (m_bEnemyOnTheScreen == true) {
		m_pEnemy->Draw();
	}
	m_pMario->Draw();
	m_pBarrier->Draw();
	m_pBarrier1->Draw();

	m_pCrateScore->CrateIsOnScreen();

	m_pCrateAmmo->CrateIsOnScreen();

	m_pCrateLife->CrateIsOnScreen();




	//Draw the lives and score
	if (!m_pPlayer->gameOver) {
		HFONT hFont, eFont, lFont;
		hFont = CreateFont(36, 20, 100, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Times New Roman"));
		SelectObject(m_pBBuffer->getDC(), hFont);

		eFont = CreateFont(36, 20, -100, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Times New Roman"));
		sprintf(score, "%d", m_pPlayer->points);

		TextOut(m_pBBuffer->getDC(), 0, 50, "Score", 5);
		TextOut(m_pBBuffer->getDC(), 10, 100, score, strlen(score));

		SelectObject(m_pBBuffer->getDC(), eFont);
		sprintf(life, "%d", m_pPlayer->lives);
		TextOut(m_pBBuffer->getDC(), GetSystemMetrics(SM_CXSCREEN) - 200, 50, "Life", 4);
		TextOut(m_pBBuffer->getDC(), GetSystemMetrics(SM_CXSCREEN) - 115, 70, life, strlen(life));

		lFont = CreateFont(36, 20, 0, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Times New Roman"));
		SelectObject(m_pBBuffer->getDC(), lFont);
		sprintf(level, "%d", m_iLevel);
		TextOut(m_pBBuffer->getDC(), GetSystemMetrics(SM_CXSCREEN) / 2, 50, "Level", 5);
		TextOut(m_pBBuffer->getDC(), GetSystemMetrics(SM_CXSCREEN) / 2 + 130, 50, level, strlen(level));
	}
	m_pBBuffer->present();
}