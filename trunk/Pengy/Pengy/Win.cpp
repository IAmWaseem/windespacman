#include "Win.h"
#include <tchar.h>

//////////////////////////////////////////////////////////////////
// Static Initialisation
//////////////////////////////////////////////////////////////////
static CWin * g_pCWin		= NULL;
HINSTANCE CWin::m_hInstance = GetModuleHandle(NULL);

//////////////////////////////////////////////////////////////////
// Connectivity WIN32 -> Class
//////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return g_pCWin->MsgProc(hWnd, uMsg, wParam, lParam);
}

//////////////////////////////////////////////////////////////////
// Constructors/Destructors
//////////////////////////////////////////////////////////////////
CWin::CWin()
{
	g_pCWin		 = this;

	this->m_hWnd = NULL;
	this->m_dwCreationFlags  = 0L;
	this->m_dwWindowStyle		= (WS_OVERLAPPEDWINDOW | WS_SYSMENU) & ~(WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME) ;
	this->m_dwExWindowStyle	= WS_EX_OVERLAPPEDWINDOW;
	this->m_dwCreationFlags	= SW_SHOW;
	this->m_PosX			= CW_USEDEFAULT;	
	this->m_PosY			= CW_USEDEFAULT;	
	this->m_dwCreationWidth		= 800;
	this->m_dwCreationHeight	= 600;
	this->m_hbrWindowColor	= (HBRUSH)(COLOR_WINDOW+1);
	this->m_hIcon			= LoadIcon(m_hInstance, (LPCTSTR)IDI_APPLICATION);
	this->m_strWindowTitle	= _T("Pengy the Pinguin");
	this->m_hMenu			= NULL; 	
}

CWin::~CWin()
{
}


//////////////////////////////////////////////////////////////////
// Functions
//////////////////////////////////////////////////////////////////
int CWin::Run()
{
	MSG msg;

	ZeroMemory( &msg, sizeof(msg) );
	
	while( msg.message != WM_QUIT )
	{
		short keystateLeft;
		short keystateUp;
		short keystateRight;
		short keystateDown;
		short keystateSpace;

		keystateSpace = GetAsyncKeyState(32);
		keystateLeft = GetAsyncKeyState(37);
		keystateUp = GetAsyncKeyState(38);
		keystateRight = GetAsyncKeyState(39);
		keystateDown = GetAsyncKeyState(40);

		if(keystateSpace != 0)
			MessageQueue::Inst()->sendMessage(CM_CHARACTER_SPACEBAR, NULL, NULL);
		if(keystateLeft != 0)
			MessageQueue::Inst()->sendMessage(CM_CHARACTER_LEFT, NULL, NULL);
		if(keystateUp != 0)
			MessageQueue::Inst()->sendMessage(CM_CHARACTER_UP, NULL, NULL);
		if(keystateRight != 0)
			MessageQueue::Inst()->sendMessage(CM_CHARACTER_RIGHT, NULL, NULL);
		if(keystateDown != 0)
			MessageQueue::Inst()->sendMessage(CM_CHARACTER_DOWN, NULL, NULL);

		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		} 
		else 
		{
			GameLoop();
		}
	}
	
	GameEnd();
	
	return msg.wParam;
}

HRESULT CWin::Create()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= m_hInstance;
	wcex.hIcon			= m_hIcon;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= m_hbrWindowColor;
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= _T("Skeleton");
	wcex.hIconSm		= NULL;

	::RegisterClassEx(&wcex);

	m_hWnd = ::CreateWindowEx(m_dwExWindowStyle,_T("Skeleton"), m_strWindowTitle, m_dwWindowStyle,
	  m_PosX, m_PosY, m_dwCreationWidth, m_dwCreationHeight, NULL, m_hMenu, m_hInstance, NULL);

	if (!m_hWnd)
	{
	  return FALSE;
	}

	graphics = ::GetDC(m_hWnd);
	GameInit();

	::ShowWindow(m_hWnd, m_dwCreationFlags);
	::UpdateWindow(m_hWnd);

	return TRUE;
}

LRESULT CWin::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int wmId;
	int wmEvent;

	if (!m_hWnd)
		m_hWnd = hWnd;
	switch (uMsg) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
   }
   return 0;
}
