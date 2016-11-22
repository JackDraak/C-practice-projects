#include<string>
#include "IsogramGame.h"

using int32 = int;

void IsogramGame::IncrementGuess()          { iCurrentGuess++; }
void IsogramGame::EvaluateGuess() const     { return; } // TODO code this
int32 IsogramGame::iGetMaxGuesses() const     { return iMaxGuesses; }
int32 IsogramGame::iGetCurrentGuess() const   { return iCurrentGuess; }
int32 IsogramGame::iGetIsogramLength() const  { return iIsogramLength; }
bool IsogramGame::bIsIsogramRevealed() const { return false; } // TODO code this


IsogramGame::IsogramGame()
{
    iMaxGuesses = 4;
    Reset();
}

std::string IsogramGame::SelectIsogram()
{
    return std::string("isogram"); // TODO y'know, more isograms!
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
    sIsogram = SelectIsogram();
    iIsogramLength = sIsogram.length();
    return;
}
