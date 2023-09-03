/*******************************************************************************
	Window (Arquivo de Cabe�alho)

	Cria��o:	02 Jul 2023
	Compilador:	Visual C++ 2022

	Descri��o:	A classe abstrai todos os detalhes de configura��o de
				uma janela para um jogo.
*******************************************************************************/

#ifndef _PROGJOGOS_WINDOW_H_
#define _PROGJOGOS_WINDOW_H_

// -----------------------------------------------------------------------------
// Inclus�es

#include <windows.h>		// inclui fun��es do windows
#include <windowsx.h>		// inclui extens�es do windows
#include <string>			// inclui a classe string
#include "Types.h"			// tipos personalizados do motor
							
using std::string;			// permite usar o tipo string sem o std:

// -----------------------------------------------------------------------------
// Constantes globais e enumera��es

enum WindowModes { FULLSCREEN, WINDOWED, BORDELESS };

// -----------------------------------------------------------------------------

class Window
{
private:
	HINSTANCE	hInstance;						// identificador da aplica��o
	HWND		windowHandle;					// identificador da janela
	int			windowWidth;					// largura da janela
	int			windowHeight;					// altura da janela
	HICON		windowIcon;						// icone da janela
	HCURSOR		windowCursor;					// cursor da janela
	COLORREF	windowColor;					// cor de fundo da janela
	string		windowTitle;					// nome da barra de t�tulo
	DWORD		windowStyle;					// estilo da janela
	int			windowMode;						// modo tela cheia, em janela ou sem borda
	int			windowPosX;						// posi��o inicial da janela no eixo x
	int			windowPosY;						// posi��o inicial da janela no eixo y
	float		windowCenterX;					// centro da janela no eixo x
	float		windowCenterY;					// centro da janela no eixo y
	static bool windowKeys[256];				// estado das teclas do teclado
	static bool windowCtrl[256];				// controle de libera��o de teclas
	static int	windowMouseX;					// posi��o do mouse eixo x
	static int	windowMouseY;					// posi��o do mouse eixo y
	static int  windowMouseWheel;				// giro da roda do mouse

public:
	Window();									// construtor de window
												
	HINSTANCE AppId();							// retorna o identificador da aplica��o
	HWND Id();									// retorna o identificador da janela
	int Width();								// retorna a largura atual da janela
	int Height();								// retorna a altura atual da janela
												
	void Icon(const uint icon);					// define o �cone da janela
	void Cursor(const uint cursor);				// define o cursor da janela
	void Title(const string title);				// define o t�tulo da janela
	void Size(int width, int height);			// defime o tamanho (largura e altura) da janela
	void Mode(int mode);						// define o modo da janela (FULLSCREEN/WINDOWED)

	int Mode() const;							// retorna o modo atual da janela (FULLSCREEN/WINDOMED)
	float CenterX() const;						// retorna o centro da janela no eixo x
	float CenterY() const;						// retorna o centro da janela no eixo y
	string Title() const;						// retorna o t�tulo da janela

	void HideCursor(bool hide);					// habilita ou desabilita a exibi��o do cursor
	void Close();								// fecha a janela imediatamente

	bool KeyDown(int vkcode);					// verifica se uma tecla/bot�o est� pressionado
	bool KeyUp(int vkcode);						// verifica se uma tecla/bot�o est� liberada
	bool KeyPress(int vkcode);					// registra um pressionamento por vez

	int MouseX();								// retorna a posi��o x do mouse
	int MouseY();								// retorna a posi��o y do mouse
	int MouseWheel();							// retorna giro da roda do mouse

	COLORREF Color();							// retorna a cor de fundo da janela
	void Color(int r, int g, int b);			// define a cor de fundo da janela
	bool Create();								// cria a janela com os valores dos atributos

	// tratamento de eventos do Windows
	static LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

// -----------------------------------------------------------------------------
// Fun��es Membro inline

// retorna o identificador da aplica��o
inline HINSTANCE Window::AppId() { return hInstance; }

// retorna o identificador da janela
inline HWND Window::Id() { return windowHandle; }

// retorna a largura atual da janela
inline int Window::Width() { return windowWidth; }

// retorna a altura atual da janela
inline int Window::Height() { return windowHeight; }

// -----------------------------------------------------------------------------

// define o �cone da janela
inline void Window::Icon(const uint icon)
{ windowIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(icon)); }

// define o cursor da janela
inline void Window::Cursor(const uint cursor)
{ windowCursor = LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(cursor)); }

// define o titulo da janela
inline void Window::Title(const string title)
{ windowTitle = title; }

// -----------------------------------------------------------------------------

// retorna o modo atual da janela
inline int Window::Mode() const
{ return windowMode; }

// retorna o centro da janela no eixo horizontal
inline float Window::CenterX() const
{ return windowCenterX; }

// retorna o centro da janela no eixo vertical
inline float Window::CenterY() const
{ return windowCenterY; }

// retorna o titulo da janela
inline string Window::Title() const
{ return windowTitle; }

// -----------------------------------------------------------------------------

// habilita ou desabilita a exibi��o do cursor
inline void Window::HideCursor(bool hide)
{ ShowCursor(!hide); }

// fecha a janela imediatamente
inline void Window::Close()
{ PostMessage(windowHandle, WM_DESTROY, 0, 0); }

// retorna verdadeiro se a tecla est� pressionada
inline bool Window::KeyDown(int vkcode)
{ return windowKeys[vkcode]; }

// retorna verdadeiro se a tecla est� liberada
inline bool Window::KeyUp(int vkcode)
{ return !windowKeys[vkcode]; }

// retorna a posi��o do mouse no eixo x
inline int Window::MouseX()
{ return windowMouseX; }

// retorna a posi��o do mouse no eixo y
inline int Window::MouseY()
{ return windowMouseY; }

// retorna giro da roda do mouse
inline int Window::MouseWheel()
{ return windowMouseWheel; }

// -----------------------------------------------------------------------------

// retorna a cor de fundo da janela
inline COLORREF Window::Color()
{ return windowColor; }

// define a cor de fundo da janela
inline void Window::Color(int r, int g, int b)
{ windowColor = RGB(r, g, b); }

// -----------------------------------------------------------------------------


#endif