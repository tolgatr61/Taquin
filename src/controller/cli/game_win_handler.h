#ifndef GAME_WIN_HANDLER_H
#define GAME_WIN_HANDLER_H

#include "model/timer.h"
#include "model/score.h"

void handleGameWin(Timer *gameTimer, Leaderboard *leaderboard, const char *scoreFilePath);

#endif // GAME_WIN_HANDLER_H