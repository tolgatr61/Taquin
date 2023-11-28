#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "model/taquin.h"
#include "model/timer.h"
#include "model/score.h"

void displayGameState(const Taquin *taquin, const Timer *gameTimer);
void displayLeaderboard(const Leaderboard *leaderboard);
void displayPlayerNamePrompt();

#endif // GAME_VIEW_H