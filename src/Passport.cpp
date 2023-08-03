#include "Passport.h"
#include "Sound.h"

Passport::Passport(GameObject& associated) : Component(associated) {
    Sprite* passportSprite = new Sprite(associated, "assets/img/ticket.png");
    passportSprite->SetScaleX(0.08, 0.08);
    associated.box.h = passportSprite->GetHeight();
	associated.box.w = passportSprite->GetWidth();
    associated.AddComponent(passportSprite);

    associated.AddComponent(new MouseDragger(associated));

    auto currentPassenger = Passenger::currentPassenger.lock();
    if(currentPassenger) {
        destination = currentPassenger->box.GetVecCentralizado();
        destination.x += 40;
        destination.y -= 50;
    }
    
    scanned = false;
    deploying = true;
    obliterating = false;
}

void Passport::Update(float dt) {
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
                destination.x += 60;
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

float Passport::Lerp(float start, float target, float dt) {
    return start + (target - start) * dt * 1.5;
}

void Passport::Render() {
}

bool Passport::Is(std::string type) {
    return type == "Passport";
}

void Passport::Obliterate() {
    obliterating = true;
    auto currentPassenger = Passenger::currentPassenger.lock();
    if (currentPassenger) {
        destination = Vec2(associated.box.GetVecCentralizado().x, currentPassenger->box.GetVecCentralizado().y + 50);
    }
}

void Passport::FallToTable() {
    destination = Vec2(associated.box.GetVecCentralizado().x, Game::GetInstance().GetWindowSize().y * (0.47 + static_cast<float> (rand()) / (static_cast<float> (RAND_MAX/(0.55-0.47)))));
}

void Passport::ResetDestination(Vec2 newDes) {
    destination = newDes;
}

std::string Passport::GetCPF() {
    return cpf;
}

std::string Passport::GetFirstName() {
    return firstname;
}

std::string Passport::GetSurName() {
    return surname;
}

std::string Passport::GetFlightDate() {
    return flightdate;
}

std::string Passport::GetFlightID() {
    return flightid;
}

std::string Passport::GetFlightOrigin() {
    return origin;
}

std::string Passport::GetFlightDestiny() {
    return destiny;
}

void Passport::SetCPF(std::string cpf) {
    this->cpf = cpf;
}

void Passport::SetFirstName(std::string firstname) {
    this->firstname = firstname;
}

void Passport::SetSurName(std::string surname) {
    this->surname = surname;
}

void Passport::SetFlightDate(std::string flightdate) {
    this->flightdate = flightdate;
}

void Passport::SetFlightID(std::string flightid) {
    this->flightid = flightid;
}

void Passport::SetFlightOrigin(std::string origin) {
    this->origin = origin;
}

void Passport::SetFlightDestiny(std::string destiny) {
    this->destiny = destiny;
}

void Passport::NotifyCollision(GameObject& other) {
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
            position += 3;
            state.objectArray[position]->RemoveComponent("Text2");
            Text2* textCPFPassport = new Text2(*state.objectArray[position], "assets/font/Roboto-Regular.ttf", 30 * windowScale.x, Text2::TextStyle::BLENDED, "CPF: " + cpf, SDL_Color{ 255, 255, 255 });
            state.objectArray[position]->AddComponent(textCPFPassport);

            position += 1;
            state.objectArray[position]->RemoveComponent("Text2");
            Text2* textNamePassport = new Text2(*state.objectArray[position], "assets/font/Roboto-Regular.ttf", 30 * windowScale.x, Text2::TextStyle::BLENDED, "NOME: " + firstname + " " + surname, SDL_Color{ 255, 255, 255 });
            state.objectArray[position]->AddComponent(textNamePassport);

            position += 1;
            state.objectArray[position]->RemoveComponent("Text2");
            Text2* textFlightDate = new Text2(*state.objectArray[position], "assets/font/Roboto-Regular.ttf", 30 * windowScale.x, Text2::TextStyle::BLENDED, "DATA VOO: " + flightdate, SDL_Color{ 255, 255, 255 });
            state.objectArray[position]->AddComponent(textFlightDate);

            position += 1;
            state.objectArray[position]->RemoveComponent("Text2");
            Text2* textFlightID = new Text2(*state.objectArray[position], "assets/font/Roboto-Regular.ttf", 30 * windowScale.x, Text2::TextStyle::BLENDED, "ID VOO: " + flightid, SDL_Color{ 255, 255, 255 });
            state.objectArray[position]->AddComponent(textFlightID);

            position += 1;
            state.objectArray[position]->RemoveComponent("Text2");
            Text2* textOrigin = new Text2(*state.objectArray[position], "assets/font/Roboto-Regular.ttf", 30 * windowScale.x, Text2::TextStyle::BLENDED, "ORIGEM: " + origin, SDL_Color{ 255, 255, 255 });
            state.objectArray[position]->AddComponent(textOrigin);

            position += 1;
            state.objectArray[position]->RemoveComponent("Text2");
            Text2* textDestiny = new Text2(*state.objectArray[position], "assets/font/Roboto-Regular.ttf", 30 * windowScale.x, Text2::TextStyle::BLENDED, "DESTINO: " + destiny, SDL_Color{ 255, 255, 255 });
            state.objectArray[position]->AddComponent(textDestiny);
        }
        scanned = true;
    }
}