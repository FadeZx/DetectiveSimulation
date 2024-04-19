#pragma once

#include "IOrderDataObserver.h"
#include "../Text/Text.h"
#include "OrderData.h"

class OrderUIManager : public IOrderDataObserver {
    Text* orderNoText;
    Text* teaOrderText;
    Text* sandwichOrderText;
    Text* pastryOrderText;

public:
    OrderUIManager(Text* orderNo, Text* teaOrder, Text* sandwichOrder, Text* pastryOrder)
        : orderNoText(orderNo), teaOrderText(teaOrder), sandwichOrderText(sandwichOrder), pastryOrderText(pastryOrder) {
        OrderData::GetInstance().RegisterObserver(this);
    }

    ~OrderUIManager() {
        OrderData::GetInstance().UnregisterObserver(this);
    }

    void OnOrderDataChanged() override {
        orderNoText->SetContent(OrderData::GetInstance().GetRoomNumber());
        teaOrderText->SetContent(OrderData::GetInstance().GetTeaOrder());
        sandwichOrderText->SetContent(OrderData::GetInstance().GetSandwichOrder());
        pastryOrderText->SetContent(OrderData::GetInstance().GetPastryOrder());
    }
};
