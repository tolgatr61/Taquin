#include "game_win_handler.h"
#include "view/cli/game_view.h"
#include <stdio.h>

void handleGameWin(Timer *gameTimer, Leaderboard *leaderboard, const char *scoreFilePath) {
    double elapsedTime = getElapsedTime(gameTimer);
    printf("Félicitations ! Vous avez résolu le puzzle en %.2f secondes!\n", elapsedTime);

    displayPlayerNamePrompt();
    char playerName[50];
    scanf("%49s", playerName);

    Score *newScore = createScore(playerName, elapsedTime);
    addScore(leaderboard, newScore);
    saveScoresToFile(leaderboard, scoreFilePath);
}
