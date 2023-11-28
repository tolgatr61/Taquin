#include "taquin.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif


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

void startTimer(Timer *timer) {
    if (timer != NULL) {
        timer->start_time = time(NULL);
        timer->end_time = 0; // On s'assure que end_time est réinitialisé
    }
}

double getElapsedTime(const Timer *timer) {
    if (timer != NULL && timer->start_time != 0) {
        time_t current_time = time(NULL);
        return difftime(current_time, timer->start_time);
    }
    return 0.0;
}

void stopTimer(Timer *timer) {
    if (timer == NULL) {
        printf("Timer non initialisé.\n");
        return;
    }
    timer->end_time = time(NULL);  // Enregistre l'heure actuelle
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

// Libère la mémoire allouée pour un score
void freeScore(Score *score) {
    if (score != NULL) {
        free(score->player_name);
        free(score);
    }
}

// Libère la mémoire allouée pour tous les scores dans le classement
void freeScores(Leaderboard *leaderboard) {
    for (int i = 0; i < MAX_SCORES; i++) {
        freeScore(leaderboard->scores[i]);
        leaderboard->scores[i] = NULL;
    }
}

// Crée un score et l'initialise
Score *createScore(const char *name, double time) {
    Score *new_score = malloc(sizeof(Score));
    if (new_score == NULL) {
        return NULL;
    }

    new_score->player_name = strdup(name);
    new_score->time_taken = time;

    return new_score;
}

// Affiche les scores
void printScores(const Leaderboard *leaderboard) {
    for (int i = 0; i < MAX_SCORES; i++) {
        if (leaderboard->scores[i] != NULL) {
            printf("%s: %f\n", leaderboard->scores[i]->player_name, leaderboard->scores[i]->time_taken);
        }
    }
}

// Ajoute un score au tableau des scores dans le classement
void addScore(Leaderboard *leaderboard, Score *new_score) {
    int i;
    for (i = 0; i < MAX_SCORES; i++) {
        if (leaderboard->scores[i] == NULL || leaderboard->scores[i]->time_taken > new_score->time_taken) {
            break;
        }
    }

    if (i < MAX_SCORES) {
        freeScore(leaderboard->scores[MAX_SCORES - 1]);
        for (int j = MAX_SCORES - 1; j > i; j--) {
            leaderboard->scores[j] = leaderboard->scores[j - 1];
        }
        leaderboard->scores[i] = new_score;
    } else {
        freeScore(new_score);
    }
}

void sortScores(Leaderboard *leaderboard) {
    bool sorted;
    do {
        sorted = true;
        for (int i = 0; i < MAX_SCORES - 1; i++) {
            if (leaderboard->scores[i] && leaderboard->scores[i + 1] && 
                leaderboard->scores[i]->time_taken > leaderboard->scores[i + 1]->time_taken) {
                Score *temp = leaderboard->scores[i];
                leaderboard->scores[i] = leaderboard->scores[i + 1];
                leaderboard->scores[i + 1] = temp;
                sorted = false;
            }
        }
    } while (!sorted);
}

// Sauvegarde les scores dans un fichier
bool saveScoresToFile(Leaderboard *leaderboard, const char *filepath) {
    #ifdef _WIN32
    mkdir("save");
    #else
    mkdir("save", 0777);
    #endif

    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        return false;
    }

    sortScores(leaderboard); // Trie les scores avant la sauvegarde

    for (int i = 0; i < MAX_SCORES; i++) {
        if (leaderboard->scores[i] != NULL) {
            fprintf(file, "%s %f\n", leaderboard->scores[i]->player_name, leaderboard->scores[i]->time_taken);
        }
    }

    fclose(file);
    return true;
}

// Charge les scores depuis un fichier
bool loadScoresFromFile(Leaderboard *leaderboard, const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        return false; // Pas de scores à charger
    }

    char name[100];
    double time;
    int index = 0;

    while (fscanf(file, "%99s %lf", name, &time) == 2 && index < MAX_SCORES) {
        freeScore(leaderboard->scores[index]);
        leaderboard->scores[index] = createScore(name, time);
        index++;
    }

    fclose(file);
    sortScores(leaderboard); // Trie les scores après le chargement
    return true;
}