#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "bitops.h"
#include "board.h"

/**
 * Checks if a square is occupied by the current player
 * @param game Pointer to game state
 * @param position Bit position to check
 * @return 1 if occupied by current player, 0 otherwise
 */
int IsOwnPiece(GameState* game, int position) {
    if (game->current_player == 0) {  // Red
        return GetBit(game->red_pieces | game->red_kings, position);
    } else {  // Black
        return GetBit(game->black_pieces | game->black_kings, position);
    }
}

/**
 * Checks if a square is occupied by the opponent
 * @param game Pointer to game state
 * @param position Bit position to check
 * @return 1 if occupied by opponent, 0 otherwise
 */
int IsOpponentPiece(GameState* game, int position) {
    if (game->current_player == 0) {  // Red player, check for black
        return GetBit(game->black_pieces | game->black_kings, position);
    } else {  // Black player, check for red
        return GetBit(game->red_pieces | game->red_kings, position);
    }
}

/**
 * Checks if a position is empty
 * @param game Pointer to game state
 * @param position Bit position to check
 * @return 1 if empty, 0 otherwise
 */
int IsEmpty(GameState* game, int position) {
    unsigned long long all_pieces = game->red_pieces | game->red_kings | 
                                    game->black_pieces | game->black_kings;
    return !GetBit(all_pieces, position);
}

/**
 * Checks if a piece at a position is a king
 * @param game Pointer to game state
 * @param position Bit position to check
 * @return 1 if king, 0 otherwise
 */
int IsKing(GameState* game, int position) {
    return GetBit(game->red_kings | game->black_kings, position);
}

/**
 * Validates and executes a move
 * @param game Pointer to game state
 * @param from_row Starting row
 * @param from_col Starting column
 * @param to_row Destination row
 * @param to_col Destination column
 * @return 1 if move successful, 0 otherwise
 */
int MakeMove(GameState* game, int from_row, int from_col, int to_row, int to_col) {
    // Validate positions
    if (!IsValidPosition(from_row, from_col) || !IsValidPosition(to_row, to_col)) {
        printf("Invalid position! Must be on dark squares.\n");
        return 0;
    }
    
    int from_pos = GetPosition(from_row, from_col);
    int to_pos = GetPosition(to_row, to_col);
    
    // Check if from position has current player's piece
    if (!IsOwnPiece(game, from_pos)) {
        printf("No piece at that position or not your piece!\n");
        return 0;
    }
    
    // Check if destination is empty
    if (!IsEmpty(game, to_pos)) {
        printf("Destination is not empty!\n");
        return 0;
    }
    
    int row_diff = to_row - from_row;
    int col_diff = abs(to_col - from_col);
    int is_king_piece = IsKing(game, from_pos);
    
    // Validate move direction for non-kings
    if (!is_king_piece) {
        if (game->current_player == 0 && row_diff <= 0) {  // Red moves up
            printf("Regular red pieces must move forward (up)!\n");
            return 0;
        }
        if (game->current_player == 1 && row_diff >= 0) {  // Black moves down
            printf("Regular black pieces must move forward (down)!\n");
            return 0;
        }
    }
    
    // Check if it's a simple move (1 square diagonally)
    if (abs(row_diff) == 1 && col_diff == 1) {
        // Simple move - just move the piece
        MovePiece(game, from_pos, to_pos);
        return 1;
    }
    
    // Check if it's a capture move (2 squares diagonally)
    if (abs(row_diff) == 2 && col_diff == 2) {
        // Calculate middle position (the captured piece)
        int mid_row = (from_row + to_row) / 2;
        int mid_col = (from_col + to_col) / 2;
        int mid_pos = GetPosition(mid_row, mid_col);
        
        // Check if there's an opponent piece to capture
        if (!IsOpponentPiece(game, mid_pos)) {
            printf("No opponent piece to capture!\n");
            return 0;
        }
        
        // Perform capture
        CapturePiece(game, from_pos, to_pos, mid_pos);
        return 1;
    }
    
    printf("Invalid move! Pieces move diagonally 1 or 2 squares.\n");
    return 0;
}

// Moves a piece from one position to another
void MovePiece(GameState* game, int from_pos, int to_pos) {
    int is_king_piece = IsKing(game, from_pos);
    
    if (game->current_player == 0) {  // Red
        if (is_king_piece) {
            game->red_kings = ClearBit(game->red_kings, from_pos);
            game->red_kings = SetBit(game->red_kings, to_pos);
        } else {
            game->red_pieces = ClearBit(game->red_pieces, from_pos);
            game->red_pieces = SetBit(game->red_pieces, to_pos);
        }
        
        // Check for king promotion (reaching row 7)
        if (to_pos >= 56 && !is_king_piece) {
            game->red_pieces = ClearBit(game->red_pieces, to_pos);
            game->red_kings = SetBit(game->red_kings, to_pos);
            printf("🎉 Red piece promoted to KING! 🎉\n");
        }
    } else {  // Black
        if (is_king_piece) {
            game->black_kings = ClearBit(game->black_kings, from_pos);
            game->black_kings = SetBit(game->black_kings, to_pos);
        } else {
            game->black_pieces = ClearBit(game->black_pieces, from_pos);
            game->black_pieces = SetBit(game->black_pieces, to_pos);
        }
        
        // Check for king promotion (reaching row 0)
        if (to_pos < 8 && !is_king_piece) {
            game->black_pieces = ClearBit(game->black_pieces, to_pos);
            game->black_kings = SetBit(game->black_kings, to_pos);
            printf("🎉 Black piece promoted to KING! 🎉\n");
        }
    }
}

// Captures an opponent piece
void CapturePiece(GameState* game, int from_pos, int to_pos, int capture_pos) {
    // Remove the captured piece
    if (game->current_player == 0) {  // Red capturing black
        game->black_pieces = ClearBit(game->black_pieces, capture_pos);
        game->black_kings = ClearBit(game->black_kings, capture_pos);
    } else {  // Black capturing red
        game->red_pieces = ClearBit(game->red_pieces, capture_pos);
        game->red_kings = ClearBit(game->red_kings, capture_pos);
    }
    
    // Move the capturing piece
    MovePiece(game, from_pos, to_pos);
    
    printf("💥 Piece captured! 💥\n");
}

// Checks if the current player has won
int CheckWinCondition(GameState* game) {
    int red_count = CountBits(game->red_pieces | game->red_kings);
    int black_count = CountBits(game->black_pieces | game->black_kings);
    
    if (red_count == 0) {
        printf("\n");
        printf("  ╔═══════════════════════════════════════╗\n");
        printf("  ║                                       ║\n");
        printf("  ║          🏆 BLACK WINS! 🏆           ║\n");
        printf("  ║                                       ║\n");
        printf("  ║      CONGRATULATIONS BLACK PLAYER!    ║\n");
        printf("  ║                                       ║\n");
        printf("  ╚═══════════════════════════════════════╝\n");
        printf("\n");
        game->game_over = 1;
        return 1;
    }
    
    if (black_count == 0) {
        printf("\n");
        printf("  ╔═══════════════════════════════════════╗\n");
        printf("  ║                                       ║\n");
        printf("  ║           🏆 RED WINS! 🏆            ║\n");
        printf("  ║                                       ║\n");
        printf("  ║       CONGRATULATIONS RED PLAYER!     ║\n");
        printf("  ║                                       ║\n");
        printf("  ╚═══════════════════════════════════════╝\n");
        printf("\n");
        game->game_over = 1;
        return 1;
    }
    
    return 0;
}

// Switches to the other player
void SwitchPlayer(GameState* game) {
    game->current_player = 1 - game->current_player;
}

// Saves the current game state to a file
int SaveGame(GameState* game, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file for saving!\n");
        return 0;
    }
    
    // Write header
    fprintf(file, "# BitBoard Checkers Save File\n");
    fprintf(file, "# Format: bitboard values in hexadecimal\n\n");
    
    // Write game state
    fprintf(file, "RED_PIECES=%016llX\n", game->red_pieces);
    fprintf(file, "RED_KINGS=%016llX\n", game->red_kings);
    fprintf(file, "BLACK_PIECES=%016llX\n", game->black_pieces);
    fprintf(file, "BLACK_KINGS=%016llX\n", game->black_kings);
    fprintf(file, "CURRENT_PLAYER=%d\n", game->current_player);
    fprintf(file, "GAME_OVER=%d\n", game->game_over);
    
    fclose(file);
    printf("✓ Game saved successfully to '%s'\n", filename);
    return 1;
}

// Loads a game state from a file
int LoadGame(GameState* game, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file for loading!\n");
        return 0;
    }
    
    char line[256];
    int loaded_fields = 0;
    
    while (fgets(line, sizeof(line), file)) {
        // Skip comments and empty lines
        if (line[0] == '#' || line[0] == '\n') continue;
        
        // Parse each field
        if (sscanf(line, "RED_PIECES=%llX", &game->red_pieces) == 1) {
            loaded_fields++;
        } else if (sscanf(line, "RED_KINGS=%llX", &game->red_kings) == 1) {
            loaded_fields++;
        } else if (sscanf(line, "BLACK_PIECES=%llX", &game->black_pieces) == 1) {
            loaded_fields++;
        } else if (sscanf(line, "BLACK_KINGS=%llX", &game->black_kings) == 1) {
            loaded_fields++;
        } else if (sscanf(line, "CURRENT_PLAYER=%d", &game->current_player) == 1) {
            loaded_fields++;
        } else if (sscanf(line, "GAME_OVER=%d", &game->game_over) == 1) {
            loaded_fields++;
        }
    }
    
    fclose(file);
    
    if (loaded_fields == 6) {
        printf("✓ Game loaded successfully from '%s'\n", filename);
        return 1;
    } else {
        printf("Error: Invalid save file format!\n");
        return 0;
    }
}