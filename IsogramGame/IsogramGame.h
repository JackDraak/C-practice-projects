#pragma once
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <time.h>
#include <vector>

// substitutions to maintain UnrealEngine compatability
using FString = std::string;
using int32 = int;

struct Analysis
{
    FString sLetterHint = "";
    FString sPositionHint = "";
    int32 iLetterMatches = 0;
    int32 iPositionMatches = 0;
};

// CLASS IsogramGame -- functions that manage the core of the Isogram Game
class IsogramGame {
public:
    IsogramGame(); // constructor 
    bool bDisplayHints;

    Analysis AnalyzeGuess(FString);
    bool bGetGuessMatch() const;
    FString sGetIsogram() const;
    FString SelectIsogram();
    int32 iGetCurrentGuess() const;
    int32 iGetIsogramLength() const;
    int32 iGetLossCount() const;
    int32 iGetRunningScore() const;
    int32 iGetScore() const;
    int32 iGetMaxGuesses() const;
    int32 iGetWinCount() const;
    void IncrementGuess();
    void IncrementLoss();
    void Reset();
    void Tally();

    // see IsogramGame::IsogramGame() definition for initialization [found in IsogramGame.cpp]
private:
    bool bFirstGuess;
    bool bGuessMatch;
    bool bInitialized;
    bool bValidDictionary;
    FString sIsogram;
    int32 iCurrentGuess;
    int32 iLossCount;
    int32 iMaxGuesses;
    int32 iRunningScore;
    int32 iScore;
    int32 iWinCount;
};

// CLASS LetterBox -- container to store characters submitted during a round of play
class LetterBox {
public:
    FString sGetLetters() const;
    void Reset();
    void SetLetter(char);
private:
    FString sBoxOfLetters;
};
