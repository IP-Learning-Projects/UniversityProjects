//-----------------------------------------------------------------------------
// File: CGameApp.cpp
//
// Desc: Game Application class, this is the central hub for all app processing
//
// Original design by Adam Hoult & Gary Simmons. Modified by Mihai Popescu.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// CGameApp Specific Includes
//-----------------------------------------------------------------------------
#include "CGameApp.h"
extern HINSTANCE g_hInst;

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
	m_hWnd			= NULL;
	m_hIcon			= NULL;
	m_hMenu			= NULL;
	m_pBBuffer		= NULL;
	m_pPlayer		= NULL;
	m_LastFrameRate = 0;
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
bool CGameApp::InitInstance( LPCTSTR lpCmdLine, int iCmdShow )
{
	// Create the primary display device
	if (!CreateDisplay()) { ShutDown(); return false; }

	// Build Objects
	if (!BuildObjects()) 
	{ 
		MessageBox( 0, _T("Failed to initialize properly. Reinstalling the application may solve this problem.\nIf the problem persists, please contact technical support."), _T("Fatal Error"), MB_OK | MB_ICONSTOP);
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
	LPTSTR			WindowTitle		= _T("GameFramework");
	LPCSTR			WindowClass		= _T("GameFramework_Class");
	USHORT			Width = 800;
		USHORT			Height = 600;
	RECT			rc;
	WNDCLASSEX		wcex;


	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= CGameApp::StaticWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= g_hInst;
	wcex.hIcon			= LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_ICON));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= WindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON));

	if(RegisterClassEx(&wcex)==0)
		return false;

	// Retrieve the final client size of the window
	::GetClientRect( m_hWnd, &rc );
	m_nViewX		= rc.left;
	m_nViewY		= rc.top;
	m_nViewWidth	= rc.right - rc.left;
	m_nViewHeight	= rc.bottom - rc.top;

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
// Name : BeginGame ()
// Desc : Signals the beginning of the physical post-initialisation stage.
//		From here on, the game engine has control over processing.
//-----------------------------------------------------------------------------
int CGameApp::BeginGame()
{
	int ok = 2;
	int ok2 = 2;
	int ok3 = 2;
	MSG		msg;
	static UINT			fTimer;
	// Start main loop
	while(true) 
	{
		// Did we recieve a message, or are we idling ?
		if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ) 
		{
			if (msg.message == WM_QUIT) break;
			TranslateMessage( &msg );
			DispatchMessage ( &msg );
		} 
		else 
		{
			// Advance Game Frame.
				FrameAdvance();
				CollisionDetection();

			if (PlayerHit1) {
				fTimer = SetTimer(m_hWnd, 1, 50, NULL);
				m_pPlayer->Explode();
				ok = 1;
			}
			if (ok == 1 && PlayerHit1 == false) {
				m_pPlayer->score++;
				m_pPlayer2->lives--;
				ok = 0;
			}
			if (PlayerHit2) {
				fTimer = SetTimer(m_hWnd, 1, 50, NULL);
				m_pPlayer2->Explode();
				ok2 = 1;
				
				
			}
			if (ok2 == 1 && PlayerHit2 == false) {
				m_pPlayer2->score++;
				m_pPlayer->lives--;
				ok2 = 0;
			}
			if (col) {
				fTimer = SetTimer(m_hWnd, 1, 50, NULL);
				m_pPlayer->Explode();
				fTimer = SetTimer(m_hWnd, 1, 50, NULL);
				m_pPlayer2->Explode();
				ok3 = 1;
			
			}
			if (ok3 == 1 && col == false) {
				m_pPlayer->score++;
				m_pPlayer2->score++;
				m_pPlayer->lives--;
				m_pPlayer2->lives--;
				ok3 = 0;
			}
			
		} // End If messages waiting
	
	} // Until quit message is receieved

	return 0;
}
void CGameApp::GameOver() {
	HFONT hFont;
	hFont = CreateFont(125, 125, 0, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Times New Roman"));
	SelectObject(m_pBBuffer->getDC(), hFont);
	TextOut(m_pBBuffer->getDC(), 50, 400, "Game Over", 9);
}
//-----------------------------------------------------------------------------
// Name : ShutDown ()
// Desc : Shuts down the game engine, and frees up all resources.
//-----------------------------------------------------------------------------
bool CGameApp::ShutDown()
{
	// Release any previously built objects
	ReleaseObjects ( );
	
	// Destroy menu, it may not be attached
	if ( m_hMenu ) DestroyMenu( m_hMenu );
	m_hMenu		 = NULL;

	// Destroy the render window
	SetMenu( m_hWnd, NULL );
	if ( m_hWnd ) DestroyWindow( m_hWnd );
	m_hWnd		  = NULL;
	
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
	if ( Message == WM_CREATE ) SetWindowLong( hWnd, GWL_USERDATA, (LONG)((CREATESTRUCT FAR *)lParam)->lpCreateParams);

	// Obtain the correct destination for this message
	CGameApp *Destination = (CGameApp*)GetWindowLong( hWnd, GWL_USERDATA );
	
	// If the hWnd has a related class, pass it through
	if (Destination) return Destination->DisplayWndProc( hWnd, Message, wParam, lParam );
	
	// No destination found, defer to system...
	return DefWindowProc( hWnd, Message, wParam, lParam );
}

//-----------------------------------------------------------------------------
// Name : DisplayWndProc ()
// Desc : The display devices internal WndProc function. All messages being
//		passed to this function are relative to the window it owns.
//-----------------------------------------------------------------------------
LRESULT CGameApp::DisplayWndProc( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam )
{
	static UINT			fTimer;	

	// Determine message type
	switch (Message)
	{
		case WM_CREATE:
			break;
		
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		
		case WM_SIZE:
			if ( wParam == SIZE_MINIMIZED )
			{
				// App is inactive
				m_bActive = false;
			
			} // App has been minimized
			else
			{
				// App is active
				m_bActive = true;

				// Store new viewport sizes
				m_nViewWidth  = LOWORD( lParam );
				m_nViewHeight = HIWORD( lParam );
		
			
			} // End if !Minimized

			break;

		case WM_LBUTTONDOWN:
			// Capture the mouse
			SetCapture( m_hWnd );
			GetCursorPos( &m_OldCursorPos );
			break;

		case WM_LBUTTONUP:
			// Release the mouse
			ReleaseCapture( );
			break;

		case WM_KEYDOWN:
			switch(wParam)
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			case VK_RETURN:
				//fTimer = SetTimer(m_hWnd, 1, 50, NULL);
				//m_pPlayer->Explode();
				m_pPlayer->Fire();
				break;
			case 0x51:
				fTimer = SetTimer(m_hWnd, 1, 50, NULL);
				m_pPlayer2->Explode();
				break;
			case 0x52:
				m_pPlayer->Rotate(m_pBBuffer);
				
				break;
			case 0x54:
				m_pPlayer2->Rotate(m_pBBuffer);
				break;
			case VK_SPACE:
				
				m_pPlayer2->Fire();
				break;
			case 0x53:
				saveGame();
				break;
			case 0x44:
				loadGame();
				break;
			}
			break;

		case WM_TIMER:
			switch(wParam)
			{
			case 1:
				if(!m_pPlayer->AdvanceExplosion()  )
					KillTimer(m_hWnd, 1);
				if (!m_pPlayer2->AdvanceExplosion())
					KillTimer(m_hWnd, 1);


			}
			break;

		case WM_COMMAND:
			break;

		default:
			return DefWindowProc(hWnd, Message, wParam, lParam);

	} // End Message Switch
	
	return 0;
}

//-----------------------------------------------------------------------------
// Name : BuildObjects ()
// Desc : Build our demonstration meshes, and the objects that instance them
//-----------------------------------------------------------------------------
bool CGameApp::BuildObjects()
{
	m_pBBuffer = new BackBuffer(m_hWnd, m_nViewWidth, m_nViewHeight);
	m_pPlayer = new CPlayer(m_pBBuffer);
	m_pPlayer->spriteState = 4;
	m_pPlayer->Rotate(m_pBBuffer);
	//m_pPlayer->spriteState = 4;

	m_pBBuffer2 = new BackBuffer(m_hWnd, m_nViewWidth, m_nViewHeight);
	m_pPlayer2 = new CPlayer(m_pBBuffer);
	m_pPlayer2->spriteState = 2;
	m_pPlayer2->Rotate(m_pBBuffer);
	//m_pPlayer2->spriteState = 2;
	//m_hBMP = (HBITMAP)LoadImage(g_hInst, szFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	if(!m_imgBackground.LoadBitmapFromFile("data/Background.bmp", GetDC(m_hWnd) ) || !m_imgBackground1.LoadBitmapFromFile("data/Background.bmp", GetDC(m_hWnd)))
		return false;
		
	// Success!
	return true;
}

//-----------------------------------------------------------------------------
// Name : SetupGameState ()
// Desc : Sets up all the initial states required by the game.
//-----------------------------------------------------------------------------
void CGameApp::SetupGameState()
{
	m_pPlayer->Position() = Vec2(700, 700);
	m_pPlayer->lives = 3;
	m_pPlayer->score = 0;

	m_pPlayer2->Position() = Vec2(700, 200);
	m_pPlayer2->lives = 3;
	m_pPlayer2->score = 0;
	

}

//-----------------------------------------------------------------------------
// Name : ReleaseObjects ()
// Desc : Releases our objects and their associated memory so that we can
//		rebuild them, if required, during our applications life-time.
//-----------------------------------------------------------------------------
void CGameApp::ReleaseObjects( )
{
	if(m_pPlayer != NULL)
	{
		delete m_pPlayer;
		m_pPlayer = NULL;
	}

	if(m_pBBuffer != NULL)
	{
		delete m_pBBuffer;
		m_pBBuffer = NULL;
	}
}

//-----------------------------------------------------------------------------
// Name : FrameAdvance () (Private)
// Desc : Called to signal that we are now rendering the next frame.
//-----------------------------------------------------------------------------
void CGameApp::FrameAdvance()
{
	static TCHAR FrameRate[ 50 ];
	static TCHAR TitleBuffer[ 255 ];

	// Advance the timer
	m_Timer.Tick( );

	// Skip if app is inactive
	if ( !m_bActive ) return;
	
	// Get / Display the framerate
	if ( m_LastFrameRate != m_Timer.GetFrameRate() )
	{
		m_LastFrameRate = m_Timer.GetFrameRate( FrameRate, 50 );
		sprintf_s( TitleBuffer, _T("Game : %s"), FrameRate );
		SetWindowText( m_hWnd, TitleBuffer );

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
void CGameApp::ProcessInput( )
{
	static UCHAR pKeyBuffer[ 256 ];
	ULONG		Direction = 0;
	ULONG		Direction2 = 0;
	POINT		CursorPos;
	float		X = 0.0f, Y = 0.0f;

	// Retrieve keyboard state
	if ( !GetKeyboardState( pKeyBuffer ) ) return;

	// Check the relevant keys
	if ( pKeyBuffer[ VK_UP	] & 0xF0 ) Direction |= CPlayer::DIR_FORWARD;
	if ( pKeyBuffer[ VK_DOWN  ] & 0xF0 ) Direction |= CPlayer::DIR_BACKWARD;
	if ( pKeyBuffer[ VK_LEFT  ] & 0xF0 ) Direction |= CPlayer::DIR_LEFT;
	if ( pKeyBuffer[ VK_RIGHT ] & 0xF0 ) Direction |= CPlayer::DIR_RIGHT;

	if (pKeyBuffer[0x49] & 0xF0) Direction2 |= CPlayer::DIR_FORWARD;
	if (pKeyBuffer[0x4b] & 0xF0) Direction2 |= CPlayer::DIR_BACKWARD;
	if (pKeyBuffer[0x4a] & 0xF0) Direction2 |= CPlayer::DIR_LEFT;
	if (pKeyBuffer[0x4c] & 0xF0) Direction2 |= CPlayer::DIR_RIGHT;

	
	// Move the player
	m_pPlayer->Move(Direction, m_pBBuffer);
	m_pPlayer2->Move(Direction2, m_pBBuffer);

	// Now process the mouse (if the button is pressed)
	if ( GetCapture() == m_hWnd )
	{
		// Hide the mouse pointer
		SetCursor( NULL );

		// Retrieve the cursor position
		GetCursorPos( &CursorPos );

		// Reset our cursor position so we can keep going forever :)
		SetCursorPos( m_OldCursorPos.x, m_OldCursorPos.y );

	} // End if Captured
}

//-----------------------------------------------------------------------------
// Name : AnimateObjects () (Private)
// Desc : Animates the objects we currently have loaded.
//-----------------------------------------------------------------------------
void CGameApp::AnimateObjects()
{
	m_pPlayer->Update(m_Timer.GetTimeElapsed());
	m_pPlayer2->Update(m_Timer.GetTimeElapsed());
}

//-----------------------------------------------------------------------------
// Name : DrawObjects () (Private)
// Desc : Draws the game objects
//-----------------------------------------------------------------------------
void CGameApp::DrawObjects()
{
	
	

		m_pBBuffer->reset();
		DrawBackground();
		m_pPlayer->DrawScore(100, 100, m_pBBuffer);
		int x = GetSystemMetrics(SM_CXSCREEN);
		m_pPlayer2->DrawScore(x - 200, 100, m_pBBuffer);

		m_pPlayer->Draw();
		m_pPlayer2->Draw();
		if (m_pPlayer->lives <= 0 || m_pPlayer2->lives <= 0) {
			GameOver();
		}
		m_pBBuffer->present();



	
}

void CGameApp::DrawBackground() {

	bg1_y++; //bg1_y=0;
	bg2_y++; //bg2_y=-800;
	if (bg1_y == 800) {
		bg1_y = -800;
	}
	if (bg2_y == 800) {
		bg2_y = -800;
	}


	m_imgBackground.Paint(m_pBBuffer->getDC(), 0, bg1_y);
	m_imgBackground.Paint(m_pBBuffer->getDC(), 0, bg2_y);
}

void CGameApp::CollisionDetection() {
	if ( m_pPlayer->BulletPosition().x <  m_pPlayer2->PlayerPosition().x + 100
		&&  m_pPlayer->BulletPosition().x >  m_pPlayer2->PlayerPosition().x - 30
		&&  m_pPlayer->BulletPosition().y <  m_pPlayer2->PlayerPosition().y + 50
		&&  m_pPlayer->BulletPosition().y >  m_pPlayer2->PlayerPosition().y - 50)
		PlayerHit2 = true;
	else {
		PlayerHit2 = false;
	}
	if ( m_pPlayer2->BulletPosition().x    <   m_pPlayer->PlayerPosition().x + 70
		&&  m_pPlayer2->BulletPosition().x >   m_pPlayer->PlayerPosition().x - 70
		&&  m_pPlayer2->BulletPosition().y <   m_pPlayer->PlayerPosition().y + 50
		&&  m_pPlayer2->BulletPosition().y >   m_pPlayer->PlayerPosition().y - 50)
		PlayerHit1 = true;
	else {
		PlayerHit1 = false;
	}

	Vec2 rect1 =  m_pPlayer->PlayerPosition();
	Vec2 rect2 =  m_pPlayer2->PlayerPosition();

	double length = rect1.x - rect2.x;
	double width = rect1.y - rect2.y;
	double vertical_gap = abs(width) - 140;
	double horisontal_gap = abs(length) - 100;
	if (horisontal_gap <= 0 && vertical_gap <= 0 && !col)
		col = true;
	else {
		col = false;
	}

}

void CGameApp::saveGame() {
	staticLife.x = m_pPlayer->lives;
	staticLife.y = m_pPlayer2->lives;
	staticScore.x = m_pPlayer->score;
	staticScore.x = m_pPlayer2->score;
	staticPozitionPlayer1 = m_pPlayer->PlayerPosition();
	staticPozitionPlayer2 = m_pPlayer2->PlayerPosition();
}

void CGameApp::loadGame() {
	m_pPlayer->lives = staticLife.x;
	m_pPlayer2->lives = staticLife.y;
	m_pPlayer->score = staticScore.x;
	m_pPlayer2->score = staticScore.x;
	m_pPlayer->Position() = staticPozitionPlayer1;
	m_pPlayer2->Position() = staticPozitionPlayer2;
}
