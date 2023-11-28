#ifndef TAQUIN_H
#define TAQUIN_H

#include <stdbool.h>
#include <stdint.h>

// Structures et déclarations pour le puzzle de taquin.
typedef struct {
    uint8_t row;
    uint8_t col;
    uint16_t number;
    void *imagePart;
} Tile;

typedef struct {
    uint8_t row;
    uint8_t col;
} EmptyTile;

typedef struct {
    uint8_t size;
    Tile **tiles;
    EmptyTile emptyTile;
} Taquin;

Taquin *createTaquin(uint8_t size);
void shuffleTaquin(Taquin *taquin);
bool moveTile(Taquin *taquin, uint8_t row, uint8_t col);
bool checkVictory(const Taquin *taquin);
void freeTaquin(Taquin *taquin);
void printTaquin(const Taquin *taquin);

#endif // TAQUIN_H