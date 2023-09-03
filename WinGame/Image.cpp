/*******************************************************************************
	Image

	Criação:	03 Jul 2023
	Compilador:	Visual C++ 2022

	Descrição:	Define uma classe para representar imagens
*******************************************************************************/

#include "Image.h"
#include "Graphics.h"

// -----------------------------------------------------------------------------

Image::Image(string filename) : textureView(nullptr), width(0), height(0)
{
	// cria sharer resource view da imagem em disco
	D3D11CreateTextureFromFile(
		Graphics::device,			// dispositivo Direct3D
		Graphics::context,			// contexto do dispositivo
		filename.c_str(),			// nome do arquivo de imagem
		nullptr,					// retorna textura
		&textureView,				// retorna vieww da textura
		width,						// retorna largura da imagem
		height						// retorna altura da imagem
	);
}

// -----------------------------------------------------------------------------

Image::~Image()
{
	// libera mémoria ocupada pela texture view
	if (textureView)
	{
		// pega ponteiro para recurso
		ID3D11Resource * resource = nullptr;
		textureView->GetResource(&resource);

		// liberando a view não libera automaticamente
		// o recurso que foi criado junto com a view

		if (resource)
		{
			resource->Release();
			resource = nullptr;
		}

		textureView->Release();
		textureView = nullptr;
	}
}

// -----------------------------------------------------------------------------
