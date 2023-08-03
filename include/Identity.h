#pragma once

#include "MouseDragger.h"
#include "Component.h"
#include "Collider.h"
#include "DataRandomizer.h"
#include "Sprite.h"
#include "Scanner.h"
#include "Text2.h"

class Identity : public Component {
public:
    Identity(GameObject& associated);

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Obliterate();
    void FallToTable();
    void ResetDestination(Vec2 newDes);
    
    float Lerp(float start, float target, float dt);

    std::string GetCPF();
    std::string GetFirstName();
    std::string GetSurName();
    std::string GetBirthday();

    void SetCPF(std::string cpf);
    void SetFirstName(std::string firstname);
    void SetSurName(std::string surname);
    void SetBirthday(std::string birthday);

    void NotifyCollision(GameObject& other);
    
private:
    std::string cpf;
    std::string firstname;
    std::string surname;
    std::string birthday;

    bool deploying;
    bool obliterating;
    bool scanned;
    Vec2 destination;
};