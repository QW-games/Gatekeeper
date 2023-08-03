#include "MouseDragger.h"

MouseDragger::MouseDragger(GameObject& go) : Component(go) {
    mouseOffset = Vec2(0, 0);
    playDragSound = true;
}

void MouseDragger::Update(float dt) {
    InputManager& inputManager = InputManager::GetInstance();
    
    Vec2 mousePos = inputManager.GetMousePos();
    
    std::shared_ptr<GameObject> sharedDraggingObject = draggingObject.lock();
    
    if (sharedDraggingObject == nullptr && associated.box.Contains(mousePos) && inputManager.IsMouseDown(LEFT_MOUSE_BUTTON)) {
        mouseOffset = Vec2(mousePos.x - associated.box.x, mousePos.y - associated.box.y);
        State& state = Game::GetInstance().GetState();
        draggingObject = state.GetObjectPtr(&associated);
        state.BringToFront(&associated);
        
        for(auto object : state.objectArray) {
            if(object->GetComponent("Laser")){
                state.BringToFront(&(*object));
            }
        }
        
        Sound * dragSound = (Sound *) associated.GetComponent("Sound");
        if (dragSound == nullptr) {
            dragSound = new Sound(associated, "assets/audio/" + DataRandomizer::GetRandomFile("papel_arrastado", 3, "wav"));
            associated.AddComponent(dragSound);
        }
        dragSound->Play();
    }
    
    if (inputManager.MouseRelease(LEFT_MOUSE_BUTTON)) {
        if (sharedDraggingObject) {
            auto sharedPassenger = Passenger::currentPassenger.lock();
            
            //Soltou documento no passageiro
            if (sharedPassenger) {
                auto passengerCollider = (Collider *)sharedPassenger->GetComponent("Collider");
                if (passengerCollider->box.Contains(sharedDraggingObject->box.GetVecCentralizado())) {
                    auto passengerComponent = (Passenger*) sharedPassenger->GetComponent("Passenger");
                    passengerComponent->documents.emplace_back(sharedDraggingObject);
                    Game::GetInstance().GetState().WalkBack(5 + 17 + passengerComponent->accesories.size(), sharedDraggingObject.get());
                    if(sharedDraggingObject->GetComponent("Identity"))
                        sharedDraggingObject->GetComponent("Identity")->Obliterate();
                    else if(sharedDraggingObject->GetComponent("Passport"))
                        sharedDraggingObject->GetComponent("Passport")->Obliterate();
                }
                //Soltou documento acima da mesa, mas sem colisão com passageiro
                else if (mousePos.y < Game::GetInstance().GetWindowSize().y * .35) {
                    if(sharedDraggingObject->GetComponent("Identity"))
                        sharedDraggingObject->GetComponent("Identity")->FallToTable();
                    else if(sharedDraggingObject->GetComponent("Passport"))
                        sharedDraggingObject->GetComponent("Passport")->FallToTable();
                }
            }
        }
        
        draggingObject = std::weak_ptr<GameObject>();
        return;
    }

    if (sharedDraggingObject && sharedDraggingObject.get() == &associated) {
        if(sharedDraggingObject->GetComponent("Passport"))
            sharedDraggingObject->GetComponent("Passport")->ResetDestination(mousePos);
        else if(sharedDraggingObject->GetComponent("Identity"))
            sharedDraggingObject->GetComponent("Identity")->ResetDestination(mousePos);
        Vec2 step;
        step.x = Lerp(associated.box.GetVecCentralizado().x, mousePos.x, dt*10);
        step.y = Lerp(associated.box.GetVecCentralizado().y, mousePos.y, dt*10);
        associated.box.SetCentro(step);
        
        // auto distanceMoved = (step - associated.box.GetPosition()).Magnitude();
        
        // if (distanceMoved <= 5) {
        //     playDragSound = true;
        // }
        
        // if (distanceMoved > 5 && playDragSound) {
        //     Sound * dragSound = (Sound *) associated.GetComponent("Sound");
        //     if (dragSound == nullptr) {
        //         auto dragSound = new Sound(associated, "assets/audio/" + DataRandomizer::GetRandomFile("papelarrastado", 3, "wav"));
        //         associated.AddComponent(dragSound);
        //     }
        //     dragSound->Play();
        //     playDragSound = false;
        // }
    }
}

float MouseDragger::Lerp(float start, float target, float dt) {
    return start + (target - start) * dt;
}

void MouseDragger::Render() {
}

bool MouseDragger::Is(string type) {
    return type == "MouseDragger";
}
