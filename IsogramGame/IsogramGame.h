#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct Analysis
{
    int32 iLetterMatches = 0;
    int32 iPositionMatches = 0;
    FString sHint = "";
    bool bDoesGuessMatchIsogram = false;
};

// CLASS IsogramGame -- functions that manage the core of the Isogram Game
class IsogramGame {
public:
    IsogramGame(); // constructor 

    Analysis AnalyzeGuess(FString);
    FString sGetIsogram() const;
    FString SelectIsogram();
    int32 iGetCurrentGuess() const;
    int32 iGetIsogramLength() const;
    int32 iGetMaxGuesses() const;
    void IncrementGuess();
    void Reset();
    bool bGetGuessMatch() const;

    // see IsogramGame::IsogramGame() definition for initialization [found in IsogramGame.cpp]
private:
    bool bGuessMatch;
    bool bInitialized;
    FString sIsogram;
    int32 iCurrentGuess;
    int32 iLossCount;
    int32 iMaxGuesses;
    int32 iScore;
    int32 iWinCount;
};
