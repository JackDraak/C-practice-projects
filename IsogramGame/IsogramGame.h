#pragma once

// CLASS IsogramGame -- functions that manage the core of the Isogram Game
class IsogramGame {
public:
    IsogramGame(); // constructor 

    bool bIsIsogramRevealed() const;
    void Reset();
    void EvaluateGuess() const;
    void IncrementGuess();
    int iGetCurrentGuess() const;
    int iGetIsogramLength() const;
    int iGetMaxGuesses() const;
    //NewType ScoreValidGuess();
    std::string SelectIsogram();

    // see IsogramGame::IsogramGame() definition for initialization
private:
    int iCurrentGuess;
    int iMaxGuesses;
    int iIsogramLength;
    int iScore;
    int iWinCount;
    int iLossCount;
    bool bInitialized;
    std::string sIsogram;
};
