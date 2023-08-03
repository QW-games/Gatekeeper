#pragma once

#include "GameObject.h"

#include "Camera.h"
#include "Game.h"

class Collider : public Component {
public:
    Collider(GameObject& associated, Vec2 scale = { 1, 1 }, Vec2 offset = { 0, 0 });
    
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void SetScale(Vec2 scale);
    void SetOffset(Vec2 offset);
    
    Rect box;
    
    inline static bool debugMode = false;
    
private:
    Vec2 scale;
    Vec2 offset;
};