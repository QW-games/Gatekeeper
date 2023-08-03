#include "Buttons.h"

Buttons::Buttons(GameObject& associated) : Component(associated) {
    Sprite * ButtonsSprite = new Sprite(associated, "assets/img/Group 26.png");
    ButtonsSprite->SetScaleX(0.7, 0.5);
	associated.AddComponent(ButtonsSprite);
    associated.box.h = ButtonsSprite->GetHeight();
	associated.box.w = ButtonsSprite->GetWidth();
	associated.box.SetCentro(Game::GetInstance().GetWindowSize().x * .25, Game::GetInstance().GetWindowSize().y * .93);
}

void Buttons::Update(float dt) {
    if(timer.Get() > 1.0) {
        associated.RemoveComponent("Sprite");
        Sprite *resetButton = new Sprite(associated, "assets/img/Group 26.png");
        resetButton->SetScaleX(0.7, 0.5);
        associated.box.w = resetButton->GetWidth();
        associated.box.h = resetButton->GetHeight();
        associated.box.SetCentro(associated.box.GetVecCentralizado());
        associated.AddComponent(resetButton);
    }
    timer.Update(dt);
}

void Buttons::Render() {
}

bool Buttons::Is(string type) {
    return type == "Buttons";
}

void Buttons::NotifyCollision(GameObject& other) {
    timer.Restart();
    auto sharedPassenger = Passenger::currentPassenger.lock();
    if(sharedPassenger) {
        auto passengerComponent = (Passenger*) sharedPassenger->GetComponent("Passenger");
        if(passengerComponent->GetApproveState() == 1) {
            associated.RemoveComponent("Sprite");
            Sprite *greenPressed = new Sprite(associated, "assets/img/Group 25.png");
            greenPressed->SetScaleX(0.7, 0.5);
            associated.box.w = greenPressed->GetWidth();
            associated.box.h = greenPressed->GetHeight();
            associated.box.SetCentro(associated.box.GetVecCentralizado());
            associated.AddComponent(greenPressed);
        } else if (passengerComponent->GetApproveState() == 2) {
            associated.RemoveComponent("Sprite");
            Sprite *redPressed = new Sprite(associated, "assets/img/Group 27.png");
            redPressed->SetScaleX(0.7, 0.5);
            associated.box.w = redPressed->GetWidth();
            associated.box.h = redPressed->GetHeight();
            associated.box.SetCentro(associated.box.GetVecCentralizado());
            associated.AddComponent(redPressed);
        }
    }
}
