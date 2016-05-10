//
//  Camera.cpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#include "Game.h"
#include "Camera.h"
#include "Matrix.h"
#include <cmath>


Matrix& Camera::GetProjectionMatrix()
{
    /// check aspect
    int w, h;
    
    Game::GetFramebufferSize(&w, &h);
    
    float aspect = w * 1.f / h;
    
    if (aspect != m_previousAspectRatio)
    {
        m_projectionMatrix = Matrix::CreatePerspective(FieldOfView, aspect, ZNear, ZFar);
        m_previousAspectRatio = aspect;
    }
    
    return m_projectionMatrix;
    
}

Matrix& Camera::GetViewMatrix()
{
    auto t = Transform.Translation * -1.f;
    auto r = Transform.Rotation * -1.f;
    
    m_viewMatrix = Matrix::CreateRotation(r) * Matrix::CreateTranslation(t);
    
    return m_viewMatrix;
    
}

void Camera::BuildFrustum()
{
    int w, h;
    
    Game::GetFramebufferSize(&w, &h);
    
    float aspect = w * 1.f / h;
    float halfHeightSpace = ZNear * tanf(FieldOfView/2.f);
    float halfWidthSpace = halfHeightSpace * aspect;
    
    Vector3 A = Vector3(-halfWidthSpace, halfHeightSpace, ZNear);
    Vector3 B = Vector3(halfWidthSpace, halfHeightSpace, ZNear);
    Vector3 C = Vector3(halfWidthSpace, -halfHeightSpace, ZNear);
    Vector3 D = Vector3(-halfWidthSpace, -halfHeightSpace, ZNear);
    
    m_T = Vector3::cross(A, B);
//    m_T = Vector3::normalize(m_T);
    m_R = Vector3::cross(B, C);
//    m_R = Vector3::normalize(m_R);
    m_B = Vector3::cross(C, D);
//    m_B = Vector3::normalize(m_B);
    m_L = Vector3::cross(D, A);
//    m_L = Vector3::normalize(m_L);

}

bool Camera::isInFrustum(WorldEntity& world)
{
    auto object = world.Transform.Translation;
    auto objectView = (Matrix::Multiply(m_viewMatrix, object));
//    Log::Info << "Left: " <<Vector3::dot(objectView, m_L) << std::endl;
//    Log::Info << "Right: " <<Vector3::dot(objectView, m_R) << std::endl;
//    Log::Info << "Top: " <<Vector3::dot(objectView, m_T) << std::endl;
//    Log::Info << "Bottom: " <<Vector3::dot(objectView, m_B) << std::endl;
    
    if (Vector3::dot(objectView, m_T) > 13 || Vector3::dot(objectView, m_B) > 13 || Vector3::dot(objectView, m_R) > 13 || Vector3::dot(objectView, m_L) > 13)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Camera::wrapShip(Ship& ship)
{
    auto object = ship.Transform.Translation;
    auto objectView = (Matrix::Multiply(m_viewMatrix, object));
    
    
    if (Vector3::dot(objectView, m_T) > 13 || Vector3::dot(objectView, m_B) > 13)
    {
        ship.moveVertical();
    }
    if (Vector3::dot(objectView, m_R) > 13 || Vector3::dot(objectView, m_L) > 13)
    {
        ship.moveHorizontal();
    }
}

void Camera::wrap(WorldEntity& world)
{
    auto object = world.Transform.Translation;
    auto objectView = (Matrix::Multiply(m_viewMatrix, object));
    
    
    if (Vector3::dot(objectView, m_T) > 12 || Vector3::dot(objectView, m_B) > 12)
    {
        world.Transform.Translation.Y *= -1;
    }
    if (Vector3::dot(objectView, m_R) > 12 || Vector3::dot(objectView, m_L) > 12)
    {
        world.Transform.Translation.X *= -1;
    }
}