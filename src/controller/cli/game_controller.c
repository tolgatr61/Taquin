#include "game_controller.h"
#include "model/taquin.h"
#include "model/timer.h"
#include "model/score.h"
#include "view/cli/game_view.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static void gameLoop(Taquin *taquin, Timer *gameTimer, Leaderboard *leaderboard, const char *scoreFilePath);

void runGame(const char *scoreFilePath) {
    Leaderboard leaderboard = {0};
    loadScoresFromFile(&leaderboard, scoreFilePath);

    Taquin *taquin = createTaquin(3);
    if (!taquin) {
        printf("Echec de l'initialisation du taquin.\n");
        return;
    }
    shuffleTaquin(taquin);

    Timer gameTimer;
    startTimer(&gameTimer);

    gameLoop(taquin, &gameTimer, &leaderboard, scoreFilePath);

    freeScores(&leaderboard);
    freeTaquin(taquin);
}

static void gameLoop(Taquin *taquin, Timer *gameTimer, Leaderboard *leaderboard, const char *scoreFilePath) {
    bool gameRunning = true, gameWon = false;
    while (gameRunning) {
        displayGameState(taquin, gameTimer);
        gameRunning = handleUserInput(taquin, &gameWon);
        if (gameWon) {
            handleGameWin(gameTimer, leaderboard, scoreFilePath);
        }
    }
}
