/*******************************************************************************
	Timer (Arquivo de Cabeçalho)

	Criação:	02 Jul 2023
	Compilador:	Visual C++ 2022

	Descrição:	Usa um contador de alta precisão pra medir o tempo.
*******************************************************************************/

#ifndef _PROGJOGOS_TIMER_H_
#define _PROGJOGOS_TIMER_H_

#include <windows.h>	// acesso ao contador de alta precisão

// -----------------------------------------------------------------------------

class Timer
{
private:
	LARGE_INTEGER start, end;		// valores de início e fim do contador
	LARGE_INTEGER freq;				// frequência do contador
	bool stoped;					// estado da contagem
									
public:								 
	Timer();						// construtor 
									
	void  Start();					// inicia/retoma contagem do tempo
	void  Stop();					// para contagem do tempo
	float Reset();					// reinicia contagem e retorna tempo transcorrido
	float Elapsed();				// retorna tempo transcorrido em segundos
	bool  Elapsed(float secs);		// verifica se transcorreu "secs" segundos
};

// -----------------------------------------------------------------------------
// funções inline

inline bool Timer::Elapsed(float secs)
{
	return (Elapsed() >= secs ? true : false);
}

#endif // !_PROGJOGOS_TIMER_H_
