#include "IsogramGame.h"

void IsogramGame::Reset() {}
void IsogramGame::IncrementGuess() { iCurrentGuess++; }
void IsogramGame::EvaluateGuess() {}
int IsogramGame::iGetMaxGuesses() { return iMaxGuesses; }
int IsogramGame::iGetCurrentGuess() { return iCurrentGuess; }
bool IsogramGame::bGuessSuccess() { return false; }