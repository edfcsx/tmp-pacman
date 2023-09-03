/*******************************************************************************
// Window
//
// Cria��o:		02 Jul 2023
// Compilador:	Visual C++ 2022
//
// Descri��o:	A classe abstrai todos os detalhes de configura��o de
//				uma janela para um jogo.
*******************************************************************************/

#include "Window.h"
#include "Engine.h"

// -----------------------------------------------------------------------------
// Inicializa��o de membros est�ticos da classe
bool Window::windowKeys[256] = { 0 };				// estado do teclado/mouse
bool Window::windowCtrl[256] = { 0 };				// controle de teclado/mouse
int  Window::windowMouseX = 0;						// posi��o do mouse no eixo x
int  Window::windowMouseY = 0;						// posi��o do mouse no eixo y
int  Window::windowMouseWheel = 0;					// giro da roda do mouse


// -----------------------------------------------------------------------------
// Construtor

Window::Window()
{
	hInstance		= GetModuleHandle(NULL);				// identificador da aplica��o
	windowHandle	= 0;									// identificador da janela
	windowWidth		= GetSystemMetrics(SM_CXSCREEN);		// tamanho de largura da tela
	windowHeight	= GetSystemMetrics(SM_CYSCREEN);		// tamanho de altura da tela
	windowIcon		= LoadIcon(NULL, IDI_APPLICATION);		// icone padr�o de uma aplica��o
	windowCursor	= LoadCursor(NULL, IDC_ARROW);			// cursor padr�o de uma aplica��o
	windowColor		= RGB(0, 0, 0);							// cor de fundo padr�o preta
	windowTitle		= string("Windows Game");				// titulo padr�o de janela
	windowStyle		= WS_POPUP | WS_VISIBLE;				// estilo padr�o de tela cheia
	windowMode		= FULLSCREEN;							// modo padr�o de tela cheia
	windowPosX		= 0;									// posi��o inicial da janela no eixo x
	windowPosY		= 0;									// posi��o inicial da janela no eixo y
	windowCenterX	= windowWidth / 2.0f;					// centro da janela no eixo x
	windowCenterY	= windowHeight / 2.0f;					// centro da janela no eixo y
}

// -----------------------------------------------------------------------------

void Window::Mode(int mode)
{
	windowMode = mode;

	if (mode == WINDOWED)
	{
		windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE;
	}
	else {
		// modo tela cheia ou sem bordas
		windowStyle = WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE;
	}
}

// -----------------------------------------------------------------------------

void Window::Size(int width, int height)
{
	// define o tamanho da janela nas variaveis
	windowWidth = width;
	windowHeight = height;

	// calcula a posi��o do centro da janela
	windowCenterX = windowWidth / 2.0f;
	windowCenterY = windowHeight / 2.0f;

	// ajusta a posi��o da janela para o centro da tela
	windowPosX = GetSystemMetrics(SM_CXSCREEN) / 2 - windowWidth / 2;
	windowPosY = GetSystemMetrics(SM_CYSCREEN) / 2 - windowHeight / 2;
}

// -----------------------------------------------------------------------------

bool Window::KeyPress(int vkcode)
{
	if (windowCtrl[vkcode])
	{
		if (KeyDown(vkcode))
		{
			windowCtrl[vkcode] = false;
			return true;
		}
	}
	else if (KeyUp(vkcode))
	{
		windowCtrl[vkcode] = true;
	}

	return false;
}

// -----------------------------------------------------------------------------
bool Window::Create()
{
	WNDCLASSEX wndClass;

	// definindo uma classe janela chamada "GameWindow"
	wndClass.cbSize			= sizeof(WNDCLASSEX);
	wndClass.style			= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc	= Window::WinProc;
	wndClass.cbClsExtra		= 0;
	wndClass.cbWndExtra		= 0;
	wndClass.hInstance		= hInstance;
	wndClass.hIcon			= windowIcon;
	wndClass.hCursor	  	= windowCursor;
	wndClass.hbrBackground	= (HBRUSH)CreateSolidBrush(windowColor);
	wndClass.lpszMenuName 	= NULL;
	wndClass.lpszClassName	= "GameWindow";
	wndClass.hIconSm	  	= windowIcon;

	// registrando a classe "GameWindow"
	if (!RegisterClassEx(&wndClass)) return false;

	// criando uma janela baseada na classe "GameWindow"
	windowHandle = CreateWindowEx(
		NULL,							// estilos extras
		"GameWindow",					// nome da "window class"
		windowTitle.c_str(),			// t�tulo da janela
		windowStyle,					// estilo da janela
		windowPosX, windowPosY,			// posi��o (x,y) inicial da janela
		windowWidth, windowHeight,		// largura e altura da janela
		NULL,							// identificador da janela pai
		NULL,							// identificador do menu
		hInstance,						// identificador da aplica��o
		NULL							// par�metros de cria��o
	);

	/*
		Ao usar o modo janela preciso levar em conta que as barras
		e bordas ocupanm espa�o na janela. o c�digo abaixo ajusta o tamanho
		da janela de forma que a �rea cliente do jogo fique do tamanho
		(windowWidth * windowheight)
	*/

	if (windowMode == WINDOWED)
	{
		// ret�ngulo com a nova area cliente
		RECT winRect{ 0, 0, windowWidth, windowHeight };

		// ajusta o tamanho do ret�ngulo da area cliente
		AdjustWindowRectEx(
			&winRect,
			GetWindowStyle(windowHandle),
			GetMenu(windowHandle) != NULL,
			GetWindowExStyle(windowHandle)
		);

		// atualiza a posi��o da janela
		windowPosX = GetSystemMetrics(SM_CXSCREEN) / 2 - (winRect.right - winRect.left) / 2;
		windowPosY = GetSystemMetrics(SM_CYSCREEN) / 2 - (winRect.bottom - winRect.top) / 2;

		// redimensiona a janela com uma chamada a MoveWindow
		MoveWindow(								
			windowHandle,						// identificador da janela
			windowPosX,							// posi��o x
			windowPosY,							// posi��o y
			winRect.right - winRect.left,		// largura
			winRect.bottom - winRect.top,		// altura
			TRUE								// repintar
		);
	}

	// retorna o estado da inicializa��o
	return (windowHandle ? true : false);
}

// -----------------------------------------------------------------------------

LRESULT CALLBACK Window::WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		// movimento do mouse
	case WM_MOUSEMOVE:
		windowMouseX = GET_X_LPARAM(lParam);
		windowMouseY = GET_Y_LPARAM(lParam);
		return 0;

	case WM_MOUSEWHEEL:
		windowMouseWheel = GET_WHEEL_DELTA_WPARAM(wParam);
		return 0;

		// tecla pressionada
	case WM_KEYDOWN:
		windowKeys[wParam] = true;
		return 0;


		// bot�o esquerdo do mouse pressionado
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		windowKeys[VK_LBUTTON] = true;
		return 0;

		// bot�o do meio do mouse pressionado
	case WM_MBUTTONDOWN:
	case WM_MBUTTONDBLCLK:
		windowKeys[VK_MBUTTON] = true;
		return 0;

		// bot�o direito do mouse pressionado
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
		windowKeys[VK_RBUTTON] = true;
		return 0;

		// tecla liberada
	case WM_KEYUP:
		windowKeys[wParam] = false;
		return 0;

		// bot�o esquerdo do mouse liberado
	case WM_LBUTTONUP:
		windowKeys[VK_LBUTTON] = false;
		return 0;

		// bot�o do meio do mouse liberado
	case WM_MBUTTONUP:
		windowKeys[VK_MBUTTON] = false;
		return 0;

		// bot�o direito do mouse liberado
	case WM_RBUTTONUP:
		windowKeys[VK_RBUTTON] = false;
		return 0;

		// mudan�a de foco da janela
	case WM_SETFOCUS:
		Engine::Resume();
		return 0;
	case WM_KILLFOCUS:
		Engine::Pause();
		return 0;

		// a janela foi destruida
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// -----------------------------------------------------------------------------
