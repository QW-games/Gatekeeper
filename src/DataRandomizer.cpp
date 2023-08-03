#include "DataRandomizer.h"

std::string firstname[10] = {
    "Carlos",
    "Tadeu",
    "Douglas",
    "Julio",
    "Nicolas",
    "Soraia",
    "Andressa",
    "Carina",
    "Lorena",
    "Daniela"
};

std::string surname[10] = {
    "Gonzales",
    "Moraes",
    "Vaz",
    "Assis",
    "Brito",
    "Pimentel",
    "Carvalho",
    "Camargo",
    "Duarte",
    "Alves"
};

std::string country[10] = {
    "El Salvador",
    "Cambodia",
    "Malasia",
    "Liberia",
    "Marrocos",
    "China",
    "Uganda",
    "Croacia",
    "Suecia",
    "Senegal"
};

std::string DataRandomizer::GetCpf() {
    return GenerateCpf();
}

std::string DataRandomizer::GetFirstName() {
    return firstname[rand() % 10];
}

std::string DataRandomizer::GetSurname() {
    return surname[rand() % 10];
}

std::string DataRandomizer::GetDate(int maxY, int minY) {
    return GenerateDate(maxY, minY);
}

std::string DataRandomizer::GetFlightID() {
    return std::to_string(100000 + (rand()%(999999 - 100000 + 1)));
}

std::string DataRandomizer::GetCountry() {
    return country[rand() % 10];
}

std::string DataRandomizer::GenerateDate(int maxY, int minY) {
    time_t timer;
    struct tm x_years;
    struct tm* current;
    srand (time(NULL));
    int randomYear = minY + (rand()%(maxY - minY + 1));
    int randomMonth = (rand()%12)+1;
    int randomDays = (rand()%30)+1;

    time(&timer);
    current = localtime(&timer);
    x_years.tm_hour = 0;
    x_years.tm_min = 0;
    x_years.tm_sec = 0;
    x_years.tm_year = current->tm_year - randomYear;
    x_years.tm_mon = (current->tm_mon - randomMonth) <= 0 ? current->tm_mon + (12-randomMonth) : current->tm_mon - randomMonth;
    x_years.tm_mday = (current->tm_mday - randomDays) <= 0 ? current->tm_mday + (30-randomDays) : current->tm_mday - randomDays;

    return ApplyBirthdayMask(
        ((std::to_string(x_years.tm_mday).length() == 1 ? "0" + std::to_string(x_years.tm_mday) : std::to_string(x_years.tm_mday)) +
        (std::to_string(x_years.tm_mon).length() == 1 ? "0" + std::to_string(x_years.tm_mon) : std::to_string(x_years.tm_mon)) +
        std::to_string(x_years.tm_year+1900)));
}

std::string DataRandomizer::GenerateCpf() {
    std::string cpf = "";
    for (int i = 0; i < 9; i++)
        cpf += std::to_string(rand() % 9);

    int sum = 0;
    for (int i = 0; i < 9; i++)
        sum += (cpf[i] - '0') * (10 - i);

    int rest = 11 - (sum % 11);
    if (rest >= 10)
        cpf += "0";
    else
        cpf += std::to_string(rest);

    sum = 0;
    for (int i = 0; i < 10; i++)
        sum += (cpf[i] - '0') * (11 - i);

    rest = 11 - (sum % 11);
    if (rest >= 10)
        cpf += "0";
    else
        cpf += std::to_string(rest);

    return ApplyCpfMask(cpf);
}

std::string DataRandomizer::ApplyCpfMask(std::string cpf) {
    cpf.insert(3, ".");
    cpf.insert(7, ".");
    cpf.insert(11, "-");
    
    return cpf;
}

std::string DataRandomizer::ApplyBirthdayMask(std::string birthday) {
    birthday.insert(2, "/");
    birthday.insert(5, "/");
    
    return birthday;
}

std::string DataRandomizer::GetRandomFile(std::string fileName, int numberOfOptions, std::string fileExtension) {
    // Gerador pior, mas funciona.
    int randomNumber = 1 + rand() % numberOfOptions;
    std::cout << "PESSOA: " << randomNumber << std::endl;
    return fileName + to_string(randomNumber) + "." + fileExtension;
}

std::string DataRandomizer::AddErrorCpf(std::string cpf) {
    int index = 0 + (rand()%(13 - 0 + 1));
    while(index == 3 || index == 7 || index == 11) {
        index = 0 + (rand()%(13 - 0 + 1));
    }
    int value = cpf[index] - '0';
    value += 1 + (rand()%(9 - 1 + 1));
    value %= 10;
    cpf[index] = value + '0';
    return cpf;
}

std::string DataRandomizer::AddErrorIDFlight(std::string id) {
    int index = 0 + (rand()%(5 - 0 + 1));
    int value = id[index] - '0';
    value += 1 + (rand()%(9 - 1 + 1));
    value %= 10;
    id[index] = value + '0';
    return id;
}