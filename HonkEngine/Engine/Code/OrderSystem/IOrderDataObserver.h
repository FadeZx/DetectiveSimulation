#pragma once

class IOrderDataObserver {
public:
    virtual void OnOrderDataChanged() = 0;
    virtual ~IOrderDataObserver() {}
};
