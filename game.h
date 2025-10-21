#ifndef GAME_H
#define GAME_H

#include "board.h"

// Helper functions
int IsOwnPiece(GameState* game, int position);
int IsOpponentPiece(GameState* game, int position);
int IsEmpty(GameState* game, int position);
int IsKing(GameState* game, int position);

// Game logic functions
int MakeMove(GameState* game, int from_row, int from_col, int to_row, int to_col);
void MovePiece(GameState* game, int from_pos, int to_pos);
void CapturePiece(GameState* game, int from_pos, int to_pos, int capture_pos);
int CheckWinCondition(GameState* game);
void SwitchPlayer(GameState* game);

// Save/Load functionality
int SaveGame(GameState* game, const char* filename);
int LoadGame(GameState* game, const char* filename);

#endif // GAME_H