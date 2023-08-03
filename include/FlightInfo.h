#pragma once

#include "Component.h"
#include "DataRandomizer.h"
#include <string>

class FlightInfo {
    public:
        static FlightInfo& GetInstance();
        ~FlightInfo();
        void Update(float dt);
        void Render();

        std::string GetFlightDate();
        std::string GetFlightID();
        std::string GetFlightOrigin();
        std::string GetFlightDestiny();

        void SetFlightDate(std::string flightdate);
        void SetFlightID(std::string flightid);
        void SetFlightOrigin(std::string origin);
        void SetFlightDestiny(std::string destiny);

        bool Is(std::string type);

        void UpdateScore(int value);
        int GetScore();
        int GetGoal();

        void ResetScore();
    
    private:
        FlightInfo();
        inline static FlightInfo *instance;

        std::string origin;
        std::string destination;
        std::string flightdate;
        std::string flightid;

        int passengerGoal;
        int currentScore;
};