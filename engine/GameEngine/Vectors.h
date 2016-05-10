//
//  Vectors.hpp
//  GameEngine
//
//  Created by David Lively on 2/10/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef VECTORS_H
#define VECTORS_H

#include <cmath>


struct Vector2
{
    float X;
    float Y;
    
    Vector2() : X(0), Y(0)
    {
    }
    
    Vector2(float x, float y) : X(x), Y(y)
    {
        
    }
    
};

struct Vector3 : public Vector2
{
    float Z;
    
    Vector3() : Vector2(), Z(0)
    {
        
    }
    
    Vector3(float x, float y, float z) : Vector2(x,y), Z(z)
    {
        
    }
    
    template<typename T>
    inline Vector3 operator* (const T& multiplier) const
    {
        return Vector3(X * multiplier, Y * multiplier, Z * multiplier);
    }
    
    template<typename T>
    inline Vector3& operator*=(const T& rval)
    {
        X *= rval;
        Y *= rval;
        Z *= rval;
        
        return *this;
    }
    
    template<typename T>
    inline Vector3& operator+=(const T& rval)
    {
        X += rval.X;
        Y += rval.Y;
        Z += rval.Z;
        
        return *this;
    }

    template<typename T>
    inline Vector3& operator-=(const T& rval)
    {
        X -= rval.X;
        Y -= rval.Y;
        Z -= rval.Z;
        
        return *this;
    }
    
    template<typename T>
    inline Vector3 operator-(const T& rval)
    {
        Vector3 temp;
        temp.X = X - rval.X;
        temp.Y = Y - rval.Y;
        temp.Z = Z - rval.Z;
        
        return temp;
    }
    
    template<typename T>
    inline Vector3& operator=(const T& rval)
    {
        X = rval;
        Y = rval;
        Z = rval;
        
        return *this;
    }
    
    inline static Vector3 cross(const Vector3& A, const Vector3& B)
    {
        float x = A.Y*B.Z - A.Z*B.Y;
        float y = A.Z*B.X - A.X*B.Z;
        float z = A.X*B.Y - A.Y*B.X;
        
        return Vector3(x,y,z);
    }
    inline static float dot(const Vector3& A, const Vector3& B)
    {
        return A.X * B.X + A.Y * B.Y + A.Z + B.Z;
    }
    
    inline static Vector3 normalize(Vector3 A)
    {
        float length = sqrtf(dot(A, A));
        A.X /= length;
        A.Y /= length;
        A.Z /= length;
        return A;
    }
    
};

struct Vector4 : public Vector3
{
    float W;
    
    Vector4() : Vector3(), W(0)
    {
        
    }
    
    Vector4(float x, float y, float z, float w) : Vector3(x,y,z)
    {
        
    }
};


#endif /* Vectors_hpp */
