#include "Accessory.h"
#include "Sprite.h"
#include "DataRandomizer.h"

Accessory::Accessory (weak_ptr<GameObject> passenger, GameObject& associated, int type) : Component(associated) {
    this->passenger = passenger;
	if(type == 0) {
		accessory = AccessorieType::HAT;
	} else if(type == 1) {
		accessory = AccessorieType::GLASSES;
	}
}

void Accessory::Update(float dt) {
    if (passenger.lock() == nullptr) {
		associated.RequestDelete();
	}
	else if(!passenger.expired()) {
		auto& p = *passenger.lock();
        Vec2 passengerCenter = p.box.GetVecCentralizado();
        associated.box.SetCentro(p.box.GetVecCentralizado());
		if(accessory == AccessorieType::GLASSES) {
			associated.box.y -= (p.box.h/2 - 70);
		} else {
			associated.box.y -= (p.box.h/2 - 15);
		}
	}
}

void Accessory::Render() {}

bool Accessory::Is(string type) {
    return type == "Acessory";
}