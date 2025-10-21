#include <stdio.h>
#include "board.h"
#include "bitops.h"

// Only dark squares are playable in checkers
const unsigned long long PLAYABLE_SQUARES = 0xAA55AA55AA55AA55ULL;

// Initializes a new game with standard checkers starting position
void InitializeGame(GameState* game) {
    game->red_pieces = 0ULL;
    game->red_kings = 0ULL;
    game->black_pieces = 0ULL;
    game->black_kings = 0ULL;
    game->current_player = 0; // Red starts
    game->game_over = 0;
    
    // Set up red pieces (bottom 3 rows, only dark squares)
    // Rows 0, 1, 2 (positions 0-23)
    for (int pos = 0; pos < 24; pos++) {
        int row = pos / 8;
        int col = pos % 8;
        if ((row + col) % 2 == 1) {  // Dark squares only
            game->red_pieces = SetBit(game->red_pieces, pos);
        }
    }
    
    // Set up black pieces (top 3 rows, only dark squares)
    // Rows 5, 6, 7 (positions 40-63)
    for (int pos = 40; pos < 64; pos++) {
        int row = pos / 8;
        int col = pos % 8;
        if ((row + col) % 2 == 1) {  // Dark squares only
            game->black_pieces = SetBit(game->black_pieces, pos);
        }
    }
}

// Displays the game board with a nice visual layout
void DisplayBoard(GameState* game) {
    printf("\n");
    printf("  ╔═══════════════════════════════╗\n");
    printf("  ║  BITBOARD CHECKERS GAME       ║\n");
    printf("  ╚═══════════════════════════════╝\n");
    printf("\n    0   1   2   3   4   5   6   7\n");
    printf("  ╔═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╗\n");
    
    for (int row = 7; row >= 0; row--) {
        printf("%d ║", row);
        
        for (int col = 0; col < 8; col++) {
            int pos = row * 8 + col;
            int is_dark = (row + col) % 2 == 1;
            
            // Check what piece is at this position
            int has_red = GetBit(game->red_pieces, pos);
            int has_red_king = GetBit(game->red_kings, pos);
            int has_black = GetBit(game->black_pieces, pos);
            int has_black_king = GetBit(game->black_kings, pos);
            
            if (has_red_king) {
                printf(" R̂ ");  // Red King
            } else if (has_red) {
                printf(" r ");   // Red piece
            } else if (has_black_king) {
                printf(" B̂ ");  // Black King
            } else if (has_black) {
                printf(" b ");   // Black piece
            } else if (is_dark) {
                printf(" · ");   // Empty dark square
            } else {
                printf("   ");   // Light square (not playable)
            }
            
            if (col < 7) printf("║");
        }
        
        printf("║ %d\n", row);
        
        if (row > 0) {
            printf("  ╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n");
        }
    }
    
    printf("  ╚═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╝\n");
    printf("    0   1   2   3   4   5   6   7\n\n");
    
    // Display legend
    printf("  Legend: r=Red  R̂=Red King  b=Black  B̂=Black King  ·=Empty\n");
    printf("  Current Player: %s\n", game->current_player == 0 ? "RED" : "BLACK");
    printf("  Red Pieces: %d  Black Pieces: %d\n", 
           CountBits(game->red_pieces | game->red_kings),
           CountBits(game->black_pieces | game->black_kings));
}

// Converts row and column to bit position
int GetPosition(int row, int col) {
    return row * 8 + col;
}

// Checks if a position is valid and on a dark square
int IsValidPosition(int row, int col) {
    if (row < 0 || row >= 8 || col < 0 || col >= 8) return 0;
    return (row + col) % 2 == 1;  // Must be a dark square
}