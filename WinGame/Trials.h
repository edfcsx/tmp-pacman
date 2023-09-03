/*------------------------------------------------------------------------------
    Trials (Arquivo de Cabe�alho)

    Cria��o:	06 Ago 2023
    Compilador:	Visual C++ 2022

    Descri��o: Exemplo de interface com menus
------------------------------------------------------------------------------*/

#ifndef _TRIALS_H_
#define _TRIALS_H_

// -----------------------------------------------------------------------------

#include "Game.h"
#include "Audio.h"
#include "Mouse.h"
#include "Item.h"
#include "Sprite.h"
#include "Scene.h"
#include "Resources.h"

// -----------------------------------------------------------------------------

enum MenuID { SINGLE, MULTI, TRACKS, LEADERBOARD, OPTIONS, EXIT };
enum Music { EVOLUTION };

// -----------------------------------------------------------------------------

class Trials : public Game
{
private:
    static const int MaxItens = 6;      // n�mero de itens do menu
                                        
    Scene  * scene = nullptr;           // cena do jogo
    Audio  * audio = nullptr;           // sistema de �udio
    Sprite * backg = nullptr;           // plano de fundo
    Mouse  * mouse = nullptr;           // objeto mouse
                                        
    Item * menu[MaxItens] = { 0 };      // itens do menu
    Item * selected = nullptr;          // item selecionado

    bool editMode = false;              // jogo em modo edi��o
    bool followMode = false;            // item em modo seguidor
    bool viewBBox = false;              // visualiza bounding box
                                        
public:                                 
    void Init();                        // inicializa��o
    void Update();                      // atualiza��o
    void Draw();                        // desenho
    void Finalize();                    // finaliza��o
};

// -----------------------------------------------------------------------------

#endif // !_TRIALS_H_
