/*******************************************************************************
	Arena (Código Fonte)

	Criação:	02 Set 2023
	Compilador:	Visual C++ 2022

	Descrição:	Define a arena principal do jogo Pacman
				todos os controles especificos do jogo
				devem ser implementados na arena.
*******************************************************************************/

#include "Arena.h"


// -----------------------------------------------------------------------------


void Arena::Init()
{
	// inicializa o mapa do jogo
	map = new Sprite("Resources/map.png");
}

// -----------------------------------------------------------------------------

void Arena::Update()
{

}

// -----------------------------------------------------------------------------

void Arena::Draw()
{
	// desenha o mapa do jogo
	map->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
}

// -----------------------------------------------------------------------------

void Arena::Finalize()
{
	// deleta o mapa do jogo
	delete map;
}
