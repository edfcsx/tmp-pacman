/*******************************************************************************
	Engine

	Cria��o:		02 Jul 2023
	Compilador:	Visual C++ 2022

	Descri��o:	A fun��o da Engine � rodar jogos criados a apartir da clase
				abstrata Game. Todo jogo deve ser uma classe derivada de Game
				e portanto deve implementar as fun��es membro Init, Update,
				Draw e Finalize, que ser�o chamadas pelo motor em um la�o
				de tempo real. Para usar a classe Engine, o programador
				deve criar uma inst�ncia e chamar o m�todo Start(),
				passando um objeto derivado de Game.
*******************************************************************************/

#include "Engine.h"
#include <sstream>
#include <windows.h>

using std::stringstream;

// -----------------------------------------------------------------------------
// Inicializa��o das variaveis est�ticas da classe

Game     * Engine::game		 = nullptr;		// jogo em execu��o
Window   * Engine::window	 = nullptr;		// janela do jogo
Graphics * Engine::graphics	 = nullptr;		// dispositivo gr�fico
Renderer * Engine::renderer  = nullptr;		// renderizador de sprites
float	   Engine::frameTime = 0.0f;		// tempo do quadro atual
bool	   Engine::paused	 = false;		// estado do game loop
Timer      Engine::timer;					// medidor de tempo

// -----------------------------------------------------------------------------


Engine::Engine()
{
	window = new Window();
	graphics = new Graphics();
	renderer = new Renderer();
}

// -----------------------------------------------------------------------------

Engine::~Engine() {
	delete game;
	delete renderer;
	delete graphics;
	delete window;
}

// -----------------------------------------------------------------------------

int Engine::Start(Game * level)
{
	game = level;

	// cria a janela do jogo
	if (!window->Create())
	{
		MessageBox(nullptr, "Falha na cria��o da janela", "Engine", MB_OK);
		return EXIT_FAILURE;
	}

	// inicializa dispositivo gr�fico
	if (!graphics->Initialize(window))
	{
		MessageBox(window->Id(), "Falha na inicializa��o do dispositivo Gr�fico", "Engine", MB_OK);
		return EXIT_FAILURE;
	}

	// inicia o renderizador de sprites
	if (!renderer->Initialize(window, graphics))
	{
		MessageBox(window->Id(), "Falha na cria��o do renderizador", "Engine", MB_OK);
		return EXIT_FAILURE;
	}

	// ajusta a resolu��o da fun��o Sleep para 1 milisegundo
	// requer uso da biblioteca winmm.lib
	// pelo padr�o quando se chama fun��o Sleep(x) ele dorme 
	// com pelo menos 15ms ent�o � imposs�vel usar valores
	// menores que 15 ent�o devido a isso ajustamos a resolu��o
	// para que a fun��o consiga dormir o tempo correto
	timeBeginPeriod(1);

	int exitCode = Loop();

	// volta a resolu��o ao valor original
	timeEndPeriod(1);

	return exitCode;
}

// -----------------------------------------------------------------------------

void Engine::Pause()
{
	paused = true;
	timer.Stop();
}

// -----------------------------------------------------------------------------

void Engine::Resume()
{
	paused = false;
	timer.Start();
}

// -----------------------------------------------------------------------------

int Engine::Loop()
{
	// inicia a contagem de tempo
	timer.Start();

	// inicializa��o do jogo
	game->Init();

	// mensagens do windows
	MSG msg{ 0 };

	// controle da tecla pause (VK_PAUSE)
	bool pauseKeyCtrl = true;

	// la�o do jogo
	do
	{
		// trata todos os eventos antes de atualizar o jogo
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//---------------------------------------
			// Pausa/Resume Jogo
			//---------------------------------------
	
			if (pauseKeyCtrl)
			{
				if (window->KeyDown(VK_PAUSE))
				{
					paused = !paused;
					pauseKeyCtrl = false;

					if (paused)
						timer.Stop();
					else
						timer.Start();
				}
			}
			else
			{
				// registra novo pressionamento somente
				// ap�s libera��o da tecla pause

				if (window->KeyUp(VK_PAUSE))
					pauseKeyCtrl = true;
			}

			// ------------------------------------------

			if (!paused)
			{
				// calcula o tempo do quadro
				frameTime = FrameTime();

				// atualiza��o do jogo
				game->Update();
			
				// limpa a tela para o pr�ximo quadro
				graphics->Clear();
			
				// desenha o jogo
				game->Draw();

				// renderiza sprites
				renderer->Render();

				// apresenta o jogo na tela (troca backbuffer/frontbuffer)
				graphics->Present();
			}
			else {
				// tela de pausa
				game->OnPause();
			}

			// ------------------------------------------
		}
	} while (msg.message != WM_QUIT);

	// finaliza��o do jogo
	game->Finalize();

	// encerra a aplica��o
	return int(msg.wParam);
}

float Engine::FrameTime()
{
	// ------ start debug ------
#ifdef _DEBUG
	static float totalTime = 0.0f;		// tempo total transcorrido
	static uint  frameCount = 0;		// contador de frames transcorridos
#endif // _DEBUG
	// ------ end debug --------

	// tempo do frame atual em segundos
	frameTime = timer.Reset();

	// ------ start debug ------
#ifdef _DEBUG
	// tempo acumulado dos frames
	totalTime += frameTime;
	// incrementa contador de frames
	frameCount++;

	// a cada 1000ms (1 segundo) atualiza indicador de FPS na janela
	if (totalTime >= 1.0f)
	{
		stringstream text;
		text << std::fixed;
		text.precision(3);

		text << window->Title().c_str() << "    "
			<< "FPS: " << frameCount << "    "
			<< "Frame Time: " << frameTime * 1000 << " (ms)";

		SetWindowText(window->Id(), text.str().c_str());

		frameCount = 0;
		totalTime -= 1.0f;
	}
#endif // _DEBUG
	// ------ end debug --------

	return frameTime;

}