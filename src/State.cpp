#include "State.h"

State::State(){
    quitRequested = false;
    popRequested = false;
    started = false;
}

State::~State(){
    objectArray.clear();
}

void State::Start() {
	LoadAssets();
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Start();
	}
	started = true;
}

weak_ptr<GameObject> State::AddObject(GameObject* object){
	shared_ptr<GameObject> sptr(object);
	objectArray.push_back(sptr);
	if(started == true){
		sptr->Start();
	}

	return weak_ptr<GameObject>(sptr);
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject* object){
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i].get() == object)
			return weak_ptr<GameObject>(objectArray[i]);
	}
	return weak_ptr<GameObject>();

}

void State::BringToFront(GameObject* object) {
    for (unsigned int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i].get() == object) {
            objectArray.emplace_back(objectArray[i]);
            objectArray.erase(objectArray.begin() + i);
            break;
        }
	}
}

/*void State::BringToBack(GameObject* object) {
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        if (objectArray[i].get() == object) {
            objectArray.erase(objectArray.begin() + i);
            auto objectShared = std::shared_ptr<GameObject>(object);
            objectArray.insert(objectArray.begin(), objectShared);
            break;
        }
    }
}*/

void State::WalkBack(int times, GameObject* object) {
    for (unsigned int i = 0; i < objectArray.size(); i++) {
		if(objectArray[i].get() == object){
			while(times--){
                std::rotate(objectArray.begin() + i, objectArray.begin() + i + 1, objectArray.begin() + (i - 1) + 1);
                i--;
            }
            return;
        }
    }
}

bool State::PopRequested(){
    return popRequested;
}

bool State::QuitRequested(){
    return quitRequested;
}

void State::StartArray(){
    for(unsigned int i= 0; i < objectArray.size(); i++){
        objectArray[i]->Start();
    }
    started = true;
}

void State::UpdateArray(float dt) {
    for(unsigned int i= 0; i < objectArray.size(); i++){
        objectArray[i]->Update(dt);
    }
}

void State::RenderArray(){
    for(unsigned int i = 0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}