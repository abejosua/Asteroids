//
//  Ship.cpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "Common.h"
#include "Ship.h"
#include "Mesh.h"
#include "Game.h"
#include "Camera.h"

#include <vector>
#include <cmath>

using namespace std;

bool Ship::OnInitialize()
{
    auto& mesh = Create<Mesh>("ship-mesh");
    
    
    /// narrow triangle pointed along the positive Y axis
    vector<float> vertices =
    {
        0,0.5f, 0
        ,
        1/3.f, -0.5f, 0
        ,
        -1/3.f, -0.5f, 0
    };
    
    vector<GLushort> indices = {0,1,2};
    
    mesh.Initialize(vertices, indices);
    
    m_mesh = &mesh;
    
    

    auto& material = Create<class Material>("ship-material");
    m_material = &material;
    
    mesh.Material = &material;
    material.FillType = PolygonMode::Line;
    
    m_previousTranslation = Transform.Translation;

    BoundingSphere.center = Transform.Translation;
    BoundingSphere.radius = .75;
    
    
    return material.Build("Shaders/primitive");
}

void Ship::OnUpdate(const GameTime& time)
{
    
    Vector3 up = Transform.Up();
    
    if (glfwGetKey(Game::Instance().Window(), GLFW_KEY_RIGHT)) {
        Transform.Rotation.Z += 0.1f;
    }
    if (glfwGetKey(Game::Instance().Window(), GLFW_KEY_LEFT)) {
        Transform.Rotation.Z -= 0.1f;
    }
    if (glfwGetKey(Game::Instance().Window(), GLFW_KEY_UP)) {
        Transform.Translation += up * 0.02f;
    }
    
    float drag = 0.05f;
    
    Vector3 currentTranslation = Transform.Translation;
    
    Vector3 velocity = (currentTranslation - m_previousTranslation) * (1-drag);
    Transform.Translation += velocity;
    m_previousTranslation = currentTranslation;

    BoundingSphere.Update(Transform.Translation);
    
}




void Ship::OnRender(const GameTime& time)
{
    auto& cam = Game::Camera;
    cam.Transform.Translation.Z = 20;
    m_material->Bind();

    m_material->SetUniform("World", Transform.GetMatrix());
    m_material->SetUniform("View",cam.GetViewMatrix());
    m_material->SetUniform("Projection",cam.GetProjectionMatrix());
}

Matrix& Ship::GetClipMatrix() { 
    auto& cam = Game::Camera;
    m_clipMatrix = Transform.GetMatrix();
    return m_clipMatrix;
}

void Ship::moveVertical()
{
    Transform.Translation.Y *= -1;
    m_previousTranslation.Y *= -1;
    m_previousTranslation.Y += (Transform.Translation.Y - m_previousTranslation.Y)*2;
}

void Ship::moveHorizontal()
{
    Transform.Translation.X *= -1;
    m_previousTranslation.X *= -1;
    m_previousTranslation.X += (Transform.Translation.X - m_previousTranslation.X)*2;
   
}

void Ship::moveCenter()
{
    Transform.Translation.X = 0;
    Transform.Translation.Y = 0;
    m_previousTranslation.X = 0;
    m_previousTranslation.Y = 0;
}
