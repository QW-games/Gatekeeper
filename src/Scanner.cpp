#include "Scanner.h"

Scanner::Scanner(GameObject& associated) : Component(associated) {
    Sprite * scannerSprite = new Sprite(associated, "assets/img/Group 22.png");
    scannerSprite->SetScaleX(0.75, 0.75);
	associated.AddComponent(scannerSprite);
    associated.box.h = scannerSprite->GetHeight();
	associated.box.w = scannerSprite->GetWidth();
	associated.box.SetCentro(Game::GetInstance().GetWindowSize().x * .9, Game::GetInstance().GetWindowSize().y * .44);
    
    auto collider = new Collider(associated);
    collider->SetScale(Vec2(0.2, 0.1));
    collider->SetOffset({0, 75});
    associated.AddComponent(collider);
    
    readObjects = {};
}

void Scanner::Update(float dt) {
}

void Scanner::Render() {
}

bool Scanner::Is(string type) {
    return type == "Scanner";
}

void Scanner::NotifyCollision(GameObject& other) {
    bool objectAlreadyRead = false;
    
    for (unsigned int i = 0; i < readObjects.size(); i++) {
        if (readObjects[i].get() == &other) {
            objectAlreadyRead = true;
        }
    }
    
    if (!objectAlreadyRead) {
        readObjects.emplace_back(&other);
        Sound * bipSound = new Sound(associated, "assets/audio/scanner.wav");
        associated.AddComponent(bipSound);
        bipSound->SetVolume(128);
        bipSound->Play();
    }
}
