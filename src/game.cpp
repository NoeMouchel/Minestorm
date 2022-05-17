#include <iostream>
#include <raylib.h>
#include <string>

#include "../include/game.h"

void switchBool(bool* a)
{
    if (*a)
        *a = false;
    else
        *a = true;
}

//  Constructor - Initialize the game components
Game::Game()
{
    std::cout << "Constructing game..." << std::endl;

    deltaTime = 0.f;
    m_display = D_MAIN_MENU;

    m_entities = nullptr;

    m_debug = false;

    m_window = new WindowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "Mine Storm", DEFAULT_FPS);
    m_renderer = new Renderer();
    m_sound_manager = new SoundManager();

    m_background_fx = BackgroundParticle(2000, &m_renderer->m_textures[T_SPRITE], RoundColor[START_ROUND]);
}

//  Destructor - Destroy the game component
Game::~Game()
{
	std::cout << "Destroying game..." << std::endl;
    delete m_sound_manager;
    delete m_renderer;
    delete m_window;

    if (m_entities!=nullptr )
        delete m_entities;

}


//  Loop - main loop of the window and the game
void Game::gameLoop()
{
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        deltaTime = GetFrameTime();
        if (deltaTime > 1 / 3.f)
            deltaTime = 0;

        gameEvent();    // trigger event
        gameUpdate();   // update game
        gameRender();   // render game
        gamePlayer();   // play sound
    }
}

/*--------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------EVENT-----------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------*/

//  Event - take information from the keyBoard and toggle events
void Game::gameEvent()
{
    // Display switcher
    switch (m_display)
    {
    case D_MAIN_MENU :
        mainMenuEvent(); break;
    case D_IN_GAME :
        inGameEvent(); break;
    case D_PAUSE :
        pauseEvent(); break;
    case D_GAME_OVER :
        gameOverEvent(); break;
    case D_INTER_ROUND:
        interRoundEvent(); break;
    default :
        break;
    }
}

void Game::mainMenuEvent()
{
    if (IsKeyPressed(KEY_F))
    {
        std::cout << "solo mode selected" << std::endl;
        m_display = D_IN_GAME;
        m_entities = new EntitiesManager(false, &m_renderer->m_textures[T_SPRITE]);
        m_sound_manager->stopMusic();
    }
    else if (IsKeyPressed(KEY_K))
    {
        std::cout << "duo mode selected" << std::endl;
        m_display = D_IN_GAME;
        m_entities = new EntitiesManager(true, &m_renderer->m_textures[T_SPRITE]);
        m_sound_manager->stopMusic();
    }
}

void Game::inGameEvent()
{
    if (IsKeyPressed(PAUSE_INPUT))
    {
        m_saved_display = m_display;
        m_display = D_PAUSE;
        return;
    }

    m_entities->EventPlayers(deltaTime);

    //DEBUG ENABLE/DISABLE
    if (IsKeyPressed(DEBUG_INPUT))
        switchBool(&m_debug);
}

void Game::pauseEvent()
{
    if (IsKeyPressed(PAUSE_INPUT))
    {
        m_display = m_saved_display;
    }
    else if (IsKeyPressed(LEAVE_INPUT))
    {
        m_sound_manager->stopAmbient();
        delete m_entities;
        m_entities = nullptr;
        m_display = D_MAIN_MENU;
    }
}

void Game::gameOverEvent()
{
    if (IsKeyPressed(LEAVE_INPUT))
    {
        delete m_entities;
        m_entities = nullptr;
        m_display = D_MAIN_MENU;
    }
}

void Game::interRoundEvent()
{
    if (IsKeyPressed(PAUSE_INPUT))
    {
        m_saved_display = m_display;
        m_display = D_PAUSE;
        return;
    }

    m_round_timer += deltaTime;
    if (m_round_timer > 3.f)
    {
        m_display = D_IN_GAME;
        m_round_timer = 0.f;
        m_entities->reset();
    }
}

/*--------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------UPDATE------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------*/

//  Update - update all updatable components
void Game::gameUpdate()
{
    m_background_fx.update(deltaTime);
    // Display switcher
    switch (m_display)
    {
    case D_IN_GAME:
        inGameUpdate(); break;
    default:
        break;
    }
}

void Game::inGameUpdate()
{
    m_entities->update(deltaTime);
    if (m_entities->m_game_over)
        m_display = D_GAME_OVER;

    if (m_entities->m_next_round)
        m_display = D_INTER_ROUND;
}


/*--------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------RENDER------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------*/


//  Render - manage the objects rendering
void Game::gameRender()
{
    BeginDrawing();
        ClearBackground(RAYWHITE);
        m_renderer->drawBackground();
        m_background_fx.draw();
        
        // Display switcher
        switch (m_display)
        {
        case D_MAIN_MENU:
            mainMenuRender(); break;
        case D_IN_GAME:
            inGameRender(); break;
        case D_PAUSE:
            pauseRender(); break;
        case D_GAME_OVER:
            gameOverRender(); break;
        case D_INTER_ROUND:
            interRoundRender(); break;
        default:
            break;
        }

        m_renderer->drawForeground();
    EndDrawing();
}

void showControl()
{
    int space = 20;
    //PLAYER 1 CONTROL
    {
        int y_pos = 75;
        int x_pos = 75;
        DrawText("PLAYER ONE", x_pos, y_pos, 20, BLUE);
        x_pos += 10;
        y_pos += space + 10;

        DrawText("Rotate: 'd' and 'g'", x_pos, y_pos, 15, WHITE);
        y_pos += space;
        DrawText("Move: 'r'", x_pos, y_pos, 15, WHITE);
        y_pos += space;
        DrawText("Teleport: 'e' and 't'", x_pos, y_pos, 15, WHITE);
    }

    //PLAYER 2 CONTROL
    {
        int y_pos = 75;
        int x_pos = 420;
        DrawText("PLAYER TWO", x_pos, y_pos, 20, GREEN);
        x_pos += 10;
        y_pos += space + 10;

        DrawText("Rotate: 'j' and 'l'", x_pos, y_pos, 15, WHITE);
        y_pos += space;
        DrawText("Move: 'i'", x_pos, y_pos, 15, WHITE);
        y_pos += space;
        DrawText("Teleport: 'u' and 'o'", x_pos, y_pos, 15, WHITE);
    }
}

// main menu rendering
void Game::mainMenuRender()
{
    showControl();

    int x_pos = 150;
    int y_pos = 300;
    int space = 30;
    DrawText("Do you want to play?", x_pos, y_pos, 25, LIGHTGRAY);
    x_pos += 50;
    y_pos += space + 10;

    DrawText("Press 'F':    Solo mode", x_pos, y_pos, 20, SKYBLUE);
    y_pos += space;
    DrawText("Press 'K':    Two players mode", x_pos, y_pos, 20, GREEN);
    y_pos += space;
    DrawText("Press 'ESC':  Exit", x_pos, y_pos, 20, RED);
}


//  pause rendering
void Game::pauseRender()
{
    showControl();

    int x_pos = 150;
    int y_pos = 300;
    int space = 30;

    DrawText("Pause", 275, y_pos, 30, LIGHTGRAY);
    y_pos += space + 10;

    DrawText("Press 'space':    Resume", x_pos, y_pos, 20, SKYBLUE);
    y_pos += space;
    DrawText("Press 'Q':      Back to main menu", x_pos, y_pos, 20, RED);
}


//  In game rendering
void Game::inGameRender()
{
    int player_number = 0;
    int score_int = m_entities->m_player_score;
    std::string score = "Score " + std::to_string(score_int);
    
    m_entities->drawEntity(m_debug);

    DrawText(score.c_str(), 260, 100, 20, WHITE);
    for (Player* cur_player : m_entities->m_player)
    {
        for (int i = 0; i < cur_player->m_life; i++)
        {
            m_renderer->drawPlayerLife((float)(100 + i * 50 + player_number * 320), 100.f, cur_player->m_color);
        }
        player_number += 1;
    }
}

//  Game over rendering
void Game::gameOverRender()
{
    showControl();

    int x_pos = 150;
    int y_pos = 300;
    int space = 30;
    int score_int = m_entities->m_player_score;
    std::string score = "Score :" + std::to_string(score_int);

    DrawText("Game Over", 245, y_pos, 30, LIGHTGRAY);
    y_pos += space + 10;

    DrawText(score.c_str(), 260, y_pos, 20, GREEN);
    y_pos += space;
    DrawText("Press 'Q':      Back to main menu", x_pos, y_pos, 20, WHITE);
}


void Game::interRoundRender()
{
    int player_number = 0;
    int round_int = m_entities->m_round;
    std::string round ="Round - " + std::to_string(round_int);
    m_background_fx.m_color = RoundColor[round_int%10];
    DrawText(round.c_str(), 200, 300, 50, BLUE);
    
}

/*--------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------SOUND-PLAYER------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------*/

void Game::gamePlayer()
{
    // Display switcher
    switch (m_display)
    {
    case D_MAIN_MENU:
        mainMenuPlayer(); break;
    case D_IN_GAME:
        inGamePlayer(); break;
    case D_PAUSE:
        pausePlayer(); break;
    case D_GAME_OVER:
        gameOverPlayer(); break;
    default:
        break;
    }
}

void Game::mainMenuPlayer()
{
    m_sound_manager->playMusic();
}

void Game::inGamePlayer()
{
    m_sound_manager->playAmbient();

    for (Player* cur_player : m_entities->m_player)
    {
        if (cur_player->m_shoot)
            m_sound_manager->playShoot();

        if (cur_player->m_propulse)
            m_sound_manager->playPropulsion();

        if (cur_player->m_teleport)
            m_sound_manager->playTeleportation();
    } 

    if(m_entities->m_explosion)
        m_sound_manager->playExplosion();


    if (m_entities->m_enemy_manager->m_spawn)
        m_sound_manager->playSpawn();

    if (m_entities->m_enemy_manager->m_minelayer->m_is_alive)
        m_sound_manager->playMinelayer();
}

void Game::pausePlayer()
{
    
}

void Game::gameOverPlayer()
{

}

/*------------------------------------------------------END---------------------------------------------------------*/