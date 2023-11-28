#include "score.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <direct.h>  // Pour _mkdir sous Windows
#else
#include <sys/stat.h>  // Pour mkdir sous UNIX-like
#endif

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

// Affiche les scores
void printScores(const Leaderboard *leaderboard) {
    for (int i = 0; i < MAX_SCORES; i++) {
        if (leaderboard->scores[i] != NULL) {
            printf("%s: %f\n", leaderboard->scores[i]->player_name, leaderboard->scores[i]->time_taken);
        }
    }
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