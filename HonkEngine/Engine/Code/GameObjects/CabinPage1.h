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
		Text* M_C1 = new Text("M_C1", "Family resides at Eastside", "Assets/Fonts/ESA-m.ttf");
		M_C1->SetPosition(glm::vec3(1.0f, 2.7f, 0.0f));
		M_C1->SetColor(glm::vec3(0, 0, 0));
		M_C1->SetScale(0.58f);

		Text* M_C2 = new Text("M_C2", "Injury at right leg", "Assets/Fonts/ESA-smb.ttf");
		M_C2->SetPosition(glm::vec3(0.9f, 2.1f, 0.0f));
		M_C2->SetColor(glm::vec3(0, 0, 0));
		M_C2->SetScale(0.6f);

		Text* M_C3 = new Text("M_C3", "Pen-pal friend?", "Assets/Fonts/ESA-smb.ttf");
		M_C3->SetPosition(glm::vec3(1.05f, 1.45f, 0.0f));
		M_C3->SetColor(glm::vec3(0, 0, 0));
		M_C3->SetScale(0.65f);

		Text* M_C4_1 = new Text("M_C4_1", "Severe domestic", "Assets/Fonts/ESA-m.ttf");
		M_C4_1->SetPosition(glm::vec3(3.65f, 1.9f, 0.0f));
		M_C4_1->SetColor(glm::vec3(0, 0, 0));
		M_C4_1->SetScale(0.6f);

		Text* M_C4_2 = new Text("M_C4_2", "violence accident", "Assets/Fonts/ESA-m.ttf");
		M_C4_2->SetPosition(glm::vec3(3.65f, 1.6f, 0.0f));
		M_C4_2->SetColor(glm::vec3(0, 0, 0));
		M_C4_2->SetScale(0.6f);

		GameObject* Divider1 = new UIObject("Divider1", "Assets/Images/Journal/Line_1.png", true);
		Divider1->SetScale(glm::vec3(4.71f, 0.15f, 0.0f));
		Divider1->SetPosition(glm::vec3(3.2f, 1.0f, 0.0f));


		// LAST ACTIVITY	[M = Martha, LA = Last Activity]
		Text* LastActivity = new Text("LastActivity", "Last Activity", "Assets/Fonts/mvboli.ttf");
		LastActivity->SetPosition(glm::vec3(0.8f, 0.3f, 0.0f));
		LastActivity->SetColor(glm::vec3(0, 0, 0));
		LastActivity->SetScale(0.85f);

		// LAST ACTIVITY 1
		Text* M_LA1 = new Text("M_LA1", "Received a letter", "Assets/Fonts/ESA-smb.ttf");
		M_LA1->SetPosition(glm::vec3(0.85f, -0.2f, 0.0f));
		M_LA1->SetColor(glm::vec3(0, 0, 0));
		M_LA1->SetScale(0.6f);

		Text* M_LA1_2 = new Text("M_LA1_2", "from Westside", "Assets/Fonts/ESA-smb.ttf");
		M_LA1_2->SetPosition(glm::vec3(0.85f, -0.55f, 0.0f));
		M_LA1_2->SetColor(glm::vec3(0, 0, 0));
		M_LA1_2->SetScale(0.6f);

		// LAST ACTIVITY 2
		Text* M_LA2_1 = new Text("M_LA2_1", "Hire someone to send a letter", "Assets/Fonts/ESA-m.ttf");
		M_LA2_1->SetPosition(glm::vec3(3.1f, -0.22f, 0.0f));
		M_LA2_1->SetColor(glm::vec3(0, 0, 0));
		M_LA2_1->SetScale(0.5f);

		Text* M_LA2_2 = new Text("M_LA2_2", "instead of using post service", "Assets/Fonts/ESA-m.ttf");
		M_LA2_2->SetPosition(glm::vec3(3.15f, -0.5f, 0.0f));
		M_LA2_2->SetColor(glm::vec3(0, 0, 0));
		M_LA2_2->SetScale(0.5f);


		// DIVIDER 2
		GameObject* Divider2 = new UIObject("Divider2", "Assets/Images/Journal/Line_2.png", true);
		Divider2->SetScale(glm::vec3(4.81f, 0.09f, 0.0f));
		Divider2->SetPosition(glm::vec3(3.2f, -1.0f, 0.0f));


		// LAST VISIT
		Text* LastVisit = new Text("LastVisit", "Last Visit", "Assets/Fonts/mvboli.ttf");
		LastVisit->SetPosition(glm::vec3(0.8f, -1.75f, 0.0f));
		LastVisit->SetColor(glm::vec3(0, 0, 0));
		LastVisit->SetScale(0.85f);

		Text* TownSquare = new Text("TownSquare", "Town Square", "Assets/Fonts/ESA-m.ttf");
		TownSquare->SetPosition(glm::vec3(0.8f, -2.25f, 0.0f));
		TownSquare->SetColor(glm::vec3(0, 0, 0));
		TownSquare->SetScale(0.6f);

		Text* TheHolyChurch = new Text("TheHolyChurch", "The Holy Church", "Assets/Fonts/ESA-m.ttf");
		TheHolyChurch->SetPosition(glm::vec3(2.9f, -2.25f, 0.0f));
		TheHolyChurch->SetColor(glm::vec3(0, 0, 0));
		TheHolyChurch->SetScale(0.6f);

		Text* TheCouncil = new Text("TheCouncil", "The Council", "Assets/Fonts/ESA-m.ttf");
		TheCouncil->SetPosition(glm::vec3(0.8f, -2.75f, 0.0f));
		TheCouncil->SetColor(glm::vec3(0, 0, 0));
		TheCouncil->SetScale(0.6f);

		Text* SupremeCourt = new Text("SupremeCourt", "Supreme Court", "Assets/Fonts/ESA-m.ttf");
		SupremeCourt->SetPosition(glm::vec3(2.9f, -2.75f, 0.0f));
		SupremeCourt->SetColor(glm::vec3(0, 0, 0));
		SupremeCourt->SetScale(0.6f);



		m_gameObjects.push_back(P1Picture);
		m_gameObjects.push_back(PaperClip);
		m_gameObjects.push_back(InfoPaper);

		m_gameObjects.push_back(Name);
		m_gameObjects.push_back(Age);
		m_gameObjects.push_back(Citizen);
		m_gameObjects.push_back(Occupation);
		m_gameObjects.push_back(CabinStamp);

		m_gameObjects.push_back(M_C1);
		m_gameObjects.push_back(M_C2);
		m_gameObjects.push_back(M_C3);
		m_gameObjects.push_back(M_C4_1);
		m_gameObjects.push_back(M_C4_2);
		m_gameObjects.push_back(Divider1);


		m_gameObjects.push_back(LastActivity);
		m_gameObjects.push_back(M_LA1);
		m_gameObjects.push_back(M_LA1_2);
		m_gameObjects.push_back(M_LA2_1);
		m_gameObjects.push_back(M_LA2_2);

		m_gameObjects.push_back(LastVisit);
		m_gameObjects.push_back(Divider2);

		m_gameObjects.push_back(TownSquare);
		m_gameObjects.push_back(TheHolyChurch);
		m_gameObjects.push_back(TheCouncil);
		m_gameObjects.push_back(SupremeCourt);

	}



};