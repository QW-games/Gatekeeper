#include "AnalysisState.h"
#include "ChooseState.h"
#include "State.h"
#include "Alien.h"
#include "Resources.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Collider.h"
#include "Collision.h"
#include "EndState.h"
#include "GameData.h"
#include "Text.h"
#include "StageState.h"
#include "StageState2.h"
#include "Game.h"
#include "Text.h"
#include "Text2.h"
#include "Buttons.h"
#include "Laser.h"
#include "FlightInfo.h"

int currentPhase;
int phases[3] = { 720, 630, 590 };

AnalysisState::AnalysisState(int phase) : State() {
	currentPhase = phase;
    quitRequested = false;
	started = false;
	timerText = nullptr;
	fastMusic = false;
	gameTime = Timer(INITIAL_TIME_IN_SECONDS);
}

AnalysisState::~AnalysisState() {
    objectArray.clear();
}

void AnalysisState::Render() {
	RenderArray();
}

void AnalysisState::LoadAssets(){
	FlightInfo& flightInfo = FlightInfo::GetInstance();
	Vec2 windowSize = Game::GetInstance().GetWindowSize();
	Vec2 windowScale = Vec2(windowSize.x/1920, windowSize.y/1080);

	GameObject* goBackground = new GameObject();
    Sprite* backgroundSprite = new Sprite(*goBackground, "assets/img/Fundo_1Fullscreen.png");
	goBackground->box = Rect(0, 0, backgroundSprite->GetWidth(), backgroundSprite->GetHeight());
	goBackground->AddComponent(backgroundSprite);
	objectArray.emplace_back(goBackground);

	GameObject* goGrid = new GameObject();
    Sprite* gridSprite = new Sprite(*goGrid, "assets/img/grades.png");
	goGrid->box = Rect(0, 0, gridSprite->GetWidth(), gridSprite->GetHeight());
	goGrid->AddComponent(gridSprite);
	objectArray.emplace_back(goGrid);

    GameObject* goTable = new GameObject();
    Sprite* tableSprite = new Sprite(*goTable, "assets/img/tela_c_divisao_2.png");
	goTable->box = Rect(0, 24, tableSprite->GetWidth(), tableSprite->GetHeight());
	goTable->AddComponent(tableSprite);
	objectArray.emplace_back(goTable);

	backgroundMusic = new Music("assets/audio/playing_theme.mp3");
	// Mix_VolumeMusic(20);
	backgroundMusic->Play();

	// TÁ CARREGANDO A TRILHA NA RAM, DÁ UMA TRAVADA NO CARREGAMENTO
	/*Sound  * sound = new Sound(*goTable, "assets/audio/aeroportoambiente.wav");
    sound->Play();
    sound->SetVolume(5);
    goTable->AddComponent(sound);
	backgroundNoise = new Music("assets/audio/aeroportoambiente.mp3");
	backgroundNoise->Play();*/
	
	GameObject* goTimer = new GameObject();
	goTimer->box = Rect(0, 0, 0, 0);
	Text* text = new Text(*goTimer, "assets/font/Roboto-Regular.ttf", 25 * windowScale.x, Text::TextStyle::BLENDED, "0", SDL_Color{ 255, 255, 255, 0 });
	timerText = text;
	goTimer->AddComponent(text);
	goTimer->box.SetCentro(windowSize.x * .43, windowSize.y * .73);
	objectArray.emplace_back(goTimer);
	
	GameObject * goScanner = new GameObject();
	Scanner * scanner = new Scanner(*goScanner);
	goScanner->AddComponent(scanner);
	objectArray.emplace_back(goScanner);

	GameObject * goButtons = new GameObject();
	Buttons * buttons = new Buttons(*goButtons);
	goButtons->AddComponent(buttons);
	objectArray.emplace_back(goButtons);

	GameObject * goLaser = new GameObject();
	Laser * laser = new Laser(*goLaser);
	goLaser->AddComponent(laser);
	objectArray.emplace_back(goLaser);

	GameObject* goManual = new GameObject();
	Sprite *manualSprite = new Sprite(*goManual, "assets/img/folha.png");
	manualSprite->SetScaleX(.7 * windowScale.x, .7 * windowScale.y);
	goManual->box = Rect(windowSize.x * .77, windowSize.y * .6, manualSprite->GetWidth(), manualSprite->GetHeight());
	goManual->AddComponent(manualSprite);
	objectArray.emplace_back(goManual);

	// IDENTIDADE CPF
	GameObject* goTextCPFIdentity = new GameObject();
	goTextCPFIdentity->box = Rect(0, 0, 0, 0);
	Text2* textCPFIdentity = new Text2(*goTextCPFIdentity, "assets/font/Roboto-Regular.ttf", 30 * windowScale.x, Text2::TextStyle::BLENDED, "CPF: ", SDL_Color{ 255, 255, 255, 0 });
	goTextCPFIdentity->AddComponent(textCPFIdentity);
	goTextCPFIdentity->box.SetCentro(windowSize.x * .085, windowSize.y * .35);
	objectArray.emplace_back(goTextCPFIdentity);

	// IDENTIDADE NOME
	GameObject* goTextNameIdentity = new GameObject();
	goTextNameIdentity->box = Rect(0, 0, 0, 0);
	Text2* textNameIdentity = new Text2(*goTextNameIdentity, "assets/font/Roboto-Regular.ttf", 30 * windowScale.x, Text2::TextStyle::BLENDED, "NOME: ", SDL_Color{ 255, 255, 255, 0 });
	goTextNameIdentity->AddComponent(textNameIdentity);
	goTextNameIdentity->box.SetCentro(windowSize.x * .092, windowSize.y * .39);
	objectArray.emplace_back(goTextNameIdentity);

	// IDENTIDADE NASCIMENTO
	GameObject* goTextBirthdayIdentity = new GameObject();
	goTextBirthdayIdentity->box = Rect(0, 0, 0, 0);
	Text2* textBirthdayIdentity = new Text2(*goTextBirthdayIdentity, "assets/font/Roboto-Regular.ttf", 0, Text2::TextStyle::BLENDED, "NASC: ", SDL_Color{ 255, 255, 255, 0 });
	goTextBirthdayIdentity->AddComponent(textBirthdayIdentity);
	goTextBirthdayIdentity->box.SetCentro(windowSize.x * .1, windowSize.y * .34);
	objectArray.emplace_back(goTextBirthdayIdentity);

	// PASSAPORTE CPF
	GameObject* goTextCPFPassport = new GameObject();
	goTextCPFPassport->box = Rect(0, 0, 0, 0);
	Text2* textCPFPassport = new Text2(*goTextCPFPassport, "assets/font/Roboto-Regular.ttf", 30 * windowScale.x, Text2::TextStyle::BLENDED, "CPF: ", SDL_Color{ 255, 255, 255, 0 });
	goTextCPFPassport->AddComponent(textCPFPassport);
	goTextCPFPassport->box.SetCentro(windowSize.x * .08, windowSize.y * .55);
	objectArray.emplace_back(goTextCPFPassport);

	// PASSAPORTE NOME
	GameObject* goTextNamePassport = new GameObject();
	goTextNamePassport->box = Rect(0, 0, 0, 0);
	Text2* textNamePassport = new Text2(*goTextNamePassport, "assets/font/Roboto-Regular.ttf", 30 * windowScale.x, Text2::TextStyle::BLENDED, "NOME: ", SDL_Color{ 255, 255, 255, 0 });
	goTextNamePassport->AddComponent(textNamePassport);
	goTextNamePassport->box.SetCentro(windowSize.x * .09, windowSize.y * .615);
	objectArray.emplace_back(goTextNamePassport);

	// PASSAPORTE DATA VOO
	GameObject* goTextDataVoo = new GameObject();
	goTextDataVoo->box = Rect(0, 0, 0, 0);
	Text2* textDataVoo = new Text2(*goTextDataVoo, "assets/font/Roboto-Regular.ttf", 30 * windowScale.x, Text2::TextStyle::BLENDED, "DATA VOO: ", SDL_Color{ 255, 255, 255, 0 });
	goTextDataVoo->AddComponent(textDataVoo);
	goTextDataVoo->box.SetCentro(windowSize.x * .278, windowSize.y * .485);
	objectArray.emplace_back(goTextDataVoo);

	// PASSAPORTE ID VOO
	GameObject* goTextIdVoo = new GameObject();
	goTextIdVoo->box = Rect(0, 0, 0, 0);
	Text2* textIdVoo = new Text2(*goTextIdVoo, "assets/font/Roboto-Regular.ttf", 30 * windowScale.x, Text2::TextStyle::BLENDED, "ID VOO: ", SDL_Color{ 255, 255, 255, 0 });
	goTextIdVoo->AddComponent(textIdVoo);
	goTextIdVoo->box.SetCentro(windowSize.x * .265, windowSize.y * .55);
	objectArray.emplace_back(goTextIdVoo);

	// PASSAPORTE ORIGEM
	GameObject* goTextOriginPassport = new GameObject();
	goTextOriginPassport->box = Rect(0, 0, 0, 0);
	Text2* textOrigem = new Text2(*goTextOriginPassport, "assets/font/Roboto-Regular.ttf", 30 * windowScale.x, Text2::TextStyle::BLENDED, "ORIGEM: ", SDL_Color{ 255, 255, 255, 0 });
	goTextOriginPassport->AddComponent(textOrigem);
	goTextOriginPassport->box.SetCentro(windowSize.x * .27, windowSize.y * .615);
	objectArray.emplace_back(goTextOriginPassport);

	// PASSAPORTE DESTINO
	GameObject* goTextDestinyPassaport = new GameObject();
	goTextDestinyPassaport->box = Rect(0, 0, 0, 0);
	Text2* textDestino = new Text2(*goTextDestinyPassaport, "assets/font/Roboto-Regular.ttf", 30 * windowScale.x, Text2::TextStyle::BLENDED, "DESTINO: ", SDL_Color{ 255, 255, 255, 0 });
	goTextDestinyPassaport->AddComponent(textDestino);
	goTextDestinyPassaport->box.SetCentro(windowSize.x * .275, windowSize.y * .68);
	objectArray.emplace_back(goTextDestinyPassaport);

	// ID VOO MANUAL
	GameObject* goIDVoo = new GameObject();
	goIDVoo->box = Rect(0, 0, 0, 0);
	Text2* textManualIDVoo = new Text2(*goIDVoo, "assets/font/Roboto-Regular.ttf", 20 * windowScale.x, Text2::TextStyle::BLENDED, "ID Voo: " + flightInfo.GetFlightID(), SDL_Color{ 0, 0, 0, 0 });
	goIDVoo->AddComponent(textManualIDVoo);
	goIDVoo->box.SetCentro(windowSize.x * .93, windowSize.y * .88);
	objectArray.emplace_back(goIDVoo);

	// ORIGEM VOO MANUAL
	GameObject* goOrigemVoo = new GameObject();
	goOrigemVoo->box = Rect(0, 0, 0, 0);
	Text2* textManualOrigemVoo = new Text2(*goOrigemVoo, "assets/font/Roboto-Regular.ttf", 20 * windowScale.x, Text2::TextStyle::BLENDED, "Origem: " + flightInfo.GetFlightOrigin(), SDL_Color{ 0, 0, 0, 0 });
	goOrigemVoo->AddComponent(textManualOrigemVoo);
	goOrigemVoo->box.SetCentro(windowSize.x * .84, windowSize.y * .88);
	objectArray.emplace_back(goOrigemVoo);

	// DESTINO VOO MANUAL
	GameObject* goDestinoVoo = new GameObject();
	goDestinoVoo->box = Rect(0, 0, 0, 0);
	Text2* textManualDestinoVoo = new Text2(*goDestinoVoo, "assets/font/Roboto-Regular.ttf", 20 * windowScale.x, Text2::TextStyle::BLENDED, "Destino: " + flightInfo.GetFlightDestiny(), SDL_Color{ 0, 0, 0, 0 });
	goDestinoVoo->AddComponent(textManualDestinoVoo);
	goDestinoVoo->box.SetCentro(windowSize.x * .84, windowSize.y * .905);
	objectArray.emplace_back(goDestinoVoo);

	// DATA VOO MANUAL
	GameObject* goDataVoo = new GameObject();
	goDataVoo->box = Rect(0, 0, 0, 0);
	Text2* textManualDataVoo = new Text2(*goDataVoo, "assets/font/Roboto-Regular.ttf", 25 * windowScale.x, Text2::TextStyle::BLENDED, flightInfo.GetFlightDate(), SDL_Color{ 255, 255, 255, 0 });
	goDataVoo->AddComponent(textManualDataVoo);
	goDataVoo->box.SetCentro(windowSize.x * .38, windowSize.y * .73);
	objectArray.emplace_back(goDataVoo);

	int minutes = (int) phases[currentPhase-1] / 60;
	int seconds = ((int) phases[currentPhase-1]) % 60;
	
	std::string minutesString = to_string(minutes);
	std::string secondsString = to_string(seconds);
	
	if (seconds < 10) {
		secondsString = "0" + secondsString;
	}

	// ENCERRAMENTO DO EXPEDIENTE
	GameObject* goExpediente = new GameObject();
	goExpediente->box = Rect(0, 0, 0, 0);
	Text2* textExpediente = new Text2(*goExpediente, "assets/font/Roboto-Regular.ttf", 20 * windowScale.x, Text2::TextStyle::BLENDED, "Expediente encerra: " + minutesString + ":" + secondsString , SDL_Color{ 0, 0, 0, 0 });
	goExpediente->AddComponent(textExpediente);
	goExpediente->box.SetCentro(windowSize.x * .86, windowSize.y * .95);
	objectArray.emplace_back(goExpediente);

	// OBJETIVO
	GameObject* goGoal = new GameObject();
	goGoal->box = Rect(0, 0, 0, 0);
	Text2* textGoal = new Text2(*goGoal, "assets/font/Roboto-Regular.ttf", 15 * windowScale.x, Text2::TextStyle::BLENDED, std::to_string(flightInfo.GetGoal()), SDL_Color{ 0, 0, 0, 0 });
	goGoal->AddComponent(textGoal);
	goGoal->box.SetCentro(windowSize.x * .845, windowSize.y * .842);
	objectArray.emplace_back(goGoal);

	// ATUAL
	GameObject* goCurrent = new GameObject();
	goCurrent->box = Rect(0, 0, 0, 0);
	Text2* textCurrent = new Text2(*goCurrent, "assets/font/Roboto-Regular.ttf", 15 * windowScale.x, Text2::TextStyle::BLENDED, std::to_string(flightInfo.GetScore()), SDL_Color{ 0, 0, 0, 0 });
	goCurrent->AddComponent(textCurrent);
	goCurrent->box.SetCentro(windowSize.x * .934, windowSize.y * .842);
	objectArray.emplace_back(goCurrent);
}

void AnalysisState::Update(float dt) {
	gameTime.Update(dt);
	Camera::Update(dt);
	
	int mouseX = InputManager::GetInstance().GetMouseX() + Camera::pos.x;
	int mouseY = InputManager::GetInstance().GetMouseY() + Camera::pos.y;
	if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
		cout << mouseX << endl;
		cout << mouseY << endl;
	}

	for (unsigned int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i]->IsDead()) {
			objectArray.erase(objectArray.begin() + i);
			i--;
		}
	}
	
	// std::cout << Passenger::currentPassenger ? "EXISTE" : "NÃO EXISTE" << std::endl;
	
	if(Passenger::currentPassenger.expired()) {
		GameObject * goPassenger = new GameObject();
		//goPassenger->box = Rect(500, 100, 0, 0);
		Passenger * passenger = new Passenger(*goPassenger);
		goPassenger->AddComponent(passenger);
		auto passengerCollider = new Collider(*goPassenger);
		passengerCollider->SetScale(Vec2(.7, .45));
		passengerCollider->SetOffset(Vec2(5, -200));
		goPassenger->AddComponent(passengerCollider);
		Passenger::currentPassenger = AddObject(goPassenger);
		WalkBack(5 + 17, goPassenger);
	}

	// int mouseX = InputManager::GetInstance().GetMouseX() + Camera::pos.x;
    // int mouseY = InputManager::GetInstance().GetMouseY() + Camera::pos.y;
	
	auto currentPassengerShared = Passenger::currentPassenger.lock();
	FlightInfo& flightInfo = FlightInfo::GetInstance();

	if (currentPassengerShared) {
		auto passengerComponent = (Passenger *) currentPassengerShared->GetComponent("Passenger");
		Vec2 windowSize = Game::GetInstance().GetWindowSize();

		if(passengerComponent) {
			if (!passengerComponent->IsMoving()) {
				if (passengerComponent->documents.size() == 2 &&
				InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) &&
				((mouseX >= windowSize.x * .157) && (mouseX <= windowSize.x * .243) &&
				(mouseY >= windowSize.y * .886) && (mouseY <= windowSize.y * .95))){
					if(passengerComponent->GetValidity())
						flightInfo.UpdateScore(1);
					else
						flightInfo.UpdateScore(0);
					passengerComponent->Approve();
					for (unsigned int i = 0; i < objectArray.size(); i++) {
						if(objectArray[i]->GetComponent("Buttons")) {
							objectArray[i]->NotifyCollision(*objectArray[i]);
						}
					}
				}
				else if (passengerComponent->documents.size() == 2 &&
				InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) &&
				((mouseX >= windowSize.x * .253) && (mouseX <= windowSize.x * .339) &&
				(mouseY >= windowSize.y * .886) && (mouseY <= windowSize.y * .95))){
					if(passengerComponent->GetValidity())
						flightInfo.UpdateScore(0);
					else 
						flightInfo.UpdateScore(1);
					passengerComponent->Disapprove();
					for (unsigned int i = 0; i < objectArray.size(); i++) {
						if(objectArray[i]->GetComponent("Buttons")) {
							objectArray[i]->NotifyCollision(*objectArray[i]);
						}
					}
				}
			}
		}
	}

	for (int i = objectArray.size() - 1; i >= 0 ; i--) {
		objectArray[i]->Update(dt);
	}
	
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		Collider* a = (Collider*)objectArray[i]->GetComponent("Collider");
		if (a != nullptr) {
			for (unsigned int j = i + 1; j < objectArray.size(); j++) {
				Collider* b = (Collider*)objectArray[j]->GetComponent("Collider");
				if (b != nullptr) {
					if (Collision::IsColliding(a->box, b->box, a->associated.angleDeg, b->associated.angleDeg)) {
						objectArray[i]->NotifyCollision(*objectArray[j]);
						objectArray[j]->NotifyCollision(*objectArray[i]);
					}
				}
			}
 		}
	}

	int position;
	for(int i = 0; i < objectArray.size(); i++) {
		if(objectArray[i]->GetComponent("Text2")) {
			position = i;
		}
	}
	objectArray[position]->RemoveComponent("Text2");
    Text2* newCurrentScore = new Text2(*objectArray[position], "assets/font/Roboto-Regular.ttf", 15, Text2::TextStyle::BLENDED,std::to_string(flightInfo.GetScore()), SDL_Color{ 0, 0, 0, 0 });
    objectArray[position]->AddComponent(newCurrentScore);
	
	auto currentTimeSeconds = gameTime.Get();

	if (flightInfo.GetScore() >= flightInfo.GetGoal()) {
		auto sharedPassenger = Passenger::currentPassenger.lock();
    	if(sharedPassenger) {
        	auto passengerComponent = (Passenger*) sharedPassenger->GetComponent("Passenger");
			passengerComponent->DeleteAll();
		}
		flightInfo.ResetScore();
		std::fstream file("save.txt", std::ios::out | std::ios::in | std::ios::trunc);
		file << std::to_string(currentPhase+1);
		file.close();
		backgroundMusic->Stop(0);
		GameData::playerVictory = true;
		EndState* endState = new EndState();
		Game::GetInstance().Push(endState);
	}

	if (currentTimeSeconds >= phases[currentPhase-1]) {
		backgroundMusic->Stop(0);
		GameData::playerVictory = false;
		EndState* endState = new EndState();
		Game::GetInstance().Push(endState);
	}
	
	if (!fastMusic && (currentTimeSeconds >= (phases[currentPhase-1] - 30))) {
		fastMusic = true;
		// backgroundMusic->Stop(0);
		backgroundMusic = new Music("assets/audio/playing_theme_fast.mp3");
		// Mix_VolumeMusic(100);
		backgroundMusic->Play();
	}
	
	int minutes = (int) currentTimeSeconds / 60;
	int seconds = ((int) currentTimeSeconds) % 60;
	
	string minutesString = to_string(minutes);
	string secondsString = to_string(seconds);
	
	if (seconds < 10) {
		secondsString = "0" + secondsString;
	}
	
	timerText->SetText(minutesString + ":" + secondsString);
	
	quitRequested = false;
	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested() == true) {
		quitRequested = true;
	}
}

void AnalysisState::Start() {
    LoadAssets();
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Start();
	}
	started = true;
}

void AnalysisState::Pause() {
	backgroundMusic->Stop(0);
}

void AnalysisState::Resume() {}