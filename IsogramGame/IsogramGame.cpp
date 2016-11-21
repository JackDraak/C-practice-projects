#include "IsogramGame.h"

void IsogramGame::IncrementGuess()          { iCurrentGuess++; }
void IsogramGame::EvaluateGuess() const     { return; } // TODO code this
int IsogramGame::iGetMaxGuesses() const     { return iMaxGuesses; }
int IsogramGame::iGetCurrentGuess() const   { return iCurrentGuess; }
int IsogramGame::iGetIsogramLength() const  { return iIsogramLength; }
bool IsogramGame::bIsIsogramRevealed() const { return false; } // TODO code this


IsogramGame::IsogramGame()
{
    iMaxGuesses = 4;
    Reset();
}

void IsogramGame::Reset()
{
    if (!bInitialized) 
    {
        bInitialized = true;
        iScore = 0;
        iWinCount = 0;
        iLossCount = 0;
    }
    iCurrentGuess = 1;
    // build and call function to select new isogram
    iIsogramLength = 6; // TODO make this what it says it is
    return;
}
