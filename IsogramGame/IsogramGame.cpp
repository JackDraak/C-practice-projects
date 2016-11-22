#include<string>
#include<iostream>
#include "IsogramGame.h"

using int32 = int;

eGuessValidation IsogramGame::ValidateGuess(FString sGuess) const 
{
    // TODO 1st priority
    if (!bIsAlpha(sGuess))                      { return eGuessValidation::Not_Alpha; }
    if (!bIsIsogram(sGuess))                    { return eGuessValidation::Not_Isogram; }
    std::cout << "\nDEBUG: " << sIsogram << " " << sIsogram.length(); // DEBUG
    if (sGuess.length() > sIsogram.length())    { return eGuessValidation::Too_Long; }
    if (sGuess.length() < sIsogram.length())    { return eGuessValidation::Too_Short; }
    return eGuessValidation::Okay; // default return
}

int32 IsogramGame::iGetCurrentGuess() const     { return iCurrentGuess; }
int32 IsogramGame::iGetIsogramLength() const    { return sIsogram.length(); }
int32 IsogramGame::iGetMaxGuesses() const       { return iMaxGuesses; }
void IsogramGame::IncrementGuess()              { iCurrentGuess++; }

IsogramGame::IsogramGame()
{
    iMaxGuesses = 4;
    Reset();
}

bool IsogramGame::bIsAlpha(FString sTestString) const // TODO finish test
{
    int iLength = sTestString.length();
    for (int i = 0; i < iLength; i++)
    {
        if (!isalpha(sTestString[i])) return false;
    }
    return true;
}

bool IsogramGame::bIsIsogram(FString sTestString) const // TODO finish test
{
    int iLength = sTestString.length();
    for (int i = 0; i < iLength; i++) 
    {
        for (int j = 0; j < iLength; j++)
        {
            if (sTestString[i] == sTestString[j]) { return false; }
        }
    }
    return true;
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
        analysis.bDoesGuessMatchIsogram = true; 
    } else {
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
    iCurrentGuess = 1;
    sIsogram = SelectIsogram();
    return;
}
