#include "FlightInfo.h"

FlightInfo::FlightInfo() {
    SetFlightOrigin(DataRandomizer::GetCountry());
	SetFlightDestiny(DataRandomizer::GetCountry());
	while(GetFlightOrigin() == GetFlightDestiny()) {
		SetFlightDestiny(DataRandomizer::GetCountry());
	}
	SetFlightID(DataRandomizer::GetFlightID());
	SetFlightDate(DataRandomizer::GetDate(1, 1));
    passengerGoal = 5;
    currentScore = 0;
}

FlightInfo::~FlightInfo() {}

std::string FlightInfo::GetFlightDate() {
    return flightdate;
}

std::string FlightInfo::GetFlightID() {
    return flightid;
}

std::string FlightInfo::GetFlightOrigin() {
    return origin;
}

std::string FlightInfo::GetFlightDestiny() {
    return destination;
}

void FlightInfo::SetFlightDate(std::string flightdate) {
    this->flightdate = flightdate;
}

void FlightInfo::SetFlightID(std::string flightid) {
    this->flightid = flightid;
}

void FlightInfo::SetFlightOrigin(std::string origin) {
    this->origin = origin;
}

void FlightInfo::SetFlightDestiny(std::string destiny) {
    this->destination = destiny;
}

bool FlightInfo::Is(std::string type) {
    return type == "FlightInfo";
}

void FlightInfo::Update(float dt) {}

void FlightInfo::Render() {}

void FlightInfo::UpdateScore(int value) {
    if(value) {
        currentScore += 1;
    } else {
        currentScore -= 1;
    }
}

int FlightInfo::GetScore() {
    return currentScore;
}

int FlightInfo::GetGoal() {
    return passengerGoal;
}

FlightInfo& FlightInfo::GetInstance() {
    if (instance == nullptr) {
        instance = new FlightInfo();
    };
    return *instance;
}

void FlightInfo::ResetScore() {
    this->currentScore = 0;
}