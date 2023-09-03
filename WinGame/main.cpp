/*******************************************************************************
	Pacman

	Criação:	31 Ago 2023
	Compilador:	Visual C++ 2022

	Descrição:	Classe principal que define a janela e o jogo pacman
*******************************************************************************/

#include "Engine.h"
#include "Resources.h"
#include "Home.h"

// -----------------------------------------------------------------------------
//									WinMain
// -----------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Engine * engine = new Engine();

	// configura e inicia a janela principal
	engine->window->Mode(WINDOWED);
	engine->window->Size(625, 730);
	engine->window->Color(0, 0, 0);
	engine->window->Title("PacMan");
	engine->window->Icon(IDI_ICON);
	engine->window->Cursor(IDC_CURSOR);
	engine->window->HideCursor(true);

	// configura o dispositivo gráfico
	engine->graphics->VSync(true);

	// inicia o jogo
	int status = engine->Start(new Home());

	// destrói o motor e o jogo
	delete engine;

	return status;
}
