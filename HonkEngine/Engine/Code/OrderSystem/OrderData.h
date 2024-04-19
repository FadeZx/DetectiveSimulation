#pragma once
#include "IOrderDataObserver.h"
#include <vector>
#include <string>
#include <algorithm>

class OrderData {
    std::string roomNumber, teaOrder, sandwichOrder, pastryOrder;
    std::vector<IOrderDataObserver*> observers;

public:
    static OrderData& GetInstance() {
        static OrderData instance;
        return instance;
    }

    void RegisterObserver(IOrderDataObserver* observer) {
        observers.push_back(observer);
    }

    void UnregisterObserver(IOrderDataObserver* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void NotifyObservers() {
        for (IOrderDataObserver* obs : observers) {
            obs->OnOrderDataChanged();
        }
    }

    // Setters that trigger notifications
    void SetRoomNumber(const std::string& number) {
        roomNumber = number;
        NotifyObservers();
    }
    void SetTeaOrder(const std::string& tea) {
        teaOrder = tea;
        NotifyObservers();
    }
    void SetSandwichOrder(const std::string& sandwich) {
        sandwichOrder = sandwich;
        NotifyObservers();
    }
    void SetPastryOrder(const std::string& pastry) {
        pastryOrder = pastry;
        NotifyObservers();
    }

    // Getters
    std::string GetRoomNumber() const { return roomNumber; }
    std::string GetTeaOrder() const { return teaOrder; }
    std::string GetSandwichOrder() const { return sandwichOrder; }
    std::string GetPastryOrder() const { return pastryOrder; }
};
