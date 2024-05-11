#pragma once

#include "../Scene/KitchenData.h"
#include "JournalData.h"
#include "Timer.h"

#include <map>

enum InteractionLevel { LOW, AVERAGE, INFORMATIVE };
enum PrepTime { ONTIME, LATE };

struct characterFoodScores {

	std::map<Sandwich, int> SandwichScores;
	std::map<Tea, int> TeaScores;
	std::map<Dessert, int> DessertScores;
	std::map<Tea, int> TeaMilkScores;

};

class CharacterData {

public:

	static CharacterData* GetInstance() {

		static CharacterData instance;
		return &instance;

	}

	//get score based on food choices

	int calculateTimeScore() { //NO MEAL SCORE JUST TIME TO SERVE

		int remainingTime = Timer::GetInstance().getRemainingTime();

		if (remainingTime == 0) {
			return -2;
		}
		return 0;
	}


	int calculateScore(Cabin cabin) { //with meal score and timer

		int totalScore;

		characterFoodScores currentCabin = allCharacterData[cabin];

		int dessertScore = currentCabin.DessertScores[kitchen_instance->getDessert()];
		int sandwichScore = currentCabin.SandwichScores[kitchen_instance->getSandwich()];

		int teaScore;

		if (kitchen_instance->getOptional() == MILK) {
			teaScore = currentCabin.TeaMilkScores[kitchen_instance->getTea()];
		}
		else {
			teaScore = currentCabin.TeaScores[kitchen_instance->getTea()];
		}

		totalScore = dessertScore + sandwichScore + teaScore;

		return totalScore;

	}

	//GET INTERACTION LEVEL FUNCTIONS

	PrepTime getStage1InteractionLevel(Cabin cabin) { //STAGE 1

		if (calculateStage1Score() == 0) {
			return PrepTime::ONTIME;
		}

		return PrepTime::LATE;

	}

	InteractionLevel getStage2InteractionLevel(Cabin cabin) { // STAGE 2

		int score = calculateScore(cabin);

		if (score >= 0 && score <= 3) { return LOW; }
		else if (score >= 4 && score <= 7) { return AVERAGE; }
		else { return INFORMATIVE; }

	}

	InteractionLevel getStage3InteractionLevel(Cabin cabin) { // STAGE 3

		int score = calculateScore(cabin) + calculateStage1Score();

		if (score >= 0 && score <= 3) { return LOW; }
		else if (score >= 4 && score <= 7) { return AVERAGE; }
		else { return INFORMATIVE; }

	}



private:

	CharacterData() {

		//--------------------CABIN 1 - MARTHA - FOOD SCORES--------------------

		characterFoodScores cabin1Scores;

		cabin1Scores.SandwichScores[Sandwich::SALMON] = 1;
		cabin1Scores.SandwichScores[Sandwich::EGG] = 1;
		cabin1Scores.SandwichScores[Sandwich::CUCUMBER] = 0;
		cabin1Scores.SandwichScores[Sandwich::BEEF] = 3;

		cabin1Scores.TeaScores[Tea::EARLGREYTEA] = 0;
		cabin1Scores.TeaScores[Tea::CHAMOMILETEA] = 2;
		cabin1Scores.TeaScores[Tea::ASSAMTEA] = 0;
		cabin1Scores.TeaScores[Tea::GREENTEA] = 2;

		cabin1Scores.DessertScores[Dessert::ECLAIR] = 3;
		cabin1Scores.DessertScores[Dessert::MACARON] = 3;
		cabin1Scores.DessertScores[Dessert::TART] = 1;
		cabin1Scores.DessertScores[Dessert::SCONE] = 1;

		cabin1Scores.TeaMilkScores[Tea::EARLGREYTEA] = 2;
		cabin1Scores.TeaMilkScores[Tea::CHAMOMILETEA] = 2;
		cabin1Scores.TeaMilkScores[Tea::ASSAMTEA] = 4;
		cabin1Scores.TeaMilkScores[Tea::GREENTEA] = 2;

		//--------------------CABIN 2-1  - NATHANIEL - FOOD SCORES--------------------

		characterFoodScores cabin21Scores;

		cabin21Scores.SandwichScores[Sandwich::SALMON] = 1;
		cabin21Scores.SandwichScores[Sandwich::EGG] = 1;
		cabin21Scores.SandwichScores[Sandwich::CUCUMBER] = 0;
		cabin21Scores.SandwichScores[Sandwich::BEEF] = 3;

		cabin21Scores.TeaScores[Tea::EARLGREYTEA] = 0;
		cabin21Scores.TeaScores[Tea::CHAMOMILETEA] = 2;
		cabin21Scores.TeaScores[Tea::ASSAMTEA] = 0;
		cabin21Scores.TeaScores[Tea::GREENTEA] = 2;

		cabin21Scores.DessertScores[Dessert::ECLAIR] = 3;
		cabin21Scores.DessertScores[Dessert::MACARON] = 3;
		cabin21Scores.DessertScores[Dessert::TART] = 1;
		cabin21Scores.DessertScores[Dessert::SCONE] = 1;

		cabin21Scores.TeaMilkScores[Tea::EARLGREYTEA] = 2;
		cabin21Scores.TeaMilkScores[Tea::CHAMOMILETEA] = 2;
		cabin21Scores.TeaMilkScores[Tea::ASSAMTEA] = 4;
		cabin21Scores.TeaMilkScores[Tea::GREENTEA] = 4;

		//--------------------CABIN 2-2  - EVELYN - FOOD SCORES--------------------

		characterFoodScores cabin22Scores;

		cabin22Scores.SandwichScores[Sandwich::SALMON] = 0;
		cabin22Scores.SandwichScores[Sandwich::EGG] = 1;
		cabin22Scores.SandwichScores[Sandwich::CUCUMBER] = 0;
		cabin22Scores.SandwichScores[Sandwich::BEEF] = 0;

		cabin22Scores.TeaScores[Tea::EARLGREYTEA] = 0;
		cabin22Scores.TeaScores[Tea::CHAMOMILETEA] = 0;
		cabin22Scores.TeaScores[Tea::ASSAMTEA] = 4;
		cabin22Scores.TeaScores[Tea::GREENTEA] = 4;

		cabin22Scores.DessertScores[Dessert::ECLAIR] = 1;
		cabin22Scores.DessertScores[Dessert::MACARON] = 1;
		cabin22Scores.DessertScores[Dessert::TART] = 1;
		cabin22Scores.DessertScores[Dessert::SCONE] = 3;

		cabin22Scores.TeaMilkScores[Tea::EARLGREYTEA] = 0;
		cabin22Scores.TeaMilkScores[Tea::CHAMOMILETEA] = 0;
		cabin22Scores.TeaMilkScores[Tea::ASSAMTEA] = 2;
		cabin22Scores.TeaMilkScores[Tea::GREENTEA] = 2;

		//--------------------CABIN 3  - ARCHIBALD - FOOD SCORES--------------------

		characterFoodScores cabin3Scores;

		cabin3Scores.SandwichScores[Sandwich::SALMON] = 3;
		cabin3Scores.SandwichScores[Sandwich::CUCUMBER] = 1;
		cabin3Scores.SandwichScores[Sandwich::EGG] = 0;
		cabin3Scores.SandwichScores[Sandwich::BEEF] = 0;

		cabin3Scores.TeaScores[Tea::EARLGREYTEA] = 2;
		cabin3Scores.TeaScores[Tea::CHAMOMILETEA] = 0;
		cabin3Scores.TeaScores[Tea::ASSAMTEA] = 4;
		cabin3Scores.TeaScores[Tea::GREENTEA] = 0;

		cabin3Scores.DessertScores[Dessert::ECLAIR] = 0;
		cabin3Scores.DessertScores[Dessert::MACARON] = 0;
		cabin3Scores.DessertScores[Dessert::TART] = 3;
		cabin3Scores.DessertScores[Dessert::SCONE] = 1;

		cabin3Scores.TeaMilkScores[Tea::EARLGREYTEA] = 0;
		cabin3Scores.TeaMilkScores[Tea::CHAMOMILETEA] = 0;
		cabin3Scores.TeaMilkScores[Tea::ASSAMTEA] = 2;
		cabin3Scores.TeaMilkScores[Tea::GREENTEA] = 0;

		//--------------------CABIN 4 - OCTAVIA - FOOD SCORES--------------------

		characterFoodScores cabin4Scores;

		cabin4Scores.SandwichScores[Sandwich::SALMON] = 0;
		cabin4Scores.SandwichScores[Sandwich::CUCUMBER] = 3;
		cabin4Scores.SandwichScores[Sandwich::EGG] = 1;
		cabin4Scores.SandwichScores[Sandwich::BEEF] = 0;

		cabin4Scores.TeaScores[Tea::EARLGREYTEA] = 0;
		cabin4Scores.TeaScores[Tea::CHAMOMILETEA] = 2;
		cabin4Scores.TeaScores[Tea::ASSAMTEA] = 0;
		cabin4Scores.TeaScores[Tea::GREENTEA] = 4;

		cabin4Scores.DessertScores[Dessert::ECLAIR] = 0;
		cabin4Scores.DessertScores[Dessert::MACARON] = 0;
		cabin4Scores.DessertScores[Dessert::TART] = 3;
		cabin4Scores.DessertScores[Dessert::SCONE] = 1;

		cabin4Scores.TeaMilkScores[Tea::EARLGREYTEA] = 0;
		cabin4Scores.TeaMilkScores[Tea::CHAMOMILETEA] = 0;
		cabin4Scores.TeaMilkScores[Tea::ASSAMTEA] = 0;
		cabin4Scores.TeaMilkScores[Tea::GREENTEA] = 0;

		allCharacterData.push_back(cabin1Scores);
		allCharacterData.push_back(cabin21Scores);
		allCharacterData.push_back(cabin22Scores);
		allCharacterData.push_back(cabin3Scores);
		allCharacterData.push_back(cabin4Scores);

	}


	CharacterData(const CharacterData&) = delete;
	CharacterData& operator=(const CharacterData&) = delete;

	std::vector<characterFoodScores> allCharacterData;

	KitchenData* kitchen_instance = KitchenData::GetInstance();

};
