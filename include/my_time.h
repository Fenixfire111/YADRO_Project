#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

class Time {

private:
    int hours_;
    int minutes_;
    
public:
    Time();
    Time(int hours, int minutes);
    Time(const std::string& strTime);

    int GetHours() const;
    int GetMinutes() const;
    std::string toString() const;

    bool operator<(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator>=(const Time& other) const;
    Time operator-(const Time& other) const;
    Time& operator+=(const Time& other);

    friend std::ostream& operator<<(std::ostream& os, const Time& time);

private:
    void normalize();
};