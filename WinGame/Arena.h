/*******************************************************************************
	Arena (Arquivo de Cabe�alho)

	Cria��o:	02 Set 2023
	Compilador:	Visual C++ 2022

	Descri��o:	Define a arena principal do jogo Pacman
				todos os controles especificos do jogo 
				devem ser implementados na arena.
*******************************************************************************/

#ifndef _PACMAN_ARENA_H_
#define _PACMAN_ARENA_H_

// -----------------------------------------------------------------------------
// Inclus�es

#include "Game.h"								// interface de Game
#include "Sprite.h"								// interface de Sprite

// -----------------------------------------------------------------------------

class Arena : public Game
{
private:
	Sprite * map = nullptr;						// mapa do jogo

public:
	void Init();
	void Update();
	void Draw();
	void Finalize();
};

#endif // !_PACMAN_ARENA_H_
