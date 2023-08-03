#ifndef STAGESTATE_H
#define STAGESTATE_H
#include "Sprite.h"
#include "Music.h"
#include "Vec2.h"
#include "Sound.h"
#include "TileMap.h"
#include "TitleState.h"
#include "TileSet.h"
#include <memory>
#include <vector>
#if defined (_WIN64) || defined (_WIN32)
#include "SDL2/SDL.h"
#else
#include <SDL2/SDL.h>
#endif
using namespace std;

class StageState : public State{
    
    TileSet* tileSet;
    Music* backgroundMusic;
    int bolax;
    int livrox;
    int bolay;
    int livroy;
    GameObject* bola;
    GameObject* livro;
    bool seguindo;
    bool seguindo1;
public:
    void Start();
    ~StageState();
    StageState();
    void Pause();
    void Resume();
    void LoadAssets();
    void Update(float dt);
    void Render();
};
#endif