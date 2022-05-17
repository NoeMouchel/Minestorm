#include <iostream>

#include "../include/FXManager.h"
#include "../include/settings.h"

FXManager::FXManager(Texture* spriteSheet)
{
    m_spriteSheet = spriteSheet;
}

FXManager::~FXManager()
{
    clearFX();
}

void FXManager::update(float deltaTime)
{
    //Update each effect
    for (Effect* cur_fx : m_fx_list)
    {
        cur_fx->update(deltaTime);
    }

    //Check and delete effects that ended
    checkEffects();
}

void FXManager::checkEffects()
{
    int size = (int)m_fx_list.size();
    for (int i = 0; i < size; i++)
    {
        if (!m_fx_list[i]->m_is_occuring)
        {
            delete m_fx_list[i];
            m_fx_list.erase(m_fx_list.begin() + i);
            i--;
            size--;
        }
    }
}

void FXManager::clearFX()
{
    //  Clear explosion
    while (!m_fx_list.empty())
    {
        delete m_fx_list.back();
        m_fx_list.pop_back();
    }
}


void FXManager::draw(bool debug)
{
    for (Effect* cur_fx : m_fx_list)
        cur_fx->draw(debug);
}

void FXManager::bulletExplode(Entity* m_entity)
{
    m_fx_list.push_back(new Explosion(m_entity->m_referential, 2.f, 400.f, 50, m_spriteSheet, m_entity->m_color, false));
}

void FXManager::mineExplode(Entity* m_entity)
{
    m_fx_list.push_back(new Explosion(m_entity->m_referential, 3.f, 200.f, 75, m_spriteSheet, m_entity->m_color, true));
}

void FXManager::minelayerExplode(Entity* m_entity)
{
    m_fx_list.push_back(new Explosion(m_entity->m_referential, 2.f, 400.f, 50, m_spriteSheet, m_entity->m_color, true));
}

void FXManager::playerExplode(Entity* m_entity)
{
    m_fx_list.push_back(new Explosion(m_entity->m_referential, 5.f, 300.f, 75, m_spriteSheet, m_entity->m_color, true));
    m_fx_list.push_back(new Explosion(m_entity->m_referential, 5.f, 200.f, 75, m_spriteSheet, WHITE, true));
}


void FXManager::playerPropulse(Entity* m_entity)
{
    m_fx_list.push_back(new Propulsion(m_entity->m_referential, 2.f, 100.f, 2, m_spriteSheet,WHITE));
    m_fx_list.push_back(new Propulsion(m_entity->m_referential, 1.f, 50.f, 2, m_spriteSheet, m_entity->m_color));
}

void FXManager::playerTeleport(Entity* m_entity)
{
    m_fx_list.push_back(new Vortex(m_entity, 5.f, 100.f, .5f, 25.f, m_spriteSheet, WHITE));
    m_fx_list.push_back(new Vortex(m_entity, 5.f, 100.f, .5f, 25.f, m_spriteSheet, m_entity->m_color));
}

void FXManager::minelayerSpawn(Entity* m_entity)
{
    m_fx_list.push_back(new Vortex(m_entity, 10.f, 100.f, 2.f, 50.f, m_spriteSheet, RED));
}