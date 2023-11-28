#include "game_view.h"
#include <stdio.h>

void displayGameState(const Taquin *taquin, const Timer *gameTimer) {
    printTaquin(taquin);
    printf("Temps écoulé: %.2f secondes\n", getElapsedTime(gameTimer));
}

void displayLeaderboard(const Leaderboard *leaderboard) {
    printf("\nTop 10 des Scores:\n");
    printScores(leaderboard);
}

void displayPlayerNamePrompt() {
    printf("Entrez votre nom pour enregistrer votre score: ");
}