#include "Game.h"
#include "StageState.h"
#include <ctime>

int main(int argc, char** argv) {
    std::srand((unsigned) time(NULL));
    Game::GetInstance().Push(new TitleState);
    Game::GetInstance().Run();
    return 0;
}