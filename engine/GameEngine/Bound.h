//
//  Bound.h
//  GameEngine
//
//  Created by abe on 3/28/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef Bound_h
#define Bound_h

#include "Vectors.h"

class BoundingSphere {
public:
    float radius;
    Vector3 center;
    
    BoundingSphere()
    {
        
    }
    BoundingSphere(const Vector3& center, const float radius)
    {
        this->radius = radius;
        this->center = center;
    }
    
    void Update(const Vector3& center)
    {
        this->center = center;
    }


    
    bool inline static instersect (const BoundingSphere& first, const BoundingSphere& other)
    {
        Vector3 delta = Vector3(first.center.X - other.center.X, first.center.Y - other.center.Y, first.center.Z - other.center.Z);
        
        float sumSquared = delta.X * delta.X + delta.Y * delta.Y + delta.Z * delta.Z;
        float sumRadiusSquared = (first.radius + other.radius) * (first.radius + other.radius);
        
        return sumSquared < sumRadiusSquared;
    }

};

#endif /* Bound_h */
