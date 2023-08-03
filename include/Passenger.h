#pragma once

#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"
#include "DataRandomizer.h"
#include "Game.h"
#include "Identity.h"
#include "Passport.h"
#include "Collider.h"
#include "Sound.h"
#include "EndState.h"
#include "GameData.h"
#include "Accessory.h"
#include "FlightInfo.h"

#define PASSENGER_SPEED 300

class Passenger : public Component {
public:
    Passenger(GameObject& associated);
    void Start();
    void Update(float dt);
	void Render();
	bool Is(string type);
    
    void Approve();
    void Disapprove();
    
    bool IsMoving();
    
    inline static weak_ptr<GameObject> currentPassenger;
    int GetApproveState();
    bool GetValidity();
    void DeleteAll();
    
    vector<weak_ptr<GameObject>> documents;
    vector<weak_ptr<GameObject>> accesories;
    
private:
    enum PassengerState { MOVING, WAITING };
    enum ApproveState { NONE, APPROVED, DISAPPROVED };
    bool walk_state;
    bool valid;
    PassengerState state;

    Vec2 destination;
    Vec2 start;

    ApproveState approveState;

    Vec2 approvedDestination;
    Vec2 disapprovedDestination;

    float Lerp(float start, float target, float dt);
};
