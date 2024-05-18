#include <iostream>
#include <fstream>
#include <string>

#include "club.h"
#include "input.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    int numberTables;
    std::string openTime;
    std::string closeTime;
    int costPerHour;

    std::string line;
    try {
        ReadClubInfo(file, numberTables, openTime, closeTime, costPerHour, line);
        Club club(numberTables, openTime, closeTime, costPerHour);
        ReadEventsInfo(file, club, closeTime, line);
        club.PrintReport();
    } catch (const std::invalid_argument& e) {
        std::cerr << line << std::endl;
        return 1;
    } catch (const std::out_of_range& e) {
        std::cerr << line << std::endl;
        return 1;
    }
    return 0;
}