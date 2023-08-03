#pragma once

#include "Component.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Passenger.h"

class Laser : public Component {
public:
    Laser(GameObject& associated);

    void Update(float dt);
	void Render();
	bool Is(string type);
};