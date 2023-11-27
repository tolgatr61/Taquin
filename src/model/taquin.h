#ifndef TAQUIN_H
#define TAQUIN_H

#include <stdbool.h>
#include <time.h>
#include <stdint.h>  // Ajout pour uint8_t, uint16_t

// Structure représentant une tuile individuelle dans le puzzle de taquin.
typedef struct {
    uint8_t row;          // Ligne où se trouve la tuile.
    uint8_t col;          // Colonne où se trouve la tuile.
    uint16_t number;      // Numéro assigné à la tuile pour référence visuelle.
    void *imagePart;      // Pointeur vers une portion d'image associée à la tuile, si applicable.
} Tile;

// Structure représentant la tuile vide dans le puzzle de taquin.
typedef struct {
    uint8_t row;          // Ligne de la tuile vide.
    uint8_t col;          // Colonne de la tuile vide.
} EmptyTile;

// Structure pour le puzzle de taquin dans son ensemble.
typedef struct {
    uint8_t size;        // Dimensions du puzzle (n x n).
    Tile **tiles;        // Tableau de pointeurs vers les tuiles du puzzle.
    EmptyTile emptyTile; // Tuile vide utilisée pour les déplacements.
} Taquin;

// Structure pour gérer le chronométrage du jeu.
typedef struct {
    time_t start_time;  // Moment de démarrage du chronomètre.
    time_t end_time;    // Moment d'arrêt du chronomètre.
} Timer;

// Structure pour stocker les scores des joueurs.
typedef struct {
    char *player_name;  // Nom du joueur.
    double time_taken;  // Durée écoulée pour résoudre le puzzle.
} Score;

// Déclaration des fonctions pour la gestion du puzzle de taquin.
Taquin *createTaquin(uint8_t size);
void shuffleTaquin(Taquin *taquin);
bool moveTile(Taquin *taquin, uint8_t row, uint8_t col);
bool checkVictory(const Taquin *taquin);

// Déclaration des fonctions pour la gestion du chronomètre.
void startTimer(Timer *timer);
void stopTimer(Timer *timer);
double getElapsedTime(const Timer *timer);

// Déclaration des fonctions pour la gestion des scores.
bool saveScore(const Score *score, const char *filename);
Score *loadScores(const char *filename, size_t *num_scores);

// Déclaration des fonctions utilitaires.
void freeTaquin(Taquin *taquin);
void freeScores(Score *scores, size_t num_scores);

void printTaquin(const Taquin *taquin);

#endif // TAQUIN_H