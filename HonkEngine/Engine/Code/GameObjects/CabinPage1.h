#pragma once

#include "Page.h"

class CabinPage1 : public Page {

public:

	CabinPage1() :Page() {

		// LEFT PAGE
		GameObject* P1Picture = new UIObject("P1Picture", "Assets/Images/Journal/Passenger_Picture_Martha.png", true);
		P1Picture->SetScale(glm::vec3(5.50f, 3.19f, 0.0f));
		P1Picture->SetPosition(glm::vec3(-3.1f, 1.65f, 0.0f));

		GameObject* PaperClip = new UIObject("PaperClip", "Assets/Images/Journal/PaperClip.png", true);
		PaperClip->SetScale(glm::vec3(0.51f, 0.92f, 0.0f));
		PaperClip->SetPosition(glm::vec3(-4.0f, 3.31f, 0.0f));

		GameObject* InfoPaper = new UIObject("InfoPaper", "Assets/Images/Journal/Passenger_InfoPaper.png", true);
		InfoPaper->SetScale(glm::vec3(5.41f, 3.30f, 0.0f));
		InfoPaper->SetPosition(glm::vec3(-3.1f, -1.7f, 0.0f));

		Text* Name = new Text("Name", "Mrs. Martha Longbow", "Assets/Fonts/JMH.ttf");
		Name->SetPosition(glm::vec3(-5.3f, -0.75f, 0.0f));
		Name->SetColor(glm::vec3(0, 0, 0));
		Name->SetScale(0.6f);

		Text* Age = new Text("Age", "Age: 75", "Assets/Fonts/JMH.ttf");
		Age->SetPosition(glm::vec3(-5.3f, -1.25f, 0.0f));
		Age->SetColor(glm::vec3(0, 0, 0));
		Age->SetScale(0.47f);

		Text* Citizen = new Text("Citizen", "Citizen: Eastside", "Assets/Fonts/JMH.ttf");
		Citizen->SetPosition(glm::vec3(-5.3f, -1.65f, 0.0f));
		Citizen->SetColor(glm::vec3(0, 0, 0));
		Citizen->SetScale(0.47f);

		Text* Occupation = new Text("Occupation", "Occupation: Retired", "Assets/Fonts/JMH.ttf");
		Occupation->SetPosition(glm::vec3(-5.3f, -2.05f, 0.0f));
		Occupation->SetColor(glm::vec3(0, 0, 0));
		Occupation->SetScale(0.47f);

		GameObject* CabinStamp = new UIObject("CabinStamp", "Assets/Images/Journal/CabinStamp_1.png", true);
		CabinStamp->SetScale(glm::vec3(2.07f, 1.11f, 0.0f));
		CabinStamp->SetPosition(glm::vec3(-1.6f, -2.6f, 0.0f));


		// RIGHT PAGE
		// CLUES	[M = Martha, C = Clue]	

		Text* M_C1 = new Text("M_C1", "First time visiting Westside", "Assets/Fonts/ESA-m.ttf");
		M_C1->SetPosition(glm::vec3(0.9f, 2.7f, 0.0f));
		M_C1->SetColor(glm::vec3(0, 0, 0));
		M_C1->SetScale(0.6f);

		Text* M_C2 = new Text("M_C2", "Injury at right leg", "Assets/Fonts/ESA-smb.ttf");
		M_C2->SetPosition(glm::vec3(0.9f, 2.2f, 0.0f));
		M_C2->SetColor(glm::vec3(0, 0, 0));
		M_C2->SetScale(0.6f);

		Text* M_C3 = new Text("M_C3", "Severe domestic violence accident", "Assets/Fonts/ESA-m.ttf");
		M_C3->SetPosition(glm::vec3(0.9f, 1.7f, 0.0f));
		M_C3->SetColor(glm::vec3(0, 0, 0));
		M_C3->SetScale(0.6f);

		Text* M_C4 = new Text("M_C4", "Westside pen-pal friend", "Assets/Fonts/ESA-m.ttf");
		M_C4->SetPosition(glm::vec3(0.9f, 1.2f, 0.0f));
		M_C4->SetColor(glm::vec3(0.5, 0, 0));
		M_C4->SetScale(0.65f);

		ClueData* cabin1_clue1 = new ClueData();
		cabin1_clue1->showText = false;
		cabin1_clue1->clueText = M_C1;

		ClueData* cabin1_clue2 = new ClueData();
		cabin1_clue2->showText = false;
		cabin1_clue2->clueText = M_C2;

		ClueData* cabin1_clue3 = new ClueData();
		cabin1_clue3->showText = false;
		cabin1_clue3->clueText = M_C3;

		ClueData* cabin1_clue4 = new ClueData();
		cabin1_clue4->showText = false;
		cabin1_clue4->clueText = M_C4;
		cabin1_clue4->isEvidence = true;

		//	DIVIDER 1
		GameObject* Divider1 = new UIObject("Divider1", "Assets/Images/Journal/Line_1.png", true);
		Divider1->SetScale(glm::vec3(4.78f, 0.08f, 0.0f));
		Divider1->SetPosition(glm::vec3(3.2f, 0.7f, 0.0f));


		// LAST ACTIVITY	[M = Martha, LA = Last Activity]
		Text* LastActivity = new Text("LastActivity", "Last Activity", "Assets/Fonts/mvboli.ttf");
		LastActivity->SetPosition(glm::vec3(0.8f, 0.1f, 0.0f));
		LastActivity->SetColor(glm::vec3(0, 0, 0));
		LastActivity->SetScale(0.85f);

		// LAST ACTIVITY 1
		Text* M_LA1 = new Text("M_LA1", "Exchange letters with someone on Westside", "Assets/Fonts/ESA-smb.ttf");
		M_LA1->SetPosition(glm::vec3(0.85f, -0.4f, 0.0f));
		M_LA1->SetColor(glm::vec3(0.5, 0, 0));
		M_LA1->SetScale(0.6f);

		// LAST ACTIVITY 2
		Text* M_LA2 = new Text("M_LA2", "Hire someone to send the letter", "Assets/Fonts/ESA-m.ttf");
		M_LA2->SetPosition(glm::vec3(2.4f, -0.8f, 0.0f));
		M_LA2->SetColor(glm::vec3(0, 0, 0));
		M_LA2->SetScale(0.54f);

		ClueData* cabin1_clue5 = new ClueData();
		cabin1_clue5->showText = false;
		cabin1_clue5->clueText = M_LA1;
		cabin1_clue5->isEvidence = true;

		ClueData* cabin1_clue6 = new ClueData();
		cabin1_clue6->showText = false;
		cabin1_clue6->clueText = M_LA2;

		textClues.push_back(cabin1_clue1);
		textClues.push_back(cabin1_clue2);
		textClues.push_back(cabin1_clue3);
		textClues.push_back(cabin1_clue4);

		textClues.push_back(cabin1_clue5);
		textClues.push_back(cabin1_clue6);

		m_journalData->addClueToJournalData(CABIN1, cabin1_clue1);
		m_journalData->addClueToJournalData(CABIN1, cabin1_clue2);
		m_journalData->addClueToJournalData(CABIN1, cabin1_clue3);
		m_journalData->addClueToJournalData(CABIN1, cabin1_clue4);

		m_journalData->addClueToJournalData(CABIN1, cabin1_clue5);
		m_journalData->addClueToJournalData(CABIN1, cabin1_clue6);

		
		// DIVIDER 2
		GameObject* Divider2 = new UIObject("Divider2", "Assets/Images/Journal/Line_2.png", true);
		Divider2->SetScale(glm::vec3(4.8f, 0.06f, 0.0f));
		Divider2->SetPosition(glm::vec3(3.2f, -1.25f, 0.0f));


		// LAST VISIT
		Text* LastVisit = new Text("LastVisit", "Last Visit", "Assets/Fonts/mvboli.ttf");
		LastVisit->SetPosition(glm::vec3(0.8f, -1.95f, 0.0f));
		LastVisit->SetColor(glm::vec3(0, 0, 0));
		LastVisit->SetScale(0.85f);

		Text* TownSquare = new Text("TownSquare", "Town Square", "Assets/Fonts/ESA-m.ttf");
		TownSquare->SetPosition(glm::vec3(0.8f, -2.45f, 0.0f));
		TownSquare->SetColor(glm::vec3(0, 0, 0));
		TownSquare->SetScale(0.6f);

		Text* TheHolyChurch = new Text("TheHolyChurch", "The Holy Church", "Assets/Fonts/ESA-m.ttf");
		TheHolyChurch->SetPosition(glm::vec3(2.9f, -2.45f, 0.0f));
		TheHolyChurch->SetColor(glm::vec3(0, 0, 0));
		TheHolyChurch->SetScale(0.6f);

		Text* TheCouncil = new Text("TheCouncil", "The Council", "Assets/Fonts/ESA-m.ttf");
		TheCouncil->SetPosition(glm::vec3(0.8f, -2.95f, 0.0f));
		TheCouncil->SetColor(glm::vec3(0, 0, 0));
		TheCouncil->SetScale(0.6f);

		Text* SupremeCourt = new Text("SupremeCourt", "Supreme Court", "Assets/Fonts/ESA-m.ttf");
		SupremeCourt->SetPosition(glm::vec3(2.9f, -2.95f, 0.0f));
		SupremeCourt->SetColor(glm::vec3(0, 0, 0));
		SupremeCourt->SetScale(0.6f);

		RedUnderline_Cabin1 = new UIObject("UnderlineCabin1", "Assets/Images/Journal/CaseSummary_Icon_Red_Underline.png", true);
		RedUnderline_Cabin1->setActiveStatus(false);
		RedUnderline_Cabin1->SetScale(glm::vec3(1.7f, 0.1f, 0.0f));
		RedUnderline_Cabin1->SetPosition(glm::vec3(1.1f, -2.0f, 0.0f));

		m_gameObjects.push_back(P1Picture);
		m_gameObjects.push_back(PaperClip);
		m_gameObjects.push_back(InfoPaper);

		m_gameObjects.push_back(Name);
		m_gameObjects.push_back(Age);
		m_gameObjects.push_back(Citizen);
		m_gameObjects.push_back(Occupation);
		m_gameObjects.push_back(CabinStamp);

		m_gameObjects.push_back(Divider1);

		m_gameObjects.push_back(LastActivity);

		m_gameObjects.push_back(LastVisit);
		m_gameObjects.push_back(Divider2);

		m_gameObjects.push_back(TownSquare);
		m_gameObjects.push_back(TheHolyChurch);
		m_gameObjects.push_back(TheCouncil);
		m_gameObjects.push_back(SupremeCourt);

		m_gameObjects.push_back(RedUnderline_Cabin1);

	}

	virtual void Update(float dt, long frame) override {

		Page::Update(dt, frame);

		CabinPageData cabinData = m_journalData->GetCabinPageData(Cabin::CABIN1);

		if (!cabinData.ShowLastActivity) {

			RedUnderline_Cabin1->setActiveStatus(false);

		}
		else {

			RedUnderline_Cabin1->setActiveStatus(true);
		
		}

	}


private:

	UIObject* RedUnderline_Cabin1;

};