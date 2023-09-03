/*******************************************************************************
// Game.h (Arquivo de Cabe�alho)
//
// Cria��o:		02 Jul 2023
// Compilador:	Visual C++ 2022
//
// Descri��o:	Uma classe abstrata para representar um jogo
//				
//				Para criar um jogo o programador deve criar uma classe
//				derivada de Game e sobrescrever os m�todos Init, Update
//				Draw e Finalize. Para rodar o jogo, deve-se passar o
//				objeto Game para o m�todo Start() de um objeto Engine.
//
*******************************************************************************/

#ifndef _PROGJOGOS_GAME_H_
#define _PROGJOGOS_GAME_H_

// -----------------------------------------------------------------------------

#include "Window.h"

// -----------------------------------------------------------------------------

class Game
{
	// Membros protegidos s�o privados para o mundo externo mas
	// p�blicos para as classes derivadas, ou seja, as classes
	// derivadas de Game ser�o capazes de acessar estes membros
protected:
	// Window*& isso � uma refer�ncia para um ponteiro
	static Window* & window;			// janela do jogo
	static float   & gameTime;			// tempo do �ltimo quadro

public:
	Game();								// construtor
	virtual ~Game();					// destrutor


	// M�todos que podem ser sobrescritos para implementar
	// funcionalidade espec�fica para o jogo. Eles j� possuem
	// uma implementa��o padr�o.

	virtual void OnPause();				// pausa do jogo

	// Estes m�todos s�o puramente virtuais, isto �, devem ser
	// implementados em todas as classes derivadas de Game.

	virtual void Init() = 0;			// inicializa��o do jogo
	virtual void Update() = 0;			// atualiza��o do jogo
	virtual void Draw() = 0;			// desenho de cena
	virtual void Finalize() = 0;		// finaliza��o do jogo
};

#endif // !_PROGJOGOS_GAME_H_
