#pragma once


enum Sandwhich { SALMON, EGG, CUCUMBER, BEEF, SANDWHICH_EMPTY };

enum Dessert { ECLAIR, MACARON, TART, SCONE, DESSERT_EMPTY };

enum Tea { EARLGREYTEA, ASSAMTEA, GREENTEA, CHAMOMILETEA, TEA_EMPTY };

class KitchenData {

public:

	static KitchenData* GetInstance() {

		if (instance == nullptr) {
			instance = new KitchenData();
		}
		return instance;
	}

	void clearPlate() {

		sandwhichChoice = SANDWHICH_EMPTY;
		dessertChoice = DESSERT_EMPTY;
		teaChoice = TEA_EMPTY;

	}

	void setSandwhich(Sandwhich choice) { sandwhichChoice = choice; }
	void setDessert(Dessert choice) { dessertChoice = choice; }
	void setTea(Tea choice) { teaChoice = choice; }

	Sandwhich getSandwhich() { return sandwhichChoice; }
	Tea getTea() { return teaChoice; }
	Dessert getDessert() { return dessertChoice; }

	bool checkCompletePlate() { //RETURNS TRUE IF 3 CATEGORIES ON PLATE

		if ((sandwhichChoice != SANDWHICH_EMPTY) && (teaChoice != TEA_EMPTY) && (dessertChoice != DESSERT_EMPTY)) {
			return true;
		}
		return false;
	}

private:

	static KitchenData* instance;

	KitchenData() {

		sandwhichChoice = SANDWHICH_EMPTY;
		dessertChoice = DESSERT_EMPTY;
		teaChoice = TEA_EMPTY;

	}

	Sandwhich sandwhichChoice;
	Dessert dessertChoice;
	Tea teaChoice;

};

KitchenData* KitchenData::instance = nullptr;