//
//  Missile.h
//  GameEngine
//
//  Created by abe on 4/20/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef Missile_h
#define Missile_h

#include "GeometryProvider.h"
#include "WorldEntity.h"
#include "Common.h"
#include "Mesh.h"

class Missile : public WorldEntity
{
public:
    
    Missile()
    {
        
    }
    
    bool OnInitialize() override;
    
    void OnUpdate(const GameTime& time) override;
    void OnRender(const GameTime& time) override;
    
    void setVelocity(const float x, const float y);
    
    bool lifeTimeOver();
    
    void FillColor();
    void WireFrame();
    
    void Enable();
    
private:
    Mesh* m_mesh;
    Material* m_material;
    Vector3 m_velocity;
    float m_lifetime;
};

#endif /* Missile_h */
