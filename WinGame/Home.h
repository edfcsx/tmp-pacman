/*******************************************************************************
	Home (Arquivo de Cabe�alho)

	Cria��o:	31 Ago 2023
	Compilador:	Visual C++ 2022

	Descri��o:	Define a tela inicial do jogo pacman
*******************************************************************************/

#ifndef _PACMAN_HOME_H_
#define _PACMAN_HOME_H_

// -----------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Audio.h"
#include "Sprite.h"
#include "Animation.h"
#include "Font.h"
#include "Timer.h"

// -----------------------------------------------------------------------------
// Tipos

struct HomeScreenObject {
	Animation * animation;
	float x;
	float y;
};

// -----------------------------------------------------------------------------

class Home : public Game
{
private:
	Sprite  * backg			  = nullptr;			// plano de fundo
	TileSet * ghostTiles 	  = nullptr;			// array de tileset dos fantasmas
	TileSet * pacmanTileset	  = nullptr;			// tileset do pacman
	HomeScreenObject * ghosts = nullptr;			// array de fantasmas
	HomeScreenObject * pacman = nullptr;			// pacman
	
	Font * gameFont = nullptr;						// fonte do jogo

	Timer textBlinkTimer;							// timer para realizar o efeito blink do texto
	bool showPressStartText = true;					// variavel para controlar a exibi��o do texto

public:
	static Audio * audio;							// sistema de �udio

public:
	void Init();
	void Update();
	void Draw();
	void Finalize();
};

// -----------------------------------------------------------------------------

#endif // !_PACMAN_HOME_H_
