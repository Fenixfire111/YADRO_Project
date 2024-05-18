#include "table.h"

Table::Table(int costPerHour) : free_(true), income_(0), costPerHour_(costPerHour) { }

bool Table::AddClient(const std::string& client, const std::string& strTime) {
    if (IsFree()) {
        lastStartTime_ = Time(strTime);
        client_ = client;
        free_ = false;
        return true;
    }
    return false;
}

bool Table::DeleteClient(const std::string& strTime) {
    if (!IsFree()) {
        Time diffTime = (Time(strTime) - lastStartTime_);
        workTime_ += diffTime;
        income_ += costPerHour_ * (diffTime.GetHours() + 1);
        free_ = true;
        return true;
    }
    return false;
}

bool Table::IsFree() const {
    return free_;
}

int Table::GetIncome() const {
    return income_;
}

std::string Table::GetClient() const {
    return client_;
}

Time Table::GetWorkTime() const {
    return workTime_;
}