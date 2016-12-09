#pragma once
#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

// Substitutions to maintain UnrealEngine compatability.
using FString = std::string;
using int32 = int;

struct Analysis
{
    FString sLetterHint = "";
    FString sPositionHint = "";
    int32 iLetterMatches = 0;
    int32 iPositionMatches = 0;
};

// CLASS IsogramGame -- Functions that manage the core of the Isogram Game.
class IsogramGame {
    std::mt19937 Entropy = std::mt19937{ std::random_device{}() };

public:
    IsogramGame(); // Constructor
    bool bDisplayHints;

    Analysis AnalyzeGuess(FString);
    bool bIsGuessMatch() const;
    bool bIsIsogram(FString);
    FString sGetIsogram() const;
    FString sSelectIsogram(int);
    FString sStringToLower(FString);
    int32 iGetCurrentGuessNum() const;
    int32 iGetIsogramLength() const;
    int32 iGetLossCount() const;
    int32 iGetPhaseScore() const;
    int32 iGetRunningScore() const;
    int32 iGetMaxGuesses() const;
    int32 iGetChallengeSize() const;
    int32 iGetWinCount() const;
    int32 zGetDifficulty() const;
    void IncrementGuess();
    void IncrementLoss();
    void Reset();
    void SetEasy();
    void SetHard();
    void SetNormal();
    void Tally();

// See IsogramGame::IsogramGame() definition for initialization. [found in IsogramGame.cpp]
private:
    bool bDoesGuessMatch;
    bool bInitialized;
    bool bValidated;
    bool bValidDictionary;
    FString sIsogram;
    int32 iCurrentGuess;
    int32 iLossCount;
    int32 iMaxGuesses;
    int32 iPhaseScore;
    int32 iRunningScore;
    int32 iWinCount;
    int32 zMode; // TODO re-code with more readabilty?
};

// CLASS LetterBox -- Container to store characters submitted during a round of play.
class LetterBox {
public:
    FString sGetLetters() const;
    void Reset();
    void SubmitLetter(char);
private:
    FString sBoxOfLetters;
};
