/*------------------------------------------------------------------------------

	Audio (Arquivo de Cabe�alho)

	Cria��o:	30 Jul 2023
	Compilador:	Visual C++ 2022

	Descri��o:	Classe para reproduzir �udio

------------------------------------------------------------------------------*/

#ifndef _PROGJOGOS_AUDIO_H_
#define _PROGJOGOS_AUDIO_H_

// -----------------------------------------------------------------------------

#include "Sound.h"								// guarda som no formato WAVE
#include "Types.h"								// tipos especificos da engine
#include <XAudio2.h>							// XAudio 2 API
#include <unordered_map>						// tabela de dispers�o
#include <string>								// tipo string da STL

using std::unordered_map;
using std::string;

// -----------------------------------------------------------------------------

class Audio
{
private:
	IXAudio2 * audioEngine;										// sistema de �udio (engine)
	IXAudio2MasteringVoice * masterVoice;						// dispositivo principal de �udio
	unordered_map<uint, Sound*> soundTable;						// cole��o de sons

public:
	Audio();													// construtor
	~Audio();													// destrutor
												
	void Add(uint id, string filename, uint nVoices = 1);		// adiciona um som <id, filename>
	void Play(uint id, bool repeat = false);					// reproduz som atrav�s do seu id
	void Stop(uint id);											// para a reprodu��o do som
	void Volume(uint id, float level);							// ajusta o volume do som
	void Frequency(uint id, float level);						// ajusta a frequ�ncia do som
};

// -----------------------------------------------------------------------------

#endif

