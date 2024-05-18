#include "my_time.h"
#include <cmath>

Time::Time() : hours_(0), minutes_(0) { }

Time::Time(int hours, int minutes) : hours_(hours), minutes_(minutes) {
    normalize();
}

Time::Time(const std::string& strTime) {
    if (strTime.length() != 5 || strTime[2] != ':') {
        throw std::invalid_argument("Invalid time format");
    }
    std::size_t posH, posM;
    hours_ = std::stoi(strTime.substr(0,2), &posH);
    minutes_ = std::stoi(strTime.substr(3,2), &posM);
    if (posH < 2 || posM < 2) {
        throw std::invalid_argument("Invalid time format");
    }
    if (hours_ < 0 || hours_ >= 24 || minutes_ < 0 || minutes_ >= 60) {
        throw std::invalid_argument("Invalid time format");
    }
}

int Time::GetHours() const {
    return hours_;
}

int Time::GetMinutes() const {
    return minutes_;
}

std::string Time::toString() const {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours_ << ":"
        << std::setw(2) << std::setfill('0') << minutes_;
    return oss.str();
}

bool Time::operator<(const Time& other) const {
    if (hours_ < other.hours_) {
        return true;
    } else if (hours_ == other.hours_) {
        return minutes_ < other.minutes_;
    } else {
        return false;
    }
}

bool Time::operator>(const Time& other) const {
    if (hours_ > other.hours_) {
        return true;
    } else if (hours_ == other.hours_) {
        return minutes_ > other.minutes_;
    } else {
        return false;
    }
}

bool Time::operator>=(const Time& other) const {
    if (hours_ > other.hours_) {
        return true;
    } else if (hours_ == other.hours_) {
        return minutes_ >= other.minutes_;
    } else {
        return false;
    }
}

Time& Time::operator+=(const Time& other) {
    hours_ += other.hours_;
    minutes_ += other.minutes_;
    normalize();
    return *this;
}

Time Time::operator-(const Time& other) const {
    int totalMinutes1 = hours_ * 60 + minutes_;
    int totalMinutes2 = other.hours_ * 60 + other.minutes_;
    int diffMinutes = totalMinutes1 - totalMinutes2;

    if (diffMinutes < 0) {
        diffMinutes = 0;
    }

    return Time(diffMinutes / 60, diffMinutes % 60);
}

std::ostream& operator<<(std::ostream& os, const Time& time) {
    os << std::setw(2) << std::setfill('0') << time.hours_ << ":"
     << std::setw(2) << std::setfill('0') << time.minutes_;
    return os;
}

void Time::normalize() {
    if (minutes_ >= 60) {
        hours_ += minutes_ / 60;
        minutes_ %= 60;
    } else if (minutes_ < 0) {
        hours_ -= (std::abs(minutes_) / 60) + 1;
        minutes_ = 60 - (std::abs(minutes_) % 60);
    }

    if (hours_ < 0) {
        hours_ = 0;
        minutes_ = 0;
    }
}