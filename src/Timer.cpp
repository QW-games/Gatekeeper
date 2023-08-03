#include "Timer.h"

Timer::Timer(float offset) {
	time = offset;
}

void Timer::Update(float dt) {
	time += dt;
	// cout << time << endl;
}

void Timer::Restart() {
	time = 0;
}

float Timer::Get() {
	return time;
}