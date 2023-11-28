#ifndef SCORE_H
#define SCORE_H

#include <stdbool.h>

#define MAX_SCORES 10

// Structures pour la gestion des scores.
typedef struct {
    char *player_name;
    double time_taken;
} Score;

typedef struct {
    Score *scores[MAX_SCORES];
} Leaderboard;

Score *createScore(const char *name, double time);
void addScore(Leaderboard *leaderboard, Score *new_score);
void freeScore(Score *score);
void freeScores(Leaderboard *leaderboard);
bool saveScoresToFile(Leaderboard *leaderboard, const char *filepath);
bool loadScoresFromFile(Leaderboard *leaderboard, const char *filepath);
void printScores(const Leaderboard *leaderboard);

#endif // SCORE_H
