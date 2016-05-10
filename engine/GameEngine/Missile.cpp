//
//  Missile.cpp
//  GameEngine
//
//  Created by abe on 4/20/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "Missile.h"

#include "Mesh.h"
#include "Game.h"
#include "Camera.h"

#include <vector>
#include <cmath>

bool Missile::OnInitialize()
{
    auto& mesh = Create<Mesh>("missile-mesh");
    
    std::vector<float> vertices =
    {
        0,1.f, 0
        ,
       0, 0, 0
        ,
        0, -0, 0
    };
    
    std::vector<GLushort> indices = {0,1,2};
    
    mesh.Initialize(vertices, indices);
    
    m_mesh = &mesh;
    
    
    
    auto& material = Create<class Material>("missile-material");
    m_material = &material;
    
    mesh.Material = &material;
    material.FillType = PolygonMode::Line;
    m_velocity = Vector3(0, 0, 0);
    
    m_lifetime = 40;
    
    BoundingSphere.center = Transform.Translation;
    BoundingSphere.radius = .5;
    
    Disable();
    
    return material.Build("Shaders/primitive");
}

void Missile::OnUpdate(const GameTime& time)
{

    auto& cam = Game::Camera;
    
    Transform.Translation += m_velocity;
    
    m_lifetime -= 1;
    
    BoundingSphere.Update(Transform.Translation);
    
    m_material->Bind();
    
    m_material->SetUniform("World", Transform.GetMatrix());
    m_material->SetUniform("View",cam.GetViewMatrix());
    m_material->SetUniform("Projection",cam.GetProjectionMatrix());
    
    
}

void Missile::setVelocity(const float x, const float y)
{
    m_velocity = Vector3(x, y, 0);
}

bool Missile::lifeTimeOver()
{
    return m_lifetime < 0;
}

void Missile::OnRender(const GameTime& time)
{
}

void Missile::FillColor()
{
    m_material->FillType = PolygonMode::Fill;
}
void Missile::WireFrame()
{
    m_material->FillType = PolygonMode::Line;
}

void Missile::Enable()
{
    enabled = true;
    m_lifetime = 40;
}