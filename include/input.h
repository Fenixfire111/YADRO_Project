#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>

#include "my_time.h"
#include "club.h"

void ReadClubInfo(std::ifstream& file, int& numberTables, std::string& openTime, 
 std::string& closeTime, int& costPerHour, std::string& line);

void ReadEventsInfo(std::ifstream& file, Club& club, const std::string& closeTime, std::string& line);