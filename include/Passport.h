#pragma once

#include "MouseDragger.h"
#include "Component.h"
#include "Collider.h"
#include "DataRandomizer.h"
#include "Sprite.h"

class Passport : public Component {
public:
    Passport(GameObject& associated);

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Obliterate();
    void FallToTable();
    void ResetDestination(Vec2 newDes);

    std::string GetCPF();
    std::string GetFirstName();
    std::string GetSurName();
    std::string GetBirthday();
    std::string GetFlightDate();
    std::string GetFlightID();
    std::string GetFlightOrigin();
    std::string GetFlightDestiny();

    void SetCPF(std::string cpf);
    void SetFirstName(std::string firstname);
    void SetSurName(std::string surname);
    void SetFlightDate(std::string flightdate);
    void SetFlightID(std::string flightid);
    void SetFlightOrigin(std::string origin);
    void SetFlightDestiny(std::string destiny);

    void NotifyCollision(GameObject& other);
    
    float Lerp(float start, float target, float dt);
    
private:
    std::string cpf;
    std::string firstname;
    std::string surname;
    std::string flightdate;
    std::string flightid;
    std::string origin;
    std::string destiny;

    bool scanned;
    bool deploying;
    bool obliterating;
    Vec2 destination;
};