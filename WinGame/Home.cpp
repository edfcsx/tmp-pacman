/*******************************************************************************
	Home (Código Fonte)

	Criação:	31 Ago 2023
	Compilador:	Visual C++ 2022

	Descrição:	Define a tela inicial do jogo pacman
*******************************************************************************/

#include "Home.h"
#include "Pacman.h"
#include "Engine.h"
#include "Arena.h"

// -----------------------------------------------------------------------------

Audio * Home::audio = nullptr;

// -----------------------------------------------------------------------------


void Home::Init()
{
	// inicializa o sistema de áudio
	audio = new Audio();

	// carrega músicas
	audio->Add(Sounds::INTRO, "Resources/Sounds/Intro.wav");
	audio->Add(Sounds::COIN_BEEP, "Resources/Sounds/CoinBeep.wav");

	// insere o background
	backg = new Sprite("Resources/home_background.png");

	// carrega o tileset de cada fantasma
	ghostTiles = new TileSet[4]{
		{ "Resources/ghost_acqua.png", 32, 32, 2, 8 },
		{ "Resources/ghost_blue.png", 32, 32, 2, 8 },
		{ "Resources/ghost_orange.png", 32, 32, 2, 8 },
		{ "Resources/ghost_red.png", 32, 32, 2, 8 },
	};

	// cria os fantasmas
	ghosts = new HomeScreenObject[4]{
		{ 
			new Animation(&ghostTiles[0], 0.10f, true), 
			window->CenterX(),
			window->CenterY() + 60.0f
		},
		{ 
			new Animation(&ghostTiles[1], 0.10f, true),
			window->CenterX() + 40.0f,
			window->CenterY() + 60.0f
		},
		{ 
			new Animation(&ghostTiles[2], 0.10f, true),
			window->CenterX() + 80.0f,
			window->CenterY() + 60.0f
		},
		{ 
			new Animation(&ghostTiles[3], 0.10f, true),
			window->CenterX() + 120.0f,
			window->CenterY() + 60.0f
		}
	};

	// define a animação para os fantasmas
	for (int i = 0; i < 4; i++) {
		HomeScreenObject * tmp = ghosts + i;

		uint seqLeft[2] = { 6, 7 };
		tmp->animation->Add(LEFT, seqLeft, 2);
		tmp->animation->Select(LEFT);
	}

	// carrrega o tileset do pacman
	pacmanTileset = new TileSet("Resources/pacman.png", 32, 32, 3, 12);

	// define o objeto do pacman
	pacman = new HomeScreenObject{
		new Animation(pacmanTileset, 0.1f, true),
		window->CenterX() - 80.0f,
		window->CenterY() + 60.0f
	};

	// define a animação de andar a esquerda para o pacman
	uint seqLeft[3] = { 9, 10, 11 };
	pacman->animation->Add(LEFT, seqLeft, 3);

	// carrega a fonte utilizada na home
	gameFont = new Font("Resources/Agency30.png");
	gameFont->Spacing("Resources/Agency30.dat");

	// inicializa o timer do texto
	textBlinkTimer.Start();

	// inicia a música de introdução
	audio->Volume(Sounds::INTRO, 0.5f);
	audio->Play(Sounds::INTRO);
}


// -----------------------------------------------------------------------------

void Home::Update()
{
	// atualiza a posição e animação dos fantasmas
	for (int i = 0; i < 4; ++i)
	{
		HomeScreenObject* tmp = (ghosts + i);
		tmp->animation->NextFrame();

		tmp->x += -150.0f * gameTime;

		if (tmp->x + 16.0f < 0)
			tmp->x = window->Width() + 16.0f;
	}

	// atualiza a posição e animação do pacman
	pacman->animation->NextFrame();
	pacman->x += -150.0f * gameTime;
	
	if (pacman->x + 16.0f < 0)
		pacman->x = window->Width() + 16.0f;

	// liga/desliga a exibição do texto
	if (textBlinkTimer.Elapsed(0.5f)) {
		showPressStartText = !showPressStartText;
		textBlinkTimer.Reset();
	}

	// verifica o pressionamento da tecla enter
	if (window->KeyPress(VK_RETURN)) {
		audio->Play(COIN_BEEP);
		Engine::Next<Arena>();
	}
}

// -----------------------------------------------------------------------------

void Home::Draw()
{
	// desenha plano de fundo
	backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);

	// desenha a animação dos fantasmas
	for (int i = 0; i < 4; ++i)
	{
		HomeScreenObject * tmp = (ghosts + i);
		tmp->animation->Draw(tmp->x, tmp->y, Layer::MIDDLE);
	}

	// desenha a animação do pacman
	pacman->animation->Draw(pacman->x, pacman->y, Layer::MIDDLE);

	// desenha o texto na tela press start
	if (this->showPressStartText)
		gameFont->Draw(window->CenterX() - 48.0f,
			window->CenterY() + 250.0f, "<< Press Start >>");
}

// -----------------------------------------------------------------------------

void Home::Finalize()
{
	// remove plano de fundo
	delete backg;

	// remove as animações dos fantasmas
	for (int i = 0; i < 4; ++i)
		delete (ghosts + i)->animation;
	
	// remove o fantasma e seus tilesests
	delete [] ghostTiles;
	delete [] ghosts;

	// delete o pacman a animação e o tileset
	delete pacman->animation;
	delete pacmanTileset;
	delete pacman;

	// deleta a fonte do jogo
	delete gameFont;

	// deleta o sistema de audio
	delete audio;
}

// -----------------------------------------------------------------------------
