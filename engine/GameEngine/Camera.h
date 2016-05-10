//
//  Camera.hpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "Common.h"
#include "WorldEntity.h"
#include "Matrix.h"
#include "Vectors.h"
#include "Ship.h"

class Camera : public WorldEntity
{
public:
    float FieldOfView;
    float ZNear;
    float ZFar;
    
    Camera() : FieldOfView(TO_RADIANS(45)), ZNear(1), ZFar(1000)
    {
        
    }

    Matrix& GetProjectionMatrix();
    Matrix& GetViewMatrix();
    
    void BuildFrustum();
    
    bool isInFrustum(WorldEntity& world);
    void wrapShip(Ship& ship);
    void wrap(WorldEntity& world);
    
private:
    float m_previousAspectRatio = 0;
    Matrix m_projectionMatrix;
    
    Matrix m_viewMatrix;
    
    Vector3 m_T;
    Vector3 m_B;
    Vector3 m_L;
    Vector3 m_R;
};


#endif /* Camera_h */
