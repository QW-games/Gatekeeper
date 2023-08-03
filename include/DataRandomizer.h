#pragma once

#include "Sound.h"

#include <random>
#include <string>
#include <ctime>
#include <cstdlib>

class DataRandomizer {
public:
    static std::string GetFirstName();
    static std::string GetSurname();
    static std::string GetDate(int maxY, int minY);
    static std::string GetFlightID();
    static std::string GetCountry();
    static std::string GetCpf();

    static std::string AddErrorCpf(std::string cpf);
    static std::string AddErrorIDFlight(std::string id);

    static std::string GetRandomFile(std::string fileName, int numberOfOptions, std::string fileExtension);
    
private:
    static std::string GenerateCpf();
    static std::string GenerateDate(int maxY, int minY);
    static std::string ApplyCpfMask(std::string cpf);
    static std::string ApplyBirthdayMask(std::string birthday);
};