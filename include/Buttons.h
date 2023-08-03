#pragma once

#include "Component.h"
#include "Sprite.h"
#include "Collider.h"
#include "Sound.h"
#include "GameObject.h"
#include "Timer.h"
#include "Passenger.h"

#include <memory>

class Buttons : public Component {
public:
    Buttons(GameObject& associated);

    void Update(float dt);
	void Render();
	bool Is(string type);
    
    void NotifyCollision(GameObject& other);
    
private:
    std::vector<std::shared_ptr<GameObject>> readObjects;
    Timer timer;
};