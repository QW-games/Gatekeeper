#include "Sound.h"
#include "Resources.h"
Sound::Sound(GameObject& associated) : Component(associated) {
	this->associated = associated;
	chunk = nullptr;
}

Sound::Sound(GameObject& associated, string file) : Component( associated) {
	this->associated = associated;
	Open(file);
}

void Sound::Play(int times) {
	Mix_PlayChannel(-1, chunk, times - 1);
}

void Sound::Stop() {
	Mix_HaltChannel(channel);
}

void Sound::Open(std::string file) {
	chunk = Resources::GetSound(file);
	//chunk = Mix_LoadWAV(file.c_str());
}

Sound::~Sound() {
	if (chunk != nullptr) {
		Mix_HaltChannel(channel);
	}
	//Mix_FreeChunk(chunk);
}

bool Sound::IsOpen() {
	return chunk != nullptr;
}

void Sound::Update(float dt) {

}

void Sound::Render() {
}

bool Sound::Is(string type) {
	return type == "Sound" ? true : false;
}

void Sound::SetVolume(int volume) {
	Mix_Volume(channel, volume);
}
