#pragma once

#include <iostream>
#include <string>

#include "my_time.h"

class Table {

private:
    bool free_;
    int income_;
    int costPerHour_;
    Time workTime_;
    Time lastStartTime_;
    std::string client_;

public:
    Table(int costPerHour);

    bool AddClient(const std::string& client, const std::string& strTime);
    bool DeleteClient(const std::string& strTime);

    bool IsFree() const;
    int GetIncome() const;
    std::string GetClient() const;
    Time GetWorkTime() const;
};