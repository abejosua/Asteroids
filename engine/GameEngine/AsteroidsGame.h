//
//  SimpleGame.hpp
//  GameEngine
//
//  Created by David Lively on 2/3/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "Game.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Missile.h"

class AsteroidsGame : public Game
{
public:
	AsteroidsGame() : ShaderFolder("Shaders/")
    {
    }
    
    bool OnCreateScene() override;
    

    /// location of shaders in the file system.
	std::string ShaderFolder;
    void OnUpdate(const GameTime& time) override;
    void OnPreUpdate(const GameTime& time) override;
    Ship& CreateShip();
    Asteroid& CreateAsteroid();
    Missile& CreateMissile();
    
    void boundCheck();
    void AsteroidHitUpdate(Asteroid* asteroid);
    
    void deleteMissile(Missile* missile);
    
    void ResetGame();
    void CreateLevel(int level);
    
    void ResetAsteroids();
    void CreateAsteroids(int asteroids);
    void CreateBabyAsteroids(Asteroid* asteroid);
    
    bool CollisionCheck(const WorldEntity &world1, const WorldEntity &world2);
    void ShootMissile(Missile* missile);
    void DestroyMissile(Missile* missile);
    
private:
    Ship* m_ship;
    Asteroid* m_asteroid;
    vector <Asteroid*> m_asteroids;
    vector <Missile*> m_missiles;
    float m_last_fire_time;
    
    int m_remainingAsteroids;
    int m_score;
    int m_remainingShip;
    int m_currentLevel;
    
};


#endif /* SimpleGame_hpp */
