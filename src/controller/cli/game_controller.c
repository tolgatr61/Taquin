#include "game_controller.h"
#include "model/taquin.h"
#include "model/timer.h"
#include "model/score.h"
#include "view/cli/game_view.h"
#include "controller/cli/user_input_handler.h"
#include "controller/cli/game_win_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static void gameLoop(Taquin *taquin, Timer *gameTimer, Leaderboard *leaderboard, const char *scoreFilePath) {
    bool gameRunning = true, gameWon = false;
    while (gameRunning && !checkVictory(taquin)) {
        displayGameState(taquin, gameTimer);
        gameRunning = handleUserInput(taquin, &gameWon);
    }

    if (gameWon) {
        handleGameWin(gameTimer, leaderboard, scoreFilePath);
    }
}


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

    stopTimer(&gameTimer);

    displayLeaderboard(&leaderboard);

    freeScores(&leaderboard);
    freeTaquin(taquin);
}