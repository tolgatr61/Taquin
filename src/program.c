#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "model/taquin.h" // Votre fichier d'en-tête

int main() {
    printf("Creation d'un taquin de taille 3x3\n");
    Taquin *taquin = createTaquin(3);
    shuffleTaquin(taquin);

    Timer gameTimer;
    startTimer(&gameTimer);

    double timeLimit = 120.0; // Limite de temps fixee, par exemple 120 secondes

    bool gameRunning = true;
    while (gameRunning) {
        double elapsedTime = getElapsedTime(&gameTimer);

        // Verifier si le temps maximal est atteint
        if (elapsedTime >= timeLimit) {
            printf("Temps ecoule ! Le jeu est termine.\n");
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
                gameRunning = false;
            }
        } else {
            printf("Entree invalide. Veuillez reessayer.\n");
        }
    }

    stopTimer(&gameTimer);
    if (checkVictory(taquin)) {
        printf("Felicitations ! Vous avez resolu le puzzle en %.2f secondes!\n", getElapsedTime(&gameTimer));
    } else {
        printf("Jeu termine. Vous n'avez pas resolu le puzzle. Temps total: %.2f secondes\n", getElapsedTime(&gameTimer));
    }

    freeTaquin(taquin);
    return 0;
}