/*******************************************************************************
	Engine

	Criação:		02 Jul 2023
	Compilador:	Visual C++ 2022

	Descrição:	A função da Engine é rodar jogos criados a apartir da clase
				abstrata Game. Todo jogo deve ser uma classe derivada de Game
				e portanto deve implementar as funções membro Init, Update,
				Draw e Finalize, que serão chamadas pelo motor em um laço
				de tempo real. Para usar a classe Engine, o programador
				deve criar uma instância e chamar o método Start(),
				passando um objeto derivado de Game.
*******************************************************************************/

#include "Engine.h"
#include <sstream>
#include <windows.h>

using std::stringstream;

// -----------------------------------------------------------------------------
// Inicialização das variaveis estáticas da classe

Game     * Engine::game		 = nullptr;		// jogo em execução
Window   * Engine::window	 = nullptr;		// janela do jogo
Graphics * Engine::graphics	 = nullptr;		// dispositivo gráfico
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
		MessageBox(nullptr, "Falha na criação da janela", "Engine", MB_OK);
		return EXIT_FAILURE;
	}

	// inicializa dispositivo gráfico
	if (!graphics->Initialize(window))
	{
		MessageBox(window->Id(), "Falha na inicialização do dispositivo Gráfico", "Engine", MB_OK);
		return EXIT_FAILURE;
	}

	// inicia o renderizador de sprites
	if (!renderer->Initialize(window, graphics))
	{
		MessageBox(window->Id(), "Falha na criação do renderizador", "Engine", MB_OK);
		return EXIT_FAILURE;
	}

	// ajusta a resolução da função Sleep para 1 milisegundo
	// requer uso da biblioteca winmm.lib
	// pelo padrão quando se chama função Sleep(x) ele dorme 
	// com pelo menos 15ms então é impossível usar valores
	// menores que 15 então devido a isso ajustamos a resolução
	// para que a função consiga dormir o tempo correto
	timeBeginPeriod(1);

	int exitCode = Loop();

	// volta a resolução ao valor original
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

	// inicialização do jogo
	game->Init();

	// mensagens do windows
	MSG msg{ 0 };

	// controle da tecla pause (VK_PAUSE)
	bool pauseKeyCtrl = true;

	// laço do jogo
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
				// após liberação da tecla pause

				if (window->KeyUp(VK_PAUSE))
					pauseKeyCtrl = true;
			}

			// ------------------------------------------

			if (!paused)
			{
				// calcula o tempo do quadro
				frameTime = FrameTime();

				// atualização do jogo
				game->Update();
			
				// limpa a tela para o próximo quadro
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

	// finalização do jogo
	game->Finalize();

	// encerra a aplicação
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