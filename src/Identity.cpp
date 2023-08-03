#include "Identity.h"
#include "Sound.h"

Identity::Identity(GameObject& associated) : Component(associated) {
    Sprite* identitySprite = new Sprite(associated, "assets/img/identity.png");
    identitySprite->SetScaleX(0.08, 0.08);
    associated.box.h = identitySprite->GetHeight();
	associated.box.w = identitySprite->GetWidth();
    associated.AddComponent(identitySprite);

    associated.AddComponent(new MouseDragger(associated));

    auto currentPassenger = Passenger::currentPassenger.lock();
    if(currentPassenger) {
        destination = currentPassenger->box.GetVecCentralizado();
        destination.x -= 40;
        destination.y -= 50;
    }
    
    scanned = false;
    deploying = true;
    obliterating = false;
}

void Identity::Update(float dt) {
    static int soundPlayed = false;
    Vec2 step;

    Vec2 start = associated.box.GetVecCentralizado();
    step.x = Lerp(start.x, destination.x, dt * 3);
    step.y = Lerp(start.y, destination.y, dt * 3);
    Vec2 difference = destination - associated.box.GetVecCentralizado();

    if (deploying) {
        if (difference.Magnitude() < 3) {
            associated.box.SetCentro(destination);
            auto currentPassenger = Passenger::currentPassenger.lock();
            if (currentPassenger) {
                destination = currentPassenger->box.GetVecCentralizado();
                destination.x -= 60;
                destination.y += 30;
            }
            Game::GetInstance().GetState().BringToFront(&associated);


            if (associated.box.GetVecCentralizado() == destination) {
                if (!associated.GetComponent("Collider")) {
                    auto collider = new Collider(associated);
                    collider->SetScale(Vec2(0.7, 0.7));
                    associated.AddComponent(collider);
                }
                deploying = false;
            }
        }
        if (destination == associated.box.GetVecCentralizado() && !soundPlayed && difference.Magnitude() < 40) {
            soundPlayed = true;
            Sound  * sound = new Sound(associated, "assets/audio/" + DataRandomizer::GetRandomFile("papeljogadonamesa", 5, "wav"));
            sound->Play();
            sound->SetVolume(10);
            associated.AddComponent(sound);
        }
    }

    if (obliterating) {
        if(associated.box.GetVecCentralizado() == destination)
            obliterating = false;
        if (difference.Magnitude() < 3) {
            associated.box.SetCentro(destination);
            obliterating = false;
            return;
        }
    }
    associated.box.SetCentro(step);
}

float Identity::Lerp(float start, float target, float dt) {
    return start + (target - start) * dt * 1.5;
}

void Identity::Render() {
}

bool Identity::Is(std::string type) {
    return type == "Identity";
}

void Identity::Obliterate() {
    obliterating = true;
    auto currentPassenger = Passenger::currentPassenger.lock();
    if (currentPassenger) {
        destination = Vec2(associated.box.GetVecCentralizado().x, currentPassenger->box.GetVecCentralizado().y + 50);
    }
}

void Identity::FallToTable() {
    destination = Vec2(associated.box.GetVecCentralizado().x, Game::GetInstance().GetWindowSize().y * (0.47 + static_cast<float> (rand()) / (static_cast<float> (RAND_MAX/(0.55-0.47)))));
}

void Identity::ResetDestination(Vec2 newDes) {
    destination = newDes;
}

std::string Identity::GetCPF() {
    return cpf;
}

std::string Identity::GetFirstName() {
    return firstname;
}

std::string Identity::GetSurName() {
    return surname;
}

std::string Identity::GetBirthday() {
    return birthday;
}

void Identity::SetCPF(std::string cpf) {
    this->cpf = cpf;
}

void Identity::SetFirstName(std::string firstname) {
    this->firstname = firstname;
}

void Identity::SetSurName(std::string surname) {
    this->surname = surname;
}

void Identity::SetBirthday(std::string birthday) {
    this->birthday = birthday;
}

void Identity::NotifyCollision(GameObject& other) {
    Vec2 windowSize = Game::GetInstance().GetWindowSize();
	Vec2 windowScale = Vec2(windowSize.x/1920, windowSize.y/1080);
    int position;
    State& state = Game::GetInstance().GetState();
    Scanner* scanner = (Scanner*)other.GetComponent("Scanner");
    auto sharedPassenger = Passenger::currentPassenger.lock();
    if(sharedPassenger && scanner != nullptr) {
        auto passengerComponent = (Passenger*) sharedPassenger->GetComponent("Passenger");
        if(!scanned) {
            for(int i = 0; i < state.objectArray.size(); i++) {
                if(state.objectArray[i]->GetComponent("Text2")) {
                    position = i;
                    break;
                }
            }
            state.objectArray[position]->RemoveComponent("Text2");
            Text2* textCPFIdentity = new Text2(*state.objectArray[position], "assets/font/Roboto-Regular.ttf", 30 * windowScale.x, Text2::TextStyle::BLENDED, "CPF: " + cpf, SDL_Color{ 255, 255, 255 });
            state.objectArray[position]->AddComponent(textCPFIdentity);

            position += 1;
            state.objectArray[position]->RemoveComponent("Text2");
            Text2* textNameIdentity = new Text2(*state.objectArray[position], "assets/font/Roboto-Regular.ttf", 30 * windowScale.x, Text2::TextStyle::BLENDED, "NOME: " + firstname + " " + surname, SDL_Color{ 255, 255, 255 });
            state.objectArray[position]->AddComponent(textNameIdentity);

            position += 1;
            state.objectArray[position]->RemoveComponent("Text2");
            Text2* textBirthDayIdentity = new Text2(*state.objectArray[position], "assets/font/Roboto-Regular.ttf", 0, Text2::TextStyle::BLENDED, "NASC: " + birthday, SDL_Color{ 255, 255, 255 });
            state.objectArray[position]->AddComponent(textBirthDayIdentity);
        }
        scanned = true;
    }
}