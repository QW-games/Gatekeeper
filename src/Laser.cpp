#include "Laser.h"

Laser::Laser(GameObject& associated) : Component(associated) {
    Sprite * LaserSprite = new Sprite(associated, "assets/img/laser.png");
	associated.AddComponent(LaserSprite);
    associated.box.h = LaserSprite->GetHeight();
	associated.box.w = LaserSprite->GetWidth();
	associated.box.SetCentro(Game::GetInstance().GetWindowSize().x * .9, Game::GetInstance().GetWindowSize().y * .48);
}

void Laser::Update(float dt) {}

void Laser::Render() {}

bool Laser::Is(string type) {
    return type == "Laser";
}
