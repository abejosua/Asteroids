//
//  Asteroid.cpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "Asteroid.h"
#include "Mesh.h"
#include "Game.h"
#include "Camera.h"

#include <vector>
#include <cmath>

bool Asteroid::OnInitialize()
{
    auto& mesh = Create<Mesh>("asteroid-mesh");
    
    m_lives = 1;
    
    
    /// narrow triangle pointed along the positive Y axis
    std::vector<Vector3> vertices;
    std::vector<GLushort> indices;
    GeometryProvider::Icosahedron(vertices, indices);
    
    
    
    mesh.Initialize(vertices, indices);
    
    m_mesh = &mesh;
    
    
    
    auto& material = Create<class Material>("asteroid-material");
    m_material = &material;
    
    mesh.Material = &material;
    material.FillType = PolygonMode::Line;
    float xV =(float) ((rand() % 1500) - 750) * 0.0001f;
    float yV = (float) ((rand() % 1500) - 750) * 0.0001f;
    m_velocity = Vector3(xV, yV, 0);
    
    BoundingSphere.center = Transform.Translation;
    BoundingSphere.radius = 1;
    
    return material.Build("Shaders/primitive");
}

void Asteroid::OnUpdate(const GameTime& time)
{
    
    auto& cam = Game::Camera;
    
    if (!enabled)
    {
        if (Transform.Translation.Z >= -100)
        {
            Transform.Translation.Z -= .2;
        }
        
    }
    else
    {
//        Transform.Translation += m_velocity;
        if (Transform.Translation.Z <= 0)
        {
            Transform.Translation.Z += .5;
            if(Transform.Translation.X >= 10)
            {
                Transform.Translation.X -= .5;
            }
            else if (Transform.Translation.X <= -10)
            {
                Transform.Translation.X += .5;
            }
            if(Transform.Translation.Y >= 7)
            {
                Transform.Translation.Y -= .5;
            }
            else if (Transform.Translation.Y <= -7)
            {
                Transform.Translation.Y += .5;
            }
        }
    }
    
    Transform.Rotation.X += 0.01f;
    Transform.Rotation.Y += 0.01f;
    
    Transform.Translation += m_velocity;
    
    BoundingSphere.Update(Transform.Translation);
    
    m_material->Bind();
    
    m_material->SetUniform("World", Transform.GetMatrix());
    m_material->SetUniform("View",cam.GetViewMatrix());
    m_material->SetUniform("Projection",cam.GetProjectionMatrix());
}
void Asteroid::OnRender(const GameTime& time)
{
    
}

void Asteroid::FillColor()
{
    m_material->FillType = PolygonMode::Fill;
}
void Asteroid::WireFrame()
{
    m_material->FillType = PolygonMode::Line;
}

void Asteroid::Hit()
{
    m_lives--;
}

int Asteroid::getLives()
{
    return m_lives;
}