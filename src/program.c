#include "controller/cli/game_controller.h"

int main() {
    const char *scoreFilePath = "save/taquinsave.txt";
    runGame(scoreFilePath);
    return 0;
}