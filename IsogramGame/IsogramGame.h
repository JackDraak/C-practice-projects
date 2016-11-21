#pragma once

// CLASS IsogramGame -- functions that manage the core of the Isogram Game
class IsogramGame {
public:
    IsogramGame(); // constructor 

    void Reset();
    void EvaluateGuess() const;
    void IncrementGuess();
    int iGetCurrentGuess() const;
    int iGetIsogramLength() const;
    int iGetMaxGuesses() const;
    bool bIsIsogramRevealed() const;
    //NewType ScoreValidGuess();

    // see constructor for initialization
private:
    int iCurrentGuess;
    int iMaxGuesses;
    int iIsogramLength;
    int iScore;
    int iWinCount;
    int iLossCount;
    bool bInitialized;
};