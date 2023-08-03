#pragma once

#include "Component.h"
#include "Passenger.h"

class Accessory : public Component {
public:
    Accessory (weak_ptr<GameObject> penguinBody, GameObject& associated, int type);
    void Update(float dt);
	void Render();
	bool Is(string type);
    
private:
    enum AccessorieType { HAT, GLASSES };
    AccessorieType accessory;
    weak_ptr<GameObject> passenger;
};