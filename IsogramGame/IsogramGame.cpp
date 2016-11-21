#include "IsogramGame.h"

void IsogramGame::IncrementGuess()          { iCurrentGuess++; }
void IsogramGame::EvaluateGuess() const     { return; }
int IsogramGame::iGetMaxGuesses() const     { return iMaxGuesses; }
int IsogramGame::iGetCurrentGuess() const   { return iCurrentGuess; }
bool IsogramGame::bIsIsogramRevealed() const { return false; }

IsogramGame::IsogramGame()
{
    Reset();
}

void IsogramGame::Reset()
{
    iCurrentGuess = 1;
    iMaxGuesses = 4;
    return;
}