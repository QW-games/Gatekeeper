#pragma once

#include "Component.h"
#include "Sprite.h"
#include "Collider.h"
#include "Sound.h"
#include "GameObject.h"

#include <memory>

class Scanner : public Component {
public:
    Scanner(GameObject& associated);

    void Update(float dt);
	void Render();
	bool Is(string type);
    
    void NotifyCollision(GameObject& other);
    
private:
    std::vector<std::shared_ptr<GameObject>> readObjects;
};