/*------------------------------------------------------------------------------
    Trials (Arquivo de Cabeçalho)

    Criação:	06 Ago 2023
    Compilador:	Visual C++ 2022

    Descrição: Exemplo de interface com menus
------------------------------------------------------------------------------*/

#include "Trials.h"
#include "Engine.h"
#include "Mouse.h"
#include "Item.h"

// -----------------------------------------------------------------------------

void Trials::Init()
{
    // cria gerenciadores
    scene = new Scene();
    audio = new Audio();

    // carrega sons é musicas
    audio->Add(EVOLUTION, "Resources/Evolution.wav");

    // cria sprites
    backg = new Sprite("Resources/Trials.jpg");

    // cria objeto mouse
    mouse = new Mouse();
    scene->Add(mouse, MOVING);

    // cria itens de menu
    menu[0] = new Item(570, 250, SINGLE,      "Resources/SinglePlayer.png");
    menu[1] = new Item(570, 305, MULTI,       "Resources/MultiPlayer.png");
    menu[2] = new Item(570, 360, TRACKS,      "Resources/TrackCentral.png");
    menu[3] = new Item(570, 432, LEADERBOARD, "Resources/Leaderboards.png");
    menu[4] = new Item(570, 490, OPTIONS,     "Resources/HelpOptions.png");
    menu[5] = new Item(570, 545, EXIT,        "Resources/ExitGame.png");

    // adiciona itens na cena
    for (int i = 0; i < MaxItens; ++i)
        scene->Add(menu[i], STATIC);

    // inicia com música
    audio->Volume(EVOLUTION, 2.0f);
    audio->Play(EVOLUTION, true);
}

// -----------------------------------------------------------------------------

void Trials::Update()
{
    // fecha a janela ao pressionar ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    // atualiza objeto mouse
    mouse->Update();

    if (followMode)
    {
        // move o item selecinado com o mouse
        selected->MoveTo(window->MouseX(), window->MouseY());

        // solta o item e sai do modo de posicionamento
        if (mouse->Clicked()) followMode = false;
    }
    else {
        // destaca item selecionado
        for (int i = 0; i < MaxItens; ++i)
        {
            if (scene->Collision(mouse, menu[i]))
            {
                menu[i]->Select();
                selected = menu[i];

                if (mouse->Clicked())
                {
                    if (editMode)
                        followMode = true;
                    else
                    {
                        switch (menu[i]->Type())
                        {
                        case SINGLE:
                        case MULTI:
                        case TRACKS:
                        case LEADERBOARD:
                        case OPTIONS: break;
                        case EXIT: window->Close(); break;
                        }
                    }
                }
            }
            else {
                menu[i]->UnSelect();
            }

            menu[i]->Update();
        }
    }

    
    // habilita/desabilita a bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;

    // habilita / desabilita o modo de edição
    if (window->KeyPress('E'))
        editMode = !editMode;
}

// -----------------------------------------------------------------------------

void Trials::Draw()
{
    // desenha pano de fundo
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);

    // desenha itens do menu
    scene->Draw();

    // desenha bounding box dos items
    if (viewBBox)
        scene->DrawBBox();
}

// -----------------------------------------------------------------------------

void Trials::Finalize()
{
    // remove sprites
    delete backg;

    // remove sistemas
    delete scene;
    delete audio;
}

// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
//									WinMain
// -----------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine* engine = new Engine();

    // configura e inicia o jogo
    engine->window->Mode(WINDOWED);
    engine->window->Size(800, 600);
    engine->window->Color(0, 0, 0);
    engine->window->Title("Trials");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);

    // configura dispositivo gráfico
    engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new Trials());

    // destrói o motor e o jogo
    delete engine;
    return status;
}

// -----------------------------------------------------------------------------
