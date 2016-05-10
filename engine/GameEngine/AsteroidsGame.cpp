//
//  SimpleGame.cpp
//  GameEngine
//
//  Created by David Lively on 2/3/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include <vector>
#include <iostream>

using namespace std;

#include "AsteroidsGame.h"
#include "Mesh.h"
#include "Material.h"
#include "Files.h"

#include <cmath>


bool AsteroidsGame::OnCreateScene()
{
    m_ship = &CreateShip();
    
    for(int i = 0; i < 30; i++)
    {
        m_asteroids.push_back(&CreateAsteroid());
        
    }
    for(int i = 0; i < 6; i++)
    {
        m_missiles.push_back(&CreateMissile());
    }
    
    auto& cam = Game::Camera;
    
    cam.BuildFrustum();
    
    cam.Transform.Translation.Z = 2;
    
    m_last_fire_time = Game::Time.ElapsedSeconds();
    
    m_currentLevel = 1;
    CreateLevel(m_currentLevel);

    return true;
    
}

Asteroid& AsteroidsGame::CreateAsteroid()
{
    auto& asteroid = Create<Asteroid>("asteroid");
    asteroid.Initialize();
    asteroid.Transform.Translation.X += (float) ((rand() % 20)-10);
    asteroid.Transform.Translation.Y += (float) ((rand() % 20)-10);
    asteroid.Transform.Translation.Z = -100;
    asteroid.Disable();
    
    return asteroid;
}

Ship& AsteroidsGame::CreateShip()
{
    auto& ship = Create<Ship>("ship");
    
    return ship;
}

Missile& AsteroidsGame::CreateMissile()
{
    auto& missile = Create<Missile>("missile");
    missile.Initialize();
    missile.Transform.Translation.Z = 100;
    missile.Disable();
    
    return missile;
}

void AsteroidsGame::OnUpdate(const GameTime& time)
{
    if (m_remainingAsteroids <= 0)
    {
        m_currentLevel++;
        CreateLevel(m_currentLevel);
    }
    
    boundCheck();
    
    float gameTime = time.TotalSeconds();

    if (glfwGetKey(Game::Instance().Window(), GLFW_KEY_SPACE) && gameTime - m_last_fire_time > .3) {
        
        bool fired = false;
        int missileIndex = 0;
        while (!fired)
        {
            if(missileIndex < m_missiles.size() && !m_missiles[missileIndex]->enabled)
            {
                ShootMissile(m_missiles[missileIndex]);
                fired = true;
            }
            missileIndex++;
        }
        m_last_fire_time = gameTime;
        
    }

    for (int i = 0; i < m_asteroids.size(); i++)
    {
        if (m_asteroids[i]->enabled)
        {
            if (CollisionCheck(*m_asteroids[i], *m_ship))
            {
                m_remainingShip -= 1;
                if (m_remainingShip < 1)
                {
                    ResetGame();
                }
                else
                {
                    m_asteroids[i]->FillColor();
                    AsteroidHitUpdate(m_asteroids[i]);
                    m_ship->moveCenter();
                }
                
                
            }
            else
            {
                m_asteroids[i]->WireFrame();
            }
            for (int j = 0; j < m_missiles.size(); j++)
            {
                if (m_missiles[j]->enabled && CollisionCheck(*m_asteroids[i], *m_missiles[j]))
                {
                    m_score += 50;
                    DestroyMissile(m_missiles[j]);
                    AsteroidHitUpdate(m_asteroids[i]);
                    m_asteroids[i]->FillColor();
                }
                else
                {
                    m_asteroids[i]->WireFrame();
                }
            }
        }
        
    }
    for (int j = 0; j < m_missiles.size(); j++)
    {
        if (m_missiles[j]->enabled && m_missiles[j]->lifeTimeOver())
        {
            DestroyMissile(m_missiles[j]);
        }
    }
    
}

void AsteroidsGame::boundCheck()
{
    if (!Game::Camera.isInFrustum(*m_ship))
    {
        Game::Camera.wrapShip(*m_ship);
    }
    for (int i = 0; i < m_asteroids.size(); i++)
    {
        if(!Game::Camera.isInFrustum(*m_asteroids[i]))
        {
            Game::Camera.wrap(*m_asteroids[i]);
        }
    }
    for (int i = 0; i < m_missiles.size(); i++)
    {
        if(!Game::Camera.isInFrustum(*m_missiles[i]))
        {
            Game::Camera.wrap(*m_missiles[i]);
        }
    }
    Log::Info << "Level " << m_currentLevel << endl;
    Log::Info << "Score: " << m_score << endl;
    Log::Info << "Remaining Lives: " << m_remainingShip << endl;
    Log::Info << "Remaining Asteroids: " << m_remainingAsteroids << endl;
}

void AsteroidsGame::DestroyMissile(Missile* missile)
{
    missile->Transform.Translation.Z = 100;
    missile->Disable();
}

void AsteroidsGame::OnPreUpdate(const GameTime &time)
{
    
}

void AsteroidsGame::ResetGame()
{
    m_currentLevel = 1;
    CreateLevel(m_currentLevel);
}

void AsteroidsGame::CreateLevel(int level)
{
    ResetAsteroids();
    if (level == 1)
    {
        m_score = 0;
        m_remainingShip = 3;
    }
    
    m_remainingAsteroids = 2 + level * 2;
//    m_ship->moveCenter();
    
    CreateAsteroids(2 + level * 2);

}

void AsteroidsGame::ResetAsteroids()
{
    for (int i = 0; i < m_asteroids.size(); i++)
    {
        m_asteroids[i]->Disable();
    }
}

void AsteroidsGame::CreateAsteroids(int asteroids)
{
    for (int i = 0; i < asteroids; i++)
    {
        m_asteroids[i]->Enable();
    }
}

void AsteroidsGame::AsteroidHitUpdate(Asteroid* asteroid)
{
    asteroid->Hit();
    if(asteroid->getLives() <= 0)
    {
        asteroid->Disable();
        m_remainingAsteroids--;
    }
    else
    {
        CreateBabyAsteroids(asteroid);
    }
}

void AsteroidsGame::CreateBabyAsteroids(Asteroid* asteroid)
{
    bool recycleAsteroidFound = false;
    int asteroidIndex = 0;
    while (!recycleAsteroidFound)
    {
        if(asteroidIndex < m_asteroids.size() && !m_asteroids[asteroidIndex]->enabled)
        {
            m_asteroids[asteroidIndex]->Enable();
            m_asteroids[asteroidIndex]->Transform = asteroid->Transform;
            m_asteroids[asteroidIndex]->Transform.Scale *= .5;
            m_asteroids[asteroidIndex]->Transform.Translation.X *= 2;
            m_asteroids[asteroidIndex]->Transform.Translation.Y *= 2;
            
            asteroid->Transform.Scale *= .5;
            asteroid->Transform.Translation.X *= 2;
            asteroid->Transform.Translation.Y *= 2;
            
            recycleAsteroidFound = true;
            m_remainingAsteroids++;
        }
        asteroidIndex++;
    }
}

bool AsteroidsGame::CollisionCheck(const WorldEntity &world1, const WorldEntity &world2)
{
    return BoundingSphere::instersect(world1.BoundingSphere, world2.BoundingSphere);
}

void AsteroidsGame::ShootMissile(Missile* missile)
{
    missile->Enable();
    float velocityModifier = 0.4;
    missile->setVelocity(m_ship->Transform.Up().X*velocityModifier, m_ship->Transform.Up().Y*velocityModifier);
    missile->Transform.Translation = m_ship->Transform.Translation;
    missile->Transform.Rotation = m_ship->Transform.Rotation;
    missile->Transform.Translation.Z = 0;
}