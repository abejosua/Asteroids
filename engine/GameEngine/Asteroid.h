//
//  Asteroid.hpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef ASTEROID_H
#define ASTEROID_H

#include "GeometryProvider.h"
#include "WorldEntity.h"
#include "Common.h"
#include "Mesh.h"

class Asteroid : public WorldEntity
{
public:
    
    Asteroid()
    {
        
    }
    
    bool OnInitialize() override;
    
    void OnUpdate(const GameTime& time) override;
    void OnRender(const GameTime& time) override;
    
    void FillColor();
    void WireFrame();
    void Hit();
    int getLives();
    
private:
    Mesh* m_mesh;
    Material* m_material;
    Vector3 m_velocity;
    
    int m_lives;
};


#endif /* Asteroid_hpp */
