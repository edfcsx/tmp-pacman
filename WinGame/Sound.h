/*------------------------------------------------------------------------------

	Sound (Arquivo de Cabeçalho)

	Criação:	30 Jul 2023
	Compilador:	Visual C++ 2022

	Descrição:	Representa um som no formato WAVE

------------------------------------------------------------------------------*/

#ifndef _PROGJOGOS_SOUND_H_
#define _PROGJOGOS_SOUND_H_

// -----------------------------------------------------------------------------

#include <xaudio2.h>								// biblioteca de audio
#include <string>									// string de texto
#include "Types.h"									// tipos especificos da engine

using std::string;									// usa string sem std::

// -----------------------------------------------------------------------------

class Sound
{
private:
	WAVEFORMATEXTENSIBLE format;				// formato do arquivo .wav
	XAUDIO2_BUFFER		 buffer;				// buffer com os dados do som
	float				 volume;				// volume do som
	float				 frequency;				// frequência do som

	IXAudio2SourceVoice ** voices;				// vetor de ponteiro para vozes
	uint				 tracks;				// número de vozes para este som
	uint				 index;					// índice da voz selecionada

	HRESULT FindChunk(HANDLE hFile,				// localiza blocos no arquivo RIFF
		DWORD fourcc,
		DWORD & dwChunkSize,
		DWORD & dwChunkDataPosition);

	HRESULT ReadChunkData(HANDLE hFile,			// lê blocos do arquivo para um buffer
		void * buffer,
		DWORD bufferSize,
		DWORD bufferoffset);

	friend class Audio;

public:
	Sound(string fileName, uint nTracks);		// construtor
	~Sound();									// destrutor
};

// -----------------------------------------------------------------------------

#endif