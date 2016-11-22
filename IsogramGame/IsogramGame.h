#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// CLASS IsogramGame -- functions that manage the core of the Isogram Game
class IsogramGame {
public:
    IsogramGame(); // constructor 

    bool bIsIsogramRevealed() const;
    void Reset();
    void EvaluateGuess() const;
    void IncrementGuess();
    int32 iGetCurrentGuess() const;
    int32 iGetIsogramLength() const;
    int32 iGetMaxGuesses() const;
    //NewType ScoreValidGuess();
    FString SelectIsogram();

    // see IsogramGame::IsogramGame() definition for initialization
private:
    int32 iCurrentGuess;
    int32 iMaxGuesses;
    int32 iIsogramLength;
    int32 iScore;
    int32 iWinCount;
    int32 iLossCount;
    bool bInitialized;
    FString sIsogram;
};
