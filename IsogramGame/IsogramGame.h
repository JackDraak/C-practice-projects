#pragma once

// CLASS IsogramGame -- functions that manage the core of the Isogram Game
//this class does not need to be named the same as the .cpp file.....
//this file may also contain more than one class.
class IsogramGame {
public:
    IsogramGame(); // constructor 

    void Reset();
    void IncrementGuess();
    void EvaluateGuess() const;
    int iGetMaxGuesses() const;
    int iGetCurrentGuess() const;
    bool bIsIsogramRevealed() const;
    //NewType ScoreValidGuess();

    // see constructor for initialization
private:
    int iCurrentGuess;
    int iMaxGuesses;
};