#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include <iterator>
#include <list>

#include "my_time.h"
#include "table.h"

class Club {

private:
    struct ClientInfo {
        int tableId;
        bool inQueue;
        std::list<std::string>::iterator iteratorQueue;

        ClientInfo(int tableId = -1, bool inQueue = false) : tableId(tableId), inQueue(inQueue) { }
        ClientInfo(int tableId, bool inQueue, std::list<std::string>::iterator iteratorQueue)
         : tableId(tableId), inQueue(inQueue), iteratorQueue(iteratorQueue) { }
    };

private:
    int numberFreeTables_;
    Time openTime_;
    Time closeTime_;
    

    std::vector<Table> tables_;
    std::list<std::string> waitingQueue_;
    std::unordered_map<std::string, ClientInfo> clients_;

    std::vector<std::string> events_;

public:
    Club(int numberTables, const std::string& openTime, const std::string& closeTime, int costPerHour);

    void ClientComes(const std::string& client, const std::string& strTime);
    void ClientSitsDownAtTable(const std::string& client, const std::string& strTime, int tableId);
    void ClientWaits(const std::string& client, const std::string& strTime);
    void ClientLeaves(const std::string& client, const std::string& strTime);

    void CloseClub();
    void PrintReport();
    
private:
    bool HasFreeTable() const;

    bool DeleteClientFromQueue(const std::string& client);
    int DeleteClientFromTables(const std::string& client, const std::string& strTime);
    void AddClientToTable(const std::string& client, const std::string& strTime, int tableId);

    void ClientNeedsToLeave(const std::string& client, const std::string& strTime);
};