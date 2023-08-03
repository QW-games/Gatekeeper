#include "ChooseState.h"
#include "Game.h"
#include "GameData.h"
#include "InputManager.h"
#include "Sprite.h"
#include "StageState2.h"
#include "Text.h"
#include "Camera.h"
#include "StageState.h"
#include "AnalysisState.h"
#include "TitleState.h"
#include "Vec2.h"

SDL_Color colorsChoose[4] = {
        { 0, 0, 0, 0 },
        { 124, 124, 255, 0 },
        { 255, 124, 124, 0 },
        { 124, 255, 124, 0 }
    };
int maxPhase;

ChooseState::~ChooseState() {
    objectArray.clear();
}

ChooseState::ChooseState() {
	std::ifstream in ("save.txt");
	char c;
	in >> c;
	maxPhase = c - '0';
	if(maxPhase > 3)
		maxPhase = 3;

	Vec2 windowSize = Game::GetInstance().GetWindowSize();
	quitRequested = false;
	backgroundMusic.Stop(1000);

    GameObject* background = new GameObject();
	Sprite *yellowBackground = new Sprite(*background, "assets/img/fundo_cidade.png");
	background->box = Rect(0, windowSize.y * .166, yellowBackground->GetWidth(), yellowBackground->GetHeight());
	background->AddComponent(yellowBackground);
	objectArray.emplace_back(background);

	GameObject* gofont = new GameObject();
	gofont->box = Rect(0, 0, 0, 0);
	Text* text = new Text(*gofont, "assets/font/Roboto-Regular.ttf", 200, Text::TextStyle::BLENDED, "1", SDL_Color{ 0,0,0,0 });
	gofont->AddComponent(text);
	gofont->box.SetCentro(windowSize.x * .273, windowSize.y * .5);
	objectArray.emplace_back(gofont);

	GameObject* gofont2 = new GameObject();
	gofont2->box = Rect(0, 0, 0, 0);
	Text* text2 = new Text(*gofont2, "assets/font/Roboto-Regular.ttf", 200, Text::TextStyle::BLENDED, "2", SDL_Color{ 0,0,0,0 });
	gofont2->AddComponent(text2);
	gofont2->box.SetCentro(windowSize.x * .500, windowSize.y * .5);
	objectArray.emplace_back(gofont2);

	GameObject* gofont3 = new GameObject();
	gofont3->box = Rect(0, 0, 0, 0);
	Text* text3 = new Text(*gofont3, "assets/font/Roboto-Regular.ttf", 200, Text::TextStyle::BLENDED, "3", SDL_Color{ 0,0,0,0 });
	gofont3->AddComponent(text3);
	gofont3->box.SetCentro(windowSize.x * .727, windowSize.y * .5);
	objectArray.emplace_back(gofont3);

	GameObject* panels = new GameObject();
	Sprite* panelsprite = new Sprite(*panels, "assets/img/janelinha.png");
	panelsprite->SetScaleX(windowSize.x/1920.0, windowSize.y/1080);
	panels->box = Rect(0, 0, panelsprite->GetWidth(), panelsprite->GetHeight());
	panels->box.SetCentro(windowSize.x * .273, windowSize.y * .5);
	panels->AddComponent(panelsprite);
	objectArray.emplace_back(panels);

	GameObject* panels2 = new GameObject();
	Sprite* panelsprite2 = new Sprite(*panels2, "assets/img/janelinha.png");
	panelsprite2->SetScaleX(windowSize.x/1920.0, windowSize.y/1080);
	panels2->box = Rect(0, 0, panelsprite2->GetWidth(), panelsprite2->GetHeight());
	panels2->box.SetCentro(windowSize.x * .5, windowSize.y * .5);
	panels2->AddComponent(panelsprite2);
	objectArray.emplace_back(panels2);

	GameObject* panels3 = new GameObject();
	Sprite* panelsprite3 = new Sprite(*panels3, "assets/img/janelinha.png");
	panelsprite3->SetScaleX(windowSize.x/1920.0, windowSize.y/1080);
	panels3->box = Rect(0, 0, panelsprite3->GetWidth(), panelsprite3->GetHeight());
	panels3->box.SetCentro(windowSize.x * .727, windowSize.y * .5);
	panels3->AddComponent(panelsprite3);
	objectArray.emplace_back(panels3);

	GameObject* foreground = new GameObject();
	Sprite* fgsprite = new Sprite(*foreground, "assets/img/selectstage.png");
	foreground->box = Rect(0, 0, fgsprite->GetWidth(), fgsprite->GetHeight());
	foreground->AddComponent(fgsprite);
	objectArray.emplace_back(foreground);

	GameObject* goBack = new GameObject();
	goBack->box = Rect(0, 0, 0, 0);
	Text* textBack = new Text(*goBack, "assets/font/Roboto-Regular.ttf", 60, Text::TextStyle::BLENDED, "VOLTAR", colorsChoose[0]);
	goBack->AddComponent(textBack);
	goBack->box.SetCentro(windowSize.x * .9, windowSize.y * .92);
	objectArray.emplace_back(goBack);
	
	backgroundMusic = Music("assets/audio/menu_song.mp3");
}

void ChooseState::Update(float dt) {
	// backgroundMusic.Stop(1000);
	Vec2 windowSize = Game::GetInstance().GetWindowSize();
    quitRequested = false;
	int mouseX = InputManager::GetInstance().GetMouseX() + Camera::pos.x;
	int mouseY = InputManager::GetInstance().GetMouseY() + Camera::pos.y;

	bool window1 = ((mouseX >= windowSize.x * .195) && (mouseX <= windowSize.x * .351) &&
					(mouseY >= windowSize.y * .305) && (mouseY <= windowSize.y * .694));
	bool window2 = ((mouseX >= windowSize.x * .423) && (mouseX <= windowSize.x * .579) &&
					(mouseY >= windowSize.y * .305) && (mouseY <= windowSize.y * .694));
	bool window3 = ((mouseX >= windowSize.x * .648) && (mouseX <= windowSize.x * .806) &&
					(mouseY >= windowSize.y * .305) && (mouseY <= windowSize.y * .694));

	// Fase 1
	if (window1){ 
		if(objectArray[4]->box.y >= windowSize.y * .01) {
			objectArray[4]->box.y -= 8;
		}
		if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
			AnalysisState* analysisState = new AnalysisState(1);
			Game::GetInstance().Push(analysisState);
		}
	}
	// Fase 2
	else if (window2 && maxPhase >= 2) {
		if(objectArray[5]->box.y >= windowSize.y * .01) {
			objectArray[5]->box.y -= 8;
		}
		if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
			AnalysisState* analysisState = new AnalysisState(2);
			Game::GetInstance().Push(analysisState);
		}
    }
	// Fase 3
	else if (window3 && maxPhase >= 3) {
		if(objectArray[6]->box.y >= windowSize.y * .01) {
			objectArray[6]->box.y -= 8;
		}
		if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
			AnalysisState* analysisState = new AnalysisState(3);
			Game::GetInstance().Push(analysisState);
		}
    }

	if(!window1)
		if(objectArray[4]->box.y <= windowSize.y * .298)
			objectArray[4]->box.y += 8;
	
	if(!window2)
		if(objectArray[5]->box.y <= windowSize.y * .298)
			objectArray[5]->box.y += 8;
	
	if(!window3)
		if(objectArray[6]->box.y <= windowSize.y * .298)
			objectArray[6]->box.y += 8;

	if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) &&
		((mouseX >= windowSize.x * .846) && (mouseX <= windowSize.x * .955) &&
		(mouseY >= windowSize.y * .898) && (mouseY <= windowSize.y * .937)))
			popRequested = true;

	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}

	for(unsigned int i = 0; i < objectArray.size(); i++) {
		if(objectArray[i]->GetComponent("Text")) {
			if(objectArray[i]->box.Contains(mouseX, mouseY)) {
				Text* text = (Text*)objectArray[i]->GetComponent("Text");
				if (text != nullptr)
					text->SetColor(colorsChoose[3]);
			} else {
				Text* text = (Text*)objectArray[i]->GetComponent("Text");
				if (text != nullptr)
					text->SetColor(colorsChoose[0]);
			}
		}
	}
}

void ChooseState::Render() {
	RenderArray();
}

void ChooseState::LoadAssets(){}

void ChooseState::Start() {
}

void ChooseState::Pause() {
	backgroundMusic.Stop(0);
}

void ChooseState::Resume() {}