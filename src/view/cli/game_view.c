#include "game_view.h"
#include <stdio.h>
#include <string.h>

void displayGameState(const Taquin *taquin, const Timer *gameTimer) {
    printTaquin(taquin);
    printf("Temps écoulé: %.2f secondes\n", getElapsedTime(gameTimer));
}

bool handleUserInput(Taquin *taquin, bool *gameWon) {
    printf("Entrez 'ligne colonne' pour déplacer une tuile, ou 'quit' pour quitter: ");
    char input[10];
    fgets(input, 10, stdin);

    unsigned int tempRow, tempCol;
    if (strncmp(input, "quit", 4) == 0) {
        return false;
    } else if (sscanf(input, "%u %u", &tempRow, &tempCol) == 2) {
        uint8_t row = (uint8_t)(tempRow - 1);
        uint8_t col = (uint8_t)(tempCol - 1);

        if (!moveTile(taquin, row, col)) {
            printf("Mouvement non valide ou hors limites. Veuillez réessayer.\n");
        } else if (checkVictory(taquin)) {
            *gameWon = true;
        }
    } else {
        printf("Entrée invalide. Veuillez réessayer.\n");
    }
    return true;
}

void handleGameWin(const Timer *gameTimer, Leaderboard *leaderboard, const char *scoreFilePath) {
    double elapsedTime = getElapsedTime(gameTimer);
    printf("Félicitations ! Vous avez résolu le puzzle en %.2f secondes!\n", elapsedTime);

    char playerName[50];
    printf("Entrez votre nom pour enregistrer votre score: ");
    scanf("%49s", playerName);

    Score *newScore = createScore(playerName, elapsedTime);
    addScore(leaderboard, newScore);
    saveScoresToFile(leaderboard, scoreFilePath);

    printf("\nTop 10 des Scores:\n");
    printScores(leaderboard);
}
