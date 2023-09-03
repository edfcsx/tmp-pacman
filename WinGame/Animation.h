/*******************************************************************************
	Animation (Arquivo de Cabeçalho)

	Criação:	23 Jul 2023
	Compilador:	Visual C++ 2022

	Descrição:	Classe para animar sequências em folha de sprites
*******************************************************************************/

#ifndef _PROGJOGOS_ANIMATION_H_
#define _PROGJOGOS_ANIMATION_H_

// -----------------------------------------------------------------------------

#include "Sprite.h"						// tipo sprite para renderização
#include "TileSet.h"					// folha de sprites da animação
#include "Timer.h"						// tempo entre quadros da animação
#include "Types.h"						// tipos específicos da engine

#include <unordered_map>				// biblioteca STL
using std::unordered_map;				// usando tabelas de dispersão
using std::pair;						// usando pares de elementos

// sequência <vetor, tam>
using AnimSeq = pair<uint*, uint>;

// tabela de dispersão
using HashTable = unordered_map<uint, AnimSeq>;

// -----------------------------------------------------------------------------

class Animation
{
private:
	uint  iniFrame;						// quadro inicial da sequência
	uint  endFrame;						// quadro final da sequência
	uint  frame;						// quadro atual da animação
	bool  animLoop;						// animação em loop infinito
	float animDelay;					// espaço de tempo entre quadros (em segundos)
	Timer timer;						// medidor de tempo entre quadros da animação
	TileSet * tileSet;					// ponteiro para folha de sprites da animação
	SpriteData sprite;					// sprite a ser desenhado
	HashTable table;					// tabela com sequências de animação
	uint * sequence;					// sequência atualmente selecionada

public:
	Animation(TileSet * tiles, float delay, bool repeat);
	~Animation();

	// adiciona sequência de animação
	void Add(uint id, uint * seq, uint seqSize);

	// seleciona sequência atual
	void Select(uint id);

	void Draw(											// desenha o quadro atual da animação
		float x, float y, float z = Layer::MIDDLE,		// coordenadas da tela
		Color color = { 1, 1, 1, 1 });					// efeito de cor													

	void Draw(											// desenha um quadro da folha de sprites
		uint aFrame,									// quadro da folha a desenha
		float x, float y, float z = Layer::MIDDLE,		// coordenadas da tela
		Color color = { 1, 1, 1, 1 });					// efeito de cor

	void Frame(uint aFrame);			// define o frame atual da animação
	uint Frame();						// retorna o frame de animação ativo
	bool Inactive();					// verifica se a animação já encerrou
	void NextFrame();					// passa para o próximo frame da animação
	void Restart();						// reinicia a animação (pelo primeiro frame da sequência)
};

// -----------------------------------------------------------------------------
// Funções membro inline

// desenha quadro atual da animação
inline void Animation::Draw(float x, float y, float z, Color color)
{
	sequence ? Draw(sequence[frame], x, y, z, color) : Draw(frame, x, y, z, color);
}

// define o frame atual da animação
inline void Animation::Frame(uint aFrame)
{
	frame = aFrame;
}

// retorna o frame de animação ativo
inline unsigned Animation::Frame()
{
	return (sequence ? sequence[frame] : frame);
}

// verifica se a animação já encerrou
inline bool Animation::Inactive()
{
	return !animLoop && (frame > endFrame || (frame == endFrame && timer.Elapsed(animDelay)));
}

// reinicia a animação (pelo primeiro frame da sequência)
inline void Animation::Restart()
{
	frame = 0;
	timer.Start();
}

// -----------------------------------------------------------------------------

#endif // !_PROGJOGOS_ANIMATION_H_
