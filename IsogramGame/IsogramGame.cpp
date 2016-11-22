#include<string>
#include "IsogramGame.h"

using int32 = int;

void IsogramGame::IncrementGuess()          { iCurrentGuess++; }
void IsogramGame::EvaluateGuess() const     { return; } // TODO code this
int32 IsogramGame::iGetMaxGuesses() const     { return iMaxGuesses; }
int32 IsogramGame::iGetCurrentGuess() const   { return iCurrentGuess; }
int32 IsogramGame::iGetIsogramLength() const  { return iIsogramLength; }
bool IsogramGame::bIsIsogramRevealed() const { return false; } // TODO code this

Analysis IsogramGame::AnalyzeGuess(FString)
{
    // increment turn 
 //   iCurrentGuess++; // why here? was working from main.cpp.. have put it back there for now

    // setup return variable
    Analysis analysis;

    // loop through all letters in the guess
    for (int32 i = 0; i < iIsogramLength; i++) {
        // compare guess letters against isogram letters

            // if they match then
                // increment position matches if apropriate
                // otherwise increment letter matches
    }
    return analysis;
}


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
