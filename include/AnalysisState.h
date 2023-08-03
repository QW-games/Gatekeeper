#pragma once

#include "Sprite.h"
#include "Music.h"
#include "Vec2.h"
#include "Sound.h"
#include "TileMap.h"
#include "TitleState.h"
#include "TileSet.h"
#include "Text.h"
#include "Passenger.h"
#include "MouseDragger.h"
#include "Identity.h"
#include "Passport.h"
#include "Scanner.h"
#include "Timer.h"

#include <random>
#include <memory>
#include <vector>
#include <string>

#define INITIAL_TIME_IN_SECONDS 480
#define FINAL_TIME_IN_SECONDS 720

class AnalysisState : public State {
public:
	AnalysisState(int phase);
	~AnalysisState();
	void LoadAssets();
	void Update(float dt);
	void Render();
	void Start();
	void Pause();
	void Resume();

private:
	Music* backgroundMusic;
	Music* backgroundNoise;
	Timer gameTime;
	Text * timerText;

	bool fastMusic;
};