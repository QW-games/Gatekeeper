#ifndef STATE_H
#define STATE_H
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include "GameObject.h"
#if defined (_WIN64) || defined (_WIN32)
#include "SDL2/SDL.h"
#else
#include <SDL2/SDL.h>
#endif
using namespace std;

// #define MAX_SELECTED_OBJECTS 2
// #define TIME_SECONDS_IN_COMPARATOR 1

class State{
public:
    State();
    virtual ~State();
    virtual void LoadAssets()= 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    virtual void Start() = 0;
    virtual weak_ptr<GameObject> AddObject(GameObject* object);
    virtual weak_ptr<GameObject> GetObjectPtr(GameObject* object);
    void BringToFront(GameObject* object);
    void WalkBack(int times, GameObject* object);
    bool PopRequested();
    bool QuitRequested();
    
    vector<shared_ptr<GameObject>> objectArray;

protected:
    void StartArray();
    virtual void UpdateArray(float dt);
    virtual void RenderArray();
    
    bool popRequested;
    bool quitRequested;
    bool started;
};

#endif