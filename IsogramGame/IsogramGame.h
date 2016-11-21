#pragma once

// CLASS IsogramGame -- functions that manage the core of the Isogram Game
//this class does not need to be named the same as the .cpp file.....
//this file may also contain more than one class.
class IsogramGame {
public:
    void Reset(); // TODO enhanced return value, i.e. int iWordLength
    void IncrementGuess();
    void EvaluateGuess();
    int iGetMaxGuesses();
    int iGetCurrentGuess();
    bool bGuessSuccess();

    // ignore this area for now.....
private:
    int iCurrentGuess = 1;
    int iMaxGuesses = 4;
};