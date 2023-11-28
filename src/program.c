#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "model/taquin.h"

int main() {
    const char *scoreFilePath = "save/taquinsave.txt";
    Leaderboard leaderboard = {0};

    loadScoresFromFile(&leaderboard, scoreFilePath);

    printf("Creation d'un taquin de taille 3x3\n");
    Taquin *taquin = createTaquin(3);
    if (!taquin) {
        printf("echec de l'initialisation du taquin.\n");
        return 1;
    }
    shuffleTaquin(taquin);

    Timer gameTimer;
    startTimer(&gameTimer);

    double timeLimit = 120.0;
    bool gameRunning = true;
    bool gameWon = false;

    while (gameRunning) {
        double elapsedTime = getElapsedTime(&gameTimer);

        if (elapsedTime >= timeLimit) {
            printf("Temps ecoule ! Le jeu est termine.\n");
            gameRunning = false;
            break;
        }

        printTaquin(taquin);
        printf("Temps ecoule: %.2f secondes\n", elapsedTime);

        printf("Entrez 'ligne colonne' pour deplacer une tuile, ou 'quit' pour quitter: ");
        char input[10];
        fgets(input, 10, stdin);

        unsigned int tempRow, tempCol;
        if (strncmp(input, "quit", 4) == 0) {
            gameRunning = false;
            break;
        } else if (sscanf(input, "%u %u", &tempRow, &tempCol) == 2) {
            uint8_t row = (uint8_t)(tempRow - 1);
            uint8_t col = (uint8_t)(tempCol - 1);

            if (!moveTile(taquin, row, col)) {
                printf("Mouvement non valide ou hors limites. Veuillez reessayer.\n");
            } else if (checkVictory(taquin)) {
                printf("Felicitations ! Vous avez resolu le puzzle !\n");
                gameWon = true;
                gameRunning = false;
            }
        } else {
            printf("Entree invalide. Veuillez reessayer.\n");
        }
    }

    stopTimer(&gameTimer);

    if (gameWon) {
        double elapsedTime = getElapsedTime(&gameTimer);
        printf("Felicitations ! Vous avez resolu le puzzle en %.2f secondes!\n", elapsedTime);

        char playerName[50];
        printf("Entrez votre nom pour enregistrer votre score: ");
        scanf("%49s", playerName);

        Score *newScore = createScore(playerName, elapsedTime);
        addScore(&leaderboard, newScore);
        saveScoresToFile(&leaderboard, scoreFilePath);
    } else {
        printf("Jeu termine. Temps total: %.2f secondes\n", getElapsedTime(&gameTimer));
    }

    printf("\nTop 10 des Scores:\n");
    printScores(&leaderboard);

    freeScores(&leaderboard);
    freeTaquin(taquin);
    return 0;
}
