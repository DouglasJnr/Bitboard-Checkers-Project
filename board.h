#ifndef BOARD_H
#define BOARD_H

// Game state structure using bitboards
typedef struct {
    unsigned long long red_pieces;      // Regular red pieces
    unsigned long long red_kings;       // Red king pieces
    unsigned long long black_pieces;    // Regular black pieces
    unsigned long long black_kings;     // Black king pieces
    int current_player;                 // 0 = Red, 1 = Black
    int game_over;                      // Flag for game end
} GameState;

// Only dark squares are playable in checkers (32 squares total)
extern const unsigned long long PLAYABLE_SQUARES;

// Board functions
void InitializeGame(GameState* game);
void DisplayBoard(GameState* game);
int GetPosition(int row, int col);
int IsValidPosition(int row, int col);

#endif // BOARD_H