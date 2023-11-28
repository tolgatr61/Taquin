#include "taquin.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


Taquin *createTaquin(uint8_t size) {
    Taquin *taquin = malloc(sizeof(Taquin));
    if (taquin == NULL) {
        printf("Taquin non initialisé.\n");
        return NULL;
    }
    taquin->size = size;
    taquin->tiles = malloc(size * sizeof(Tile*));

    for (uint8_t i = 0; i < size; i++) {
        taquin->tiles[i] = malloc(size * sizeof(Tile));
        for (uint8_t j = 0; j < size; j++) {
            taquin->tiles[i][j].row = i;
            taquin->tiles[i][j].col = j;
            taquin->tiles[i][j].number = i * size + j + 1;
        }
    }

    taquin->emptyTile.row = size - 1;
    taquin->emptyTile.col = size - 1;
    taquin->tiles[taquin->emptyTile.row][taquin->emptyTile.row].number = 0; 
    return taquin;
}

void shuffleTaquin(Taquin *taquin) {
    if (taquin == NULL) {
        printf("Taquin non initialisé.\n");
        return;
    }

    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));

    // Nombre de mouvements pour mélanger
    int shuffle_moves = taquin->size * taquin->size * 100;

    for (int i = 0; i < shuffle_moves; i++) {
        // Sélection aléatoire d'une direction pour le mouvement : haut, bas, gauche, droite
        int move = rand() % 4;
        uint8_t row = taquin->emptyTile.row;
        uint8_t col = taquin->emptyTile.col;

        switch (move) {
            case 0: // haut
                if (row > 0) moveTile(taquin, row - 1, col);
                break;
            case 1: // bas
                if (row < taquin->size - 1) moveTile(taquin, row + 1, col);
                break;
            case 2: // gauche
                if (col > 0) moveTile(taquin, row, col - 1);
                break;
            case 3: // droite
                if (col < taquin->size - 1) moveTile(taquin, row, col + 1);
                break;
        }
    }
}

void printTaquin(const Taquin *taquin) {
    if (taquin == NULL) {
        printf("Taquin non initialisé.\n");
        return;
    }

    for (uint8_t i = 0; i < taquin->size; i++) {
        for (uint8_t j = 0; j < taquin->size; j++) {
            if (taquin->tiles[i][j].number == 0) {
                printf("   ");
            } else {
                printf("%2d ", taquin->tiles[i][j].number);
            }
        }
        printf("\n");
    }
}

bool moveTile(Taquin *taquin, uint8_t row, uint8_t col) {
    // Vérifier la validité des paramètres
    if (taquin == NULL || row >= taquin->size || col >= taquin->size) {
        printf("Paramètre invalide ou hors index.\n");
        return false;
    }

    // Calculer la différence entre les coordonnées de la tuile et de l'espace vide
    int rowDiff = abs((int)row - (int)taquin->emptyTile.row);
    int colDiff = abs((int)col - (int)taquin->emptyTile.col);

    // Vérifier si le mouvement est valide
    if ((rowDiff == 1 && colDiff == 0) || (rowDiff == 0 && colDiff == 1)) {
        // Échanger la tuile avec l'espace vide
        Tile temp = taquin->tiles[row][col];
        taquin->tiles[row][col] = taquin->tiles[taquin->emptyTile.row][taquin->emptyTile.col];
        taquin->tiles[taquin->emptyTile.row][taquin->emptyTile.col] = temp;

        // Mettre à jour la position de la tuile vide
        taquin->emptyTile.row = row;
        taquin->emptyTile.col = col;

        return true;
    }

    return false;
}

bool checkVictory(const Taquin *taquin) {
    if (taquin == NULL) {
        printf("Taquin non initialisé.\n");
        return false;
    }

    uint16_t expectedNumber = 1;

    for (uint8_t i = 0; i < taquin->size; i++) {
        for (uint8_t j = 0; j < taquin->size; j++) {
            // Vérifier si la tuile courante a le bon numéro, sauf pour la dernière tuile qui devrait être l'espace vide.
            if (i == taquin->size - 1 && j == taquin->size - 1) {
                if (taquin->tiles[i][j].number != 0) {
                    return false;
                }
            } else {
                if (taquin->tiles[i][j].number != expectedNumber) {
                    return false;
                }
                expectedNumber++;
            }
        }
    }

    return true;
}

void freeTaquin(Taquin *taquin) {
    if (taquin == NULL) {
        printf("Taquin non initialisé.\n");
        return;
    }

    for (uint8_t i = 0; i < taquin->size; i++) {
        free(taquin->tiles[i]);
    }
    free(taquin->tiles);
    free(taquin);
}