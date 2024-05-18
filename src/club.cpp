#include "club.h"

Club::Club(int numberTables, const std::string& openTime, const std::string& closeTime, int costPerHour)
    : numberFreeTables_(numberTables), openTime_(openTime), closeTime_(closeTime), 
    tables_(numberTables, costPerHour) { }

void Club::ClientComes(const std::string& client, const std::string& strTime) {
    events_.push_back(strTime + " 1 " + client);

    Time time(strTime);
    if (time < openTime_ || time >= closeTime_) {
        events_.push_back(strTime + " 13 " + "NotOpenYet");
        return;
    }

    if (clients_.contains(client)) {
        events_.push_back(strTime + " 13 " + "YouShallNotPass");
    } else {
        clients_[client] = ClientInfo(-1);
    }
}

void Club::ClientSitsDownAtTable(const std::string& client, const std::string& strTime, int tableId) {
    events_.push_back(strTime + " 2 " + client + " " + std::to_string(tableId));
    --tableId;

    if (clients_.contains(client)) {
        if(tables_.at(tableId).IsFree()) {
            DeleteClientFromQueue(client);

            DeleteClientFromTables(client, strTime);
            
            AddClientToTable(client, strTime, tableId);
        } else {
            events_.push_back(strTime + " 13 " + "PlaceIsBusy");
        }
    } else {
        events_.push_back(strTime + " 13 " + "ClientUnknown");
    }
}

void Club::ClientWaits(const std::string& client, const std::string& strTime) { //add client?
    events_.push_back(strTime + " 3 " + client);

    if (HasFreeTable()) {
        events_.push_back(strTime + " 13 " + "ICanWaitNoLonger");
    } 
    if (waitingQueue_.size() >= tables_.size()) {
        ClientNeedsToLeave(client, strTime);
    } else {
        waitingQueue_.push_back(client);
        clients_[client] = ClientInfo(-1, true, --waitingQueue_.end());
    }
}

void Club::ClientLeaves(const std::string& client, const std::string& strTime) {
    events_.push_back(strTime + " 4 " + client);

    if (clients_.contains(client)) {
        int tableId = DeleteClientFromTables(client, strTime);
        DeleteClientFromQueue(client);
        clients_.erase(client);

        if (!waitingQueue_.empty() && tableId != -1) {
            events_.push_back(strTime + " 12 " + waitingQueue_.front() + " " 
             + std::to_string(tableId + 1));

            AddClientToTable(waitingQueue_.front(), strTime, tableId);

            DeleteClientFromQueue(waitingQueue_.front());
        }
    } else {
        events_.push_back(strTime + " 13 " + "ClientUnknown");
    }
}

void Club::CloseClub() {
    std::set<std::string> setClients;
    for (const auto& [clientName, clientInfo]: clients_) {
        setClients.insert(clientName);
    }
    for (const auto& client: setClients) {
        std::string strTime = closeTime_.toString();
        ClientNeedsToLeave(client, strTime);
    }
}

void Club::PrintReport() {
    std::cout << openTime_ << std::endl;
    for (const auto& event : events_) {
        std::cout << event << std::endl;
    }
    std::cout << closeTime_ << std::endl;

    for (int i = 0; i < tables_.size(); ++i) {
        std::cout << i + 1 << " " << tables_[i].GetIncome() << " "
            << tables_[i].GetWorkTime() << std::endl;
    }
}

bool Club::HasFreeTable() const {
    return numberFreeTables_;
}

bool Club::DeleteClientFromQueue(const std::string& client) {
    if (clients_[client].inQueue) {
        waitingQueue_.erase(clients_[client].iteratorQueue);
        clients_[client].inQueue = false;
        return true;
    }
    return false;
}

int Club::DeleteClientFromTables(const std::string& client, const std::string& strTime) {
    int tableId = clients_[client].tableId;
    if (tableId != -1) {
        if (tables_.at(tableId).DeleteClient(strTime)) {
            clients_[client].tableId = -1;
            ++numberFreeTables_;
            return tableId;
        }      
        return -1;
    }
    return -1;
}

void Club::AddClientToTable(const std::string& client, const std::string& strTime, int tableId) {
    if (tables_.at(tableId).AddClient(client, strTime)) {
        clients_[client].tableId = tableId;
        --numberFreeTables_;
    }
}

void Club::ClientNeedsToLeave(const std::string& client, const std::string& strTime) {
    events_.push_back(strTime + " 11 " + client);

    if (clients_.contains(client)) {
        DeleteClientFromTables(client, strTime);
        DeleteClientFromQueue(client);
    }
    clients_.erase(client);
}