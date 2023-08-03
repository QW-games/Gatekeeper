#include "TitleState.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Sprite.h"
#include "StageState.h"
#include "ChooseState.h"
#include "StageState2.h"
#include "analysisState.h"
#include "Camera.h"
#include "Music.h"
#include "Sound.h"
#include "Game.h"
#include "Text.h"
#include "Vec2.h"

SDL_Color colors[4] = {
        { 255, 255, 255, 0 },
        { 124, 124, 255, 0 },
        { 255, 124, 124, 0 },
        { 124, 255, 124, 0 }
    };

int maxPhaseTitle;

TitleState::TitleState(){
	ifstream f("save.txt");
	if(!f.good()) {
		std::fstream file("save.txt", std::ios::out | std::ios::in | std::ios::app);
		file << "1";
	}

	std::ifstream in ("save.txt");
	char c;
	in >> c;
	maxPhaseTitle = c - '0';
	if(maxPhaseTitle > 3)
		maxPhaseTitle = 3;

	Vec2 windowSize = Game::GetInstance().GetWindowSize();
	quitRequested = false;

    GameObject* gobgsprite = new GameObject();
    Sprite* sprite = new Sprite(*gobgsprite, "assets/img/fundo_cidade.png");
	gobgsprite->box = Rect(0, 0, sprite->GetWidth(), sprite->GetHeight());
	gobgsprite->AddComponent(sprite);
	objectArray.emplace_back(gobgsprite);

	GameObject* foreground = new GameObject();
    Sprite* fgglasssprite = new Sprite(*foreground, "assets/img/vidro.png");
	foreground->box = Rect(0, 0, fgglasssprite->GetWidth(), fgglasssprite->GetHeight());
	foreground->AddComponent(fgglasssprite);
	Sprite* fgbarsprite = new Sprite(*foreground, "assets/img/grades.png");
	foreground->box = Rect(0, 0, fgbarsprite->GetWidth(), fgbarsprite->GetHeight());
	foreground->AddComponent(fgbarsprite);
	Sprite* fgpanelsprite = new Sprite(*foreground, "assets/img/letreiro2.png");
	foreground->box = Rect(0, 0, fgpanelsprite->GetWidth(), fgpanelsprite->GetHeight());
	foreground->AddComponent(fgpanelsprite);
	objectArray.emplace_back(foreground);

	GameObject* gofont = new GameObject();
	gofont->box = Rect(0, 0, 0, 0);
	Text* text = new Text(*gofont, "assets/font/Roboto-Regular.ttf", 60, Text::TextStyle::BLENDED, "JOGAR", colors[0]);
	gofont->AddComponent(text);
	gofont->box.SetCentro(windowSize.x * .28, windowSize.y * .505);
	objectArray.emplace_back(gofont);

	GameObject* gofont2 = new GameObject();
	gofont2->box = Rect(0, 0, 0, 0);
	Text* text2 = new Text(*gofont2, "assets/font/Roboto-Regular.ttf", 60, Text::TextStyle::BLENDED, "FASES", colors[0]);
	gofont2->AddComponent(text2);
	gofont2->box.SetCentro(windowSize.x * .28, windowSize.y * .605);
	objectArray.emplace_back(gofont2);

	GameObject* gofont3 = new GameObject();
	gofont3->box = Rect(0, 0, 0, 0);
	Text* text3 = new Text(*gofont3, "assets/font/Roboto-Regular.ttf", 60, Text::TextStyle::BLENDED, "SAIR ", colors[0]);
	gofont3->AddComponent(text3);
	gofont3->box.SetCentro(windowSize.x * .27, windowSize.y * .705);
	objectArray.emplace_back(gofont3);

	backgroundMusic = new Music("assets/audio/menu_song.mp3");
	Mix_VolumeMusic(50);
	backgroundMusic->Play();
	
	timer = Timer();
	texten = true;
}
TitleState::~TitleState() {}

void TitleState::LoadAssets() {}

void TitleState::Update(float dt){
	Vec2 windowSize = Game::GetInstance().GetWindowSize();
    quitRequested = false;
	int mouseX = InputManager::GetInstance().GetMouseX() + Camera::pos.x;
	int mouseY = InputManager::GetInstance().GetMouseY() + Camera::pos.y;

	// JOGAR
	if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) &&
		((mouseX >= windowSize.x * .230) && (mouseX <= windowSize.x * .33) &&
		(mouseY >= windowSize.y * .483) && (mouseY <= windowSize.y * .53))){
		AnalysisState* analysisState = new AnalysisState(maxPhaseTitle);
		Game::GetInstance().Push(analysisState);
	}
	// FASES
	else if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) &&
		((mouseX >= windowSize.x * .230) && (mouseX <= windowSize.x * .33) &&
		(mouseY >= windowSize.y * .580) && (mouseY <= windowSize.y * .625))){
		Game::GetInstance().Push(new ChooseState());
	}
	// SAIR
	else if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested() == true ||
		(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) &&
		((mouseX >= windowSize.x * .230) && (mouseX <= windowSize.x * .304) &&
		(mouseY >= windowSize.y * .682) && (mouseY <= windowSize.y * .725)))) {
		quitRequested = true;
	}
	
	for(unsigned int i = 0; i < objectArray.size(); i++) {
		if(objectArray[i]->GetComponent("Text")) {
			if(objectArray[i]->box.Contains(mouseX, mouseY)) {
				Text* text = (Text*)objectArray[i]->GetComponent("Text");
				if (text != nullptr)
					text->SetColor(colors[3]);
			} else {
				Text* text = (Text*)objectArray[i]->GetComponent("Text");
				if (text != nullptr)
					text->SetColor(colors[0]);
			}
		}
	}
	timer.Update(dt);
}

void TitleState::Render() {
	RenderArray();
}

void TitleState::Start() {
	StartArray();
}

void TitleState::Pause() {}

void TitleState::Resume() {}