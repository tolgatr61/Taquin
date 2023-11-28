#include "user_input_handler.h"
#include <stdio.h>
#include <string.h>

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
