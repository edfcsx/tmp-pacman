/*******************************************************************************
	Graphics (Arquivo de Cabe�alho)

	Cria��o:		02 Jul 2023
	Compilador:	Visual C++ 2022

	Descri��o:	Graphics � uma classe que faz uso das fun��es 
				do Direct3D para acessar o hardware de acelera��o gr�fica da
				placa de v�deo.
*******************************************************************************/

#ifndef _PROGJOGOS_GRAPHICS_H_
#define _PROGJOGOS_GRAPHICS_H_

// -----------------------------------------------------------------------------
// Inclus�es

#include <dxgi.h>			// infraestrutura gr�fica do dirextX
#include <d3d11.h>			// principais fun��es do Direct3D
#include "Window.h"			// cria e configura uma janela do windows
#include "Types.h"			// tipos espec�ficos da engine

// -----------------------------------------------------------------------------

class Graphics
{
private:
	IDXGISwapChain            * swapChain;			// swap chain
	ID3D11RenderTargetView    * renderTargetView;	// render target view do backbuffer
	ID3D11BlendState          * blendState;			// configura��o da mistura de cores
	D3D_FEATURE_LEVEL			featureLevel;		// n�vel de recursos D3D suportados pelo hardware
	float						bgColor[4];			// cor de fundo do backbuffer
	bool						vSync;				// vertical sync

public:
	Graphics();										// construtor
	~Graphics();									// destrutor
													
	static ID3D11Device			* device;			// dispositivo gr�fico
	static ID3D11DeviceContext  * context;			// contexto do dispositivo gr�fico
	static D3D11_VIEWPORT		  viewport;			// viewport

	void VSync(bool state);							// liga/desliga vertical vsync
	void Clear();									// limpa o backbuffer com a cor de fundo
	void Present();									// apresenta desenho na tela
	bool Initialize(Window* window);				// inicializa o Direct3D
};

// -----------------------------------------------------------------------------
// m�todos inline
// 
// liga/desliga virtual sync
inline void Graphics::VSync(bool state)
{ vSync = state; }

// limpa o backbuffer para o pr�ximo quadro
inline void Graphics::Clear()
{ context->ClearRenderTargetView(renderTargetView, bgColor); }

// apresenta desenho na tela (troca backbuffer com frontbuffer)
inline void Graphics::Present()
{
	swapChain->Present(vSync, NULL);
	context->OMSetRenderTargets(1, &renderTargetView, nullptr);
}

// -----------------------------------------------------------------------------

#endif