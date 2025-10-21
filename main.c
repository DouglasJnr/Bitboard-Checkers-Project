#include <stdio.h>
#include <string.h>
#include "bitops.h"
#include "board.h"
#include "game.h"

int main() {
    
    printf("Press Enter to start the game...");
    getchar();
    
    GameState game;
    InitializeGame(&game);
    
    printf("\n╔═══════════════════════════════════════╗\n");
    printf("║  WELCOME TO BITBOARD CHECKERS!       ║\n");
    printf("║                                       ║\n");
    printf("║  Red pieces move UP                   ║\n");
    printf("║  Black pieces move DOWN               ║\n");
    printf("║  Kings can move both directions       ║\n");
    printf("║                                       ║\n");
    printf("║  Commands:                            ║\n");
    printf("║  - Move: row col row col              ║\n");
    printf("║  - Save: save <filename>.sav              ║\n");
    printf("║  - Load: load <filename>.sav              ║\n");
    printf("║  - Quit: quit                         ║\n");
    printf("╚═══════════════════════════════════════╝\n");
    
    while (!game.game_over) {
        DisplayBoard(&game);
        
        char input[100];
        int from_row, from_col, to_row, to_col;
        
        printf("\n%s's turn:\n", game.current_player == 0 ? "RED" : "BLACK");
        printf("Enter move (from_row from_col to_row to_col): ");
        
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        
        // Remove newline
        input[strcspn(input, "\n")] = 0;
        
        // Check for quit command
        if (strcmp(input, "quit") == 0) {
            printf("Thanks for playing!\n");
            break;
        }
        
        // Check for save command
        if (strncmp(input, "save ", 5) == 0) {
            char* filename = input + 5;
            if (strlen(filename) > 0) {
                SaveGame(&game, filename);
            } else {
                printf("Usage: save <filename>\n");
            }
            continue;
        }
        
        // Check for load command
        if (strncmp(input, "load ", 5) == 0) {
            char* filename = input + 5;
            if (strlen(filename) > 0) {
                if (LoadGame(&game, filename)) {
                    printf("Game loaded! Resuming play...\n");
                }
            } else {
                printf("Usage: load <filename>\n");
            }
            continue;
        }
        
        // Parse the input
        if (sscanf(input, "%d %d %d %d", &from_row, &from_col, &to_row, &to_col) != 4) {
            printf("Invalid input! Use format: from_row from_col to_row to_col\n");
            printf("Example: 2 1 3 2\n");
            continue;
        }
        
        // Try to make the move
        if (MakeMove(&game, from_row, from_col, to_row, to_col)) {
            // Check win condition
            if (CheckWinCondition(&game)) {
                DisplayBoard(&game);
                break;
            }
            
            // Switch players
            SwitchPlayer(&game);
        } else {
            printf("Try again!\n");
        }
    }
    
    printf("\nGame Over! Thanks for playing BitBoard Checkers!\n");
    return 0;
}