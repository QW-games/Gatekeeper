#include "Passenger.h"

Passenger::Passenger(GameObject& associated) : Component(associated) {
    Sprite * passengerSprite = new Sprite(associated, DataRandomizer::GetRandomFile("assets/img/passenger", 2, "png"));
    passengerSprite->SetScaleX(0.7, 0.7);
    destination = Game::GetInstance().GetWindowSize();
    approvedDestination = Vec2(destination.x * 1.1, 260);
    disapprovedDestination = Vec2(-150, 260);
    destination.x *= .66;
    destination.y *= .41;
    associated.box.h = passengerSprite->GetHeight();
    associated.box.w = passengerSprite->GetWidth();
    associated.box.SetCentro(-150, Game::GetInstance().GetWindowSize().y * .45);
    associated.AddComponent(passengerSprite);
    start = associated.box.GetVecCentralizado();

    valid = rand() % 2;
    state = PassengerState::MOVING;
    approveState = ApproveState::NONE;
}

void Passenger::Start() {
    auto passenger = Game::GetInstance().GetState().GetObjectPtr(&associated);

    // Óculos
    if(rand() % 2){
        GameObject* tmp = new GameObject();
        Sprite *newGlasses = new Sprite(*tmp, DataRandomizer::GetRandomFile("assets/img/oculos", 3, "png"));

        tmp->box.h = newGlasses->GetHeight();
        tmp->box.w = newGlasses->GetWidth();
        tmp->box.SetCentro(associated.box.GetVecCentralizado());
        tmp->AddComponent(newGlasses);
        tmp->AddComponent(new Accessory(passenger, *tmp, 1));
        accesories.emplace_back(Game::GetInstance().GetState().AddObject(tmp));
    }
    // Chapéu
    if(rand() % 2){
        GameObject* tmp = new GameObject();
        Sprite *newHat = new Sprite(*tmp, DataRandomizer::GetRandomFile("assets/img/chapeu", 5, "png"));

        tmp->box.h = newHat->GetHeight();
        //x1 = tmp->box.h;
        tmp->box.w = newHat->GetWidth();
        //x2 = tmp->box.w;
        tmp->box.SetCentro(associated.box.GetVecCentralizado());
        tmp->AddComponent(newHat);
        tmp->AddComponent(new Accessory(passenger, *tmp, 0));
        accesories.emplace_back(Game::GetInstance().GetState().AddObject(tmp));
    }
}

void Passenger::DeleteAll() {
    associated.RequestDelete();

    for(auto document : documents) {
        auto sharedDocument = document.lock();
        if (sharedDocument) {
            sharedDocument->RequestDelete();
        }
    }

    for(auto accessory : accesories) {
        auto sharedAccessory = accessory.lock();
        if (sharedAccessory) {
            sharedAccessory->RequestDelete();
        }
    }
}

void Passenger::Update(float dt) {
    if (state == PassengerState::MOVING) {
        if ((destination == associated.box.GetVecCentralizado()) && !(approveState == ApproveState::NONE)) {
            DeleteAll();
            return;
        }
        
        Vec2 step = Vec2(PASSENGER_SPEED, 50) * dt;
        
        if (approveState == ApproveState::DISAPPROVED) {
            step.x = -step.x;
        }
        
        Vec2 difference = destination - associated.box.GetVecCentralizado();

        if (
            step.Magnitude() >= difference.Magnitude()
            || (approveState != ApproveState::DISAPPROVED  && associated.box.GetVecCentralizado().x > destination.x)
            || (approveState == ApproveState::DISAPPROVED && associated.box.GetVecCentralizado().x < destination.x)
        ) {
            destination = Game::GetInstance().GetWindowSize();
            destination.x *= .65;
            destination.y *= .45;
            associated.box.SetCentro(destination);
        } else {
            start.y = associated.box.GetVecCentralizado().y;
            step.y = Lerp(start.y, destination.y, dt * 3);
            associated.box.SetCentro(associated.box.GetVecCentralizado().x, step.y);
            associated.box.x += step.x;

            if(abs(destination.y - step.y) < 2)
                associated.box.SetCentro(associated.box.GetVecCentralizado().x, destination.y);

            if(associated.box.GetVecCentralizado().y >= (Game::GetInstance().GetWindowSize().y * .45)) {
                walk_state = true;
                destination.y = Game::GetInstance().GetWindowSize().y * .41;
            }
            else if(associated.box.GetVecCentralizado().y <= (Game::GetInstance().GetWindowSize().y * .42)) {
                walk_state = false;
                destination.y = Game::GetInstance().GetWindowSize().y * .46;
            }
        }

        for (auto accessory : accesories) {
            auto sharedAccessory = accessory.lock();
            if (sharedAccessory) {
                sharedAccessory->Update(dt);
            }
        }
      
        // CRIAÇÃO DE DOCUMENTOS
        if (destination == associated.box.GetVecCentralizado() && approveState == ApproveState::NONE) {
            State& gameState = Game::GetInstance().GetState();
            FlightInfo& flightInfo = FlightInfo::GetInstance();

            Vec2 startingPositionMultiplier = {1, 1.1};

            std::string cpf = DataRandomizer::GetCpf();
            std::string firstname = DataRandomizer::GetFirstName();
            std::string surname = DataRandomizer::GetSurname();
            std::string birthday = DataRandomizer::GetDate(50, 20);

            GameObject * goPassport = new GameObject();
            Passport * passport = new Passport(*goPassport);

            GameObject * goIdentity = new GameObject();
            Identity * identity = new Identity(*goIdentity);

            identity->SetCPF(cpf);
            identity->SetFirstName(firstname);
            identity->SetSurName(surname);
            identity->SetBirthday(birthday);

            passport->SetCPF(identity->GetCPF());
            passport->SetFirstName(identity->GetFirstName());
            passport->SetSurName(identity->GetSurName());
            passport->SetFlightDate(flightInfo.GetFlightDate());
            passport->SetFlightID(flightInfo.GetFlightID());
            passport->SetFlightOrigin(flightInfo.GetFlightOrigin());
            passport->SetFlightDestiny(flightInfo.GetFlightDestiny());

            //Bagunça alguma informação
            if(!valid) {
                // Identidade
                int choice = rand() % 2;
                if(choice) {
                    int data = rand() % 3 + 1;
                    switch(data){
                    case 1:
                        identity->SetCPF(DataRandomizer::AddErrorCpf(identity->GetCPF()));
                        break;
                    case 2:
                        while(identity->GetFirstName() == passport->GetFirstName())
                            identity->SetFirstName(DataRandomizer::GetFirstName());
                        break;
                    case 3:
                        while(identity->GetSurName() == passport->GetSurName())
                            identity->SetSurName(DataRandomizer::GetSurname());
                        break;
                    default:
                        break;
                    }
                }
                // Passaporte
                else {
                    int data = rand() % 7 + 1;
                    switch(data){
                    case 1:
                        passport->SetCPF(DataRandomizer::AddErrorCpf(passport->GetCPF()));
                        break;
                    case 2:
                        while(identity->GetFirstName() == passport->GetFirstName())
                            passport->SetFirstName(DataRandomizer::GetFirstName());
                        break;
                    case 3:
                        while(identity->GetSurName() == passport->GetSurName())
                            passport->SetSurName(DataRandomizer::GetSurname());
                        break;
                    case 4:
                        while(passport->GetFlightOrigin() == flightInfo.GetFlightOrigin()) {
                            passport->SetFlightOrigin(DataRandomizer::GetCountry());
                        }
                        break;
                    case 5:
                        while(passport->GetFlightDestiny() == flightInfo.GetFlightDestiny()) {
                            passport->SetFlightDestiny(DataRandomizer::GetCountry());
                        }
                        break;
                    case 6:
                        passport->SetFlightID(DataRandomizer::AddErrorIDFlight(passport->GetFlightID()));
                        break;
                    case 7:
                        while(passport->GetFlightDate() == flightInfo.GetFlightDate()) {
                            passport->SetFlightDate(DataRandomizer::GetDate(1, 1));
                        }
                        break;
                    default:
                        break;
                    }
                }
            }

            goPassport->AddComponent(passport);
            goPassport->box.SetCentro(associated.box.GetVecCentralizado() * startingPositionMultiplier);
            gameState.AddObject(goPassport);
            gameState.WalkBack(5 + 17 + accesories.size(), goPassport);
            
            goIdentity->AddComponent(identity);
            goIdentity->box.SetCentro(associated.box.GetVecCentralizado() * startingPositionMultiplier);
            gameState.AddObject(goIdentity);
            gameState.WalkBack(6 + 17 + accesories.size(), goIdentity);

            Sound  * ticketSound = new Sound(associated, "assets/audio/" + DataRandomizer::GetRandomFile("papeljogadonamesa", 5, "wav"));
            ticketSound->Play();
            ticketSound->SetVolume(10);
            associated.AddComponent(ticketSound);

            state = PassengerState::WAITING;
        }
    } else if(state == PassengerState::WAITING) {
        if (approveState == ApproveState::APPROVED) {
            destination = approvedDestination;
            state = PassengerState::MOVING;
        }
        
        if (approveState == ApproveState::DISAPPROVED) {
            destination = disapprovedDestination;
            state = PassengerState::MOVING;
        }
    }
}

void Passenger::Approve() {
    approveState = ApproveState::APPROVED;
}

void Passenger::Disapprove() {
    approveState = ApproveState::DISAPPROVED;
}

void Passenger::Render() {}

bool Passenger::Is(string type) {
    return type == "Passenger";
}

bool Passenger::IsMoving() {
    return state == PassengerState::MOVING;
}

float Passenger::Lerp(float start, float target, float dt) {
    return start + (target - start) * dt;
}

int Passenger::GetApproveState() {
    return approveState;
}

bool Passenger::GetValidity() {
    return valid;
}