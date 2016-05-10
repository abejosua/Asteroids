//
//  Ship.hpp
//  GameEngine
//
//  Created by David Lively on 2/22/16.
//  Copyright © 2016 David Lively. All rights reserved.
//

#ifndef SHIP_H
#define SHIP_H

#include "Common.h"
#include "WorldEntity.h"
#include "Mesh.h"

class Ship : public WorldEntity
{
public:
    
    Ship()
    {
        
    }
    
    bool OnInitialize() override;
    
    void OnUpdate(const GameTime& time) override;
    void OnRender(const GameTime& time) override;
    
    Vector3 acceleration;
    
    Matrix& GetClipMatrix();
    
    void moveVertical();
    void moveHorizontal();
    void moveCenter();
    
private:
    Mesh* m_mesh;
    Material* m_material;
    
    Vector3 m_previousTranslation;
    Matrix m_clipMatrix;
};


#endif /* Ship_hpp */
