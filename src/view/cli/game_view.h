#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "model/taquin.h"
#include "model/timer.h"
#include "model/score.h"

void displayGameState(const Taquin *taquin, const Timer *gameTimer);
bool handleUserInput(Taquin *taquin, bool *gameWon);
void handleGameWin(const Timer *gameTimer, Leaderboard *leaderboard, const char *scoreFilePath);

#endif // GAME_VIEW_H