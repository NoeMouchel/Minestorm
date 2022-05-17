#include <iostream>
#include "../include/entitiesManager.h"




EntitiesManager::EntitiesManager(bool duo,Texture* spriteSheet)
{
    m_spriteSheet = spriteSheet;
    m_round = START_ROUND;

    m_player.push_back(new Player(PLAYER_ONE_X, PLAYER_ONE_Y, BLUE, spriteSheet));

    m_fx_manager = new FXManager(spriteSheet);
    m_enemy_manager = new EnemiesManager(spriteSheet, m_fx_manager, m_round);

	m_duo = duo;
    if (m_duo)
    {
        m_player.push_back(new Player(PLAYER_TWO_X, PLAYER_TWO_Y, GREEN, spriteSheet));
    }

    m_game_over     = false;
    m_next_round    = false;
    m_explosion     = false;

    m_check_collision       = true;
    minelayer_telport_done  = false;
}


EntitiesManager::~EntitiesManager()
{
    delete m_enemy_manager;
    delete m_fx_manager;

    while (!m_player.empty())
    {
        delete m_player.back();
        m_player.pop_back();
    }
}



void EntitiesManager::EventPlayers(float deltaTime)
{
    for (int i = 0; i < m_player.size(); i++)
    {
        if (!m_player[i]->m_is_alive) continue;

        //ROTATE TO RIGHT INPUTS
        if (IsKeyDown(m_inputs.turn_right[i]))
            m_player[i]->rotateRight(deltaTime);

        //ROTATE TO LEFT INPUTS
        if (IsKeyDown(m_inputs.turn_left[i]))
            m_player[i]->rotateLeft(deltaTime);


        //FORWARD INPUTS
        if (IsKeyDown(m_inputs.forward[i]))
        {
            //Propulse -> when starting topropulse
            if (!m_player[i]->m_can_propulse)
            {
                m_player[i]->m_propulse = true;
                m_fx_manager->playerPropulse(m_player[i]);
            }
            else
                m_player[i]->m_propulse = false;

            //can propulse
            m_player[i]->m_can_propulse = true;
        }
        else
            m_player[i]->m_can_propulse = false;

        //SHOOT INPUTS
        if (IsKeyDown(m_inputs.shoot[i]) && m_player[i]->m_shoot_timer > PLAYER_CADENCE)
            m_player[i]->m_can_shoot = true;
        else
            m_player[i]->m_can_shoot = false;

        //TELEPORT INPUTS
        if (IsKeyPressed(m_inputs.teleport1[i]) || IsKeyPressed(m_inputs.teleport2[i]))
        {
            m_fx_manager->playerTeleport(m_player[i]);
            m_player[i]->m_can_teleport = true;
        }
    }
    
}


void  EntitiesManager::update(float deltaTime)
{
    //Set sounds boolean to false
    m_explosion = false;

    if (m_check_collision)
        checkCollision();

    playersUpdate(deltaTime);

    //Update mine , spawnPoints and minelayer
    m_enemy_manager->update(deltaTime, m_player);

    //  Spawn animation of the minelayer
    if (m_enemy_manager->m_minelayer_spawn && !minelayer_telport_done)
    {
        minelayer_telport_done = true;
        m_fx_manager->minelayerSpawn(m_enemy_manager->m_minelayer);
    }

    checkPlayer(deltaTime);

    //  if the round is finished activate end round timer so we pass to the next round
    checkRound(deltaTime);

    m_fx_manager->update(deltaTime);
    
}

void EntitiesManager::playersUpdate(float deltaTime)
{
    for (Player* cur_player : m_player)
    {
        if (cur_player->m_is_alive)
        {

            if (cur_player->m_can_propulse)
                m_fx_manager->playerPropulse(cur_player);

            if (cur_player->m_teleport)
                m_fx_manager->playerTeleport(cur_player);
        }

        cur_player->update(deltaTime);
    }
}

void EntitiesManager::checkRound(float deltaTime)
{
    if (m_game_over || m_respawn_timer) return;
    if (m_enemy_manager->roundCleared())
    {
        m_endround_timer += deltaTime;
        if (m_endround_timer > 2.f)
        {
            m_round++;
            m_next_round = true;
            m_endround_timer = 0;
        }
    }
}


/*---------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------COLLISION------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------------------------*/


void EntitiesManager::multipolyCircleCollision(Entity* m_target, std::vector<Bullet*> bullets)
{
    MultiPolygonCollider* target_box = (MultiPolygonCollider*)m_target->m_collider;

    //  For each bullet
    size_t size = bullets.size();
    for (size_t i = 0; i < size; i++)
    {
        //  If AABB of the collider collided
        if (!intersectionBoxBox(target_box->m_AABB.m_box, bullets[i]->m_collider->m_AABB.m_box)) continue;

        bullets[i]->m_collider->m_AABB.m_collided = target_box->m_AABB.m_collided = true;
        
        //  For each polygon the mine collision box
        for (PolygonCollider poly : target_box->m_polygon_list)
        {
            //  If AABB of each polygons had not collided skip
            if (!intersectionBoxBox(poly.m_AABB.m_box, bullets[i]->m_collider->m_AABB.m_box)) continue;
            
            poly.m_AABB.m_collided = true;

            //  Test the collision between the circle and the polygon
            if (!intersectionConvexCircle(localToGlobalConvex(poly.m_polygon, m_target->m_referential), ((CircleCollider*)bullets[i]->m_collider)->m_circle)) continue;
            
            bullets[i]->m_collider->m_collided = m_target->m_collider->m_collided = target_box->m_collided = true;
            if (target_box->m_collided)
            {
                m_explosion = true;

                //  Create explosion FX
                m_fx_manager->bulletExplode(bullets[i]);

                break;
            }
        }
    }
}

void EntitiesManager::circleCircleCollision(Entity* m_target, std::vector<Bullet*> bullets)
{
    CircleCollider* target_box = (CircleCollider*)m_target->m_collider;

    //  For each bullet
    int size = (int)bullets.size();
    for (int i = 0; i < size; i++)
    {
        //  If AABB of the collider collided
        if (!intersectionBoxBox(target_box->m_AABB.m_box, bullets[i]->m_collider->m_AABB.m_box)) continue;

        bullets[i]->m_collider->m_AABB.m_collided = target_box->m_AABB.m_collided = true;

        //  Test the collision between the circle and the polygon
        if (!intersectionCircleCircle(target_box->m_circle, ((CircleCollider*)bullets[i]->m_collider)->m_circle)) continue;

        bullets[i]->m_collider->m_collided = m_target->m_collider->m_collided = target_box->m_collided = true;
        if (target_box->m_collided)
        {
            m_explosion = true;

            //  Create FX
            m_fx_manager->bulletExplode(bullets[i]);
            m_fx_manager->bulletExplode(m_target);

            m_player_score += FIREBALL_SCORE;
            break;
        }  
    }
}

void EntitiesManager::entityBulletCollision(Entity* m_target,std::vector<Bullet*> bullets)
{
    if (m_target->m_collider->m_type == C_MULTIPOLYGONE)
        multipolyCircleCollision(m_target, bullets);
    else if (m_target->m_collider->m_type == C_CIRCLE)
        circleCircleCollision(m_target, bullets);
}

void  EntitiesManager::checkCollision()
{
    //  Reset mine collision bool to false once here, because each mine can be checked multiple time 
    for (Mine* cur_mine : m_enemy_manager->m_mine_list)
        cur_mine->m_collider->setCollisionToFalse();

    for (Bullet* cur_fireball : m_enemy_manager->m_fireball_list)
        cur_fireball->m_collider->setCollisionToFalse();
    
    for(Player* cur_player : m_player)
        cur_player->m_collider->setCollisionToFalse();

    //  For each player we test the collision with the mine and also the collisions between mines and bullets
    for (Player* cur_player : m_player)
    {
        if (!cur_player->m_is_alive) continue;

        //  Check collision with mine
        checkMineCollision(cur_player);

        //  Check collision  between player and fireball
        entityBulletCollision(cur_player, m_enemy_manager->m_fireball_list);

        //  Check collision between players bullets and player
        checkPlayerPlayerCollision(cur_player);

        //Bullet vs fireball collision
        for(Bullet* current_fireball: m_enemy_manager->m_fireball_list)
            entityBulletCollision(current_fireball, cur_player->m_bullet_list);
       
        checkMinelayerCollision(cur_player);

        //  what happen if player collided
        playerCollided(cur_player);
    }
}

void  EntitiesManager::checkPlayerPlayerCollision(Player* cur_player)
{
    for (Player* other_player : m_player)
    {
        if (other_player == cur_player || !other_player->m_is_alive) continue;

        entityBulletCollision(other_player, cur_player->m_bullet_list);
    }
}

void  EntitiesManager::checkMinelayerCollision(Player* cur_player)
{
    Minelayer* m_minelayer = m_enemy_manager->m_minelayer;
    if (!m_minelayer->m_is_alive) return;

    //  If the Minelayer is still alive

    MultiPolygonCollider* minelayer_box = (MultiPolygonCollider*)m_minelayer->m_collider;
    MultiPolygonCollider* cur_player_box = (MultiPolygonCollider*)cur_player->m_collider;

    //  Test collision between the two polygons
    cur_player_box->collisionMulti(minelayer_box, cur_player->m_referential, m_minelayer->m_referential);

    entityBulletCollision(m_minelayer, cur_player->m_bullet_list);

    if (minelayer_box->m_collided)
    {
        m_minelayer->isDead();
        minelayer_box->m_collided = false;
        m_explosion = true;
        m_fx_manager->minelayerExplode(m_minelayer);
    }
}


void  EntitiesManager::playerCollided(Player* cur_player)
{
    //  Is the player touched by a mine?
    if (!cur_player->m_collider->m_collided) return;
    
    m_explosion = true;
    m_fx_manager->playerExplode(cur_player);
}

void  EntitiesManager::checkMineCollision(Player* cur_player)
{
    //  For eaxh mine we test the collisions with the player(s) and the bullets
    for (Mine* cur_mine : m_enemy_manager->m_mine_list)
    {
        MultiPolygonCollider* mine_box = (MultiPolygonCollider*)cur_mine->m_collider;

        //  Check if the bullets of the current player collide with a mine
        entityBulletCollision(cur_mine, cur_player->m_bullet_list);

        if (cur_mine->m_collider->m_collided)
            m_player_score += cur_mine->m_score;

        //  Check player collision between the mine polygons and the player polygon
        ((MultiPolygonCollider*)cur_player->m_collider)->collisionMulti(mine_box, cur_player->m_referential, cur_mine->m_referential);

        //  Is the mine hitted
        if (cur_mine->m_collider->m_collided)
        {
            m_explosion = true;
            m_fx_manager->mineExplode(cur_mine);
        }
    }
}


void EntitiesManager::checkPlayer(float deltaTime)
{
    bool game_over = true;
    bool respawn_player = true;

    for (Player* cur_player : m_player)
    {
        if (cur_player->m_life > 0)
        {
            game_over = false;
            if (cur_player->m_is_alive)
                respawn_player = false;
        }
    }

    if (game_over)
    {
        m_check_collision = false;
        m_gameover_timer += deltaTime;
        respawn_player = false;
        if (m_gameover_timer > 2.f)
        {
            m_game_over = true;
            m_gameover_timer = 0.f;
        }
    }

    //  Check if player is dead before checking round progress
    if (respawn_player)
    {
        m_check_collision = false;
        m_respawn_timer += deltaTime;
        if (m_respawn_timer > 2.f)
        {
            reset();
            m_respawn_timer = 0.f;
        }
    }
}

void EntitiesManager::reset()
{
    m_fx_manager->clearFX();

    //  Reset boolean
    m_check_collision = true;
    m_next_round = false;
    minelayer_telport_done = false;

    //  Reset enemies
    delete m_enemy_manager;
    m_enemy_manager = new EnemiesManager(m_spriteSheet, m_fx_manager, m_round);
    
    //  Check for each player if they can respawn
    for (Player* cur_player : m_player)
    {
        if (cur_player->m_life > 0)
            cur_player->reset();
    }
}


void EntitiesManager::drawEntity(bool debug)
{
    m_enemy_manager->drawEnemies(debug);
    for (Player* cur_player : m_player)
    {
        cur_player->draw(debug);
    }
    m_fx_manager->draw(debug);
}