/*******************************************************************************
	Pacman (Arquivo de Cabe�alho)

	Cria��o:	11 Jul 2023
	Compilador:	Visual C++ 2022

	Descri��o:	Define os tipos utilizados no jogo pacman
*******************************************************************************/

#ifndef _PACMAN_H_
#define _PACMAN_H_

// -----------------------------------------------------------------------------

enum PacManObjects
{
	PLAYER,
	GHOST,
	FOOD,
	SPECIAL,
	PIVOT,
	UI
};

enum PLAYERSTATE { STOPED, UP, DOWN, LEFT, RIGHT };

// -----------------------------------------------------------------------------

enum Sounds {
	INTRO,
	COIN_BEEP
};

// -----------------------------------------------------------------------------

#endif

