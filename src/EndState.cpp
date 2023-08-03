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

SDL_Color colorsEnd[4] = {
        { 0, 0, 0, 0 },
        { 124, 124, 255, 0 },
        { 255, 124, 124, 0 },
        { 124, 255, 124, 0 }
    };
int nextPhase;

EndState::EndState() {
	Vec2 windowSize = Game::GetInstance().GetWindowSize();

	quitRequested = false;
	if ((GameData::playerVictory == true)) {
		GameObject* bg = new GameObject();
		Sprite* sprite = new Sprite(*bg, "assets/img/vitoria.png");
		bg->box = Rect(0, 0, sprite->GetWidth(), sprite->GetHeight());
		bg->AddComponent(sprite);
		objectArray.emplace_back(bg);
		backgroundMusic = new Music("assets/audio/you_win.mp3");
		backgroundMusic->Play(1);
	} else {
		GameObject* bg = new GameObject();
		Sprite* sprite = new Sprite(*bg, "assets/img/derrota.png");
		bg->box = Rect(0, 0, sprite->GetWidth(), sprite->GetHeight());
		bg->AddComponent(sprite);
		objectArray.emplace_back(bg);
		backgroundMusic = new Music("assets/audio/you_lose.mp3");
		Mix_VolumeMusic(10);
		backgroundMusic->Play(1);
	}

	/*GameObject* goMenu = new GameObject();
	goMenu->box = Rect(0, 0, 0, 0);
	Text* textMenu = new Text(*goMenu, "assets/font/Roboto-Regular.ttf", 60, Text::TextStyle::BLENDED, "MENU", colorsEnd[0]);
	goMenu->AddComponent(textMenu);
	goMenu->box.SetCentro(windowSize.x * .85, windowSize.y * .85);
	objectArray.emplace_back(goMenu);*/
}

void EndState::Update(float dt) {
	Vec2 windowSize = Game::GetInstance().GetWindowSize();
	int mouseX = InputManager::GetInstance().GetMouseX() + Camera::pos.x;
	int mouseY = InputManager::GetInstance().GetMouseY() + Camera::pos.y;

	if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON))
		SDL_Log("mouseX: %d mouseY: %d", mouseX, mouseY);

	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}

	/*if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) &&
		((mouseX >= windowSize.x * .808) && (mouseX <= windowSize.x * .893) &&
		(mouseY >= windowSize.y * .827) && (mouseY <= windowSize.y * .869))){
			Game::GetInstance().Push(new TitleState);
		}

	for(unsigned int i = 0; i < objectArray.size(); i++) {
		if(objectArray[i]->GetComponent("Text")) {
			if(objectArray[i]->box.Contains(mouseX, mouseY)) {
				Text* text = (Text*)objectArray[i]->GetComponent("Text");
				if (text != nullptr)
					text->SetColor(colorsEnd[3]);
			} else {
				Text* text = (Text*)objectArray[i]->GetComponent("Text");
				if (text != nullptr)
					text->SetColor(colorsEnd[0]);
			}
		}
	}*/
}

void EndState::Render() {
	RenderArray();
}

void EndState::LoadAssets(){}

void EndState::Start() {
}

void EndState::Pause() {
	backgroundMusic->Stop(0);
}

void EndState::Resume() {}