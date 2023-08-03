#pragma once

#include "Component.h"
#include "InputManager.h"
#include "Vec2.h"
#include "State.h"
#include "Game.h"
#include "Sound.h"
#include "DataRandomizer.h"
#include "Passenger.h"

class MouseDragger : public Component {
public:
    MouseDragger(GameObject& go);
    void Update(float dt);
    void Render();
    bool Is(string type);
    float Lerp(float start, float target, float dt);
private:
    inline static std::weak_ptr<GameObject> draggingObject;
    Vec2 mouseOffset;
    
    bool playDragSound;
};