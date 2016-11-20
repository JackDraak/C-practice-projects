#include "IsogramGame.h"

void IsogramGame::Reset() {};
void IsogramGame::IncrementGuess() { iCurrentGuess++; };
void IsogramGame::EvaluateGuess() {};
int IsogramGame::iGetMaxGuesses() { return IsogramGame::iMaxGuesses; };
int IsogramGame::iGetCurrentGuess() { return IsogramGame::iCurrentGuess; };
bool IsogramGame::bGuessSuccess() { return false; };
