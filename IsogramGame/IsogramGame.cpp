#include<string>
#include "IsogramGame.h"

using int32 = int;

// bool IsogramGame::bIsIsogramRevealed() const    { return ; } 
int32 IsogramGame::iGetCurrentGuess() const     { return iCurrentGuess; }
int32 IsogramGame::iGetIsogramLength() const    { return sIsogram.length(); }
int32 IsogramGame::iGetMaxGuesses() const       { return iMaxGuesses; }
void IsogramGame::IncrementGuess()              { iCurrentGuess++; }

IsogramGame::IsogramGame()
{
    iMaxGuesses = 4;
    Reset();
}

Analysis IsogramGame::AnalyzeGuess(FString sGuess)
{
    Analysis analysis; // setup return variable
    int32 iIsogramLength = sIsogram.length();

    for (int32 GuessLetter = 0; GuessLetter < iIsogramLength; GuessLetter++) {
        for (int32 IsogramLetter = 0; IsogramLetter < iIsogramLength; IsogramLetter++) {
            if (sGuess[GuessLetter] == sIsogram[IsogramLetter]) {
                if (GuessLetter == IsogramLetter) 
                {
                    analysis.iPositionMatches++; // TODO score
                }
                else // implicit: if (iGuessLetter != iIsogramLetter) {
                { 
                    analysis.iLetterMatches++; // TODO score
                }
            }
        }
    }

    if (analysis.iPositionMatches == iIsogramLength) 
    {
        // TODO need to settle on one of these rather than doing both....
  //      bIsIsogramMatched = true;
        analysis.bDoesGuessMatchIsogram = true;
        
    }
    else {
        // TODO need to settle on one of these rather than doing both....
  //      bIsIsogramMatched = false;
        analysis.bDoesGuessMatchIsogram = false;
    }
    return analysis;
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
        iLossCount = 0;
        iScore = 0;
        iWinCount = 0;
    }
//    bIsIsogramMatched = false;
    iCurrentGuess = 1;
    sIsogram = SelectIsogram();
    return;
}
