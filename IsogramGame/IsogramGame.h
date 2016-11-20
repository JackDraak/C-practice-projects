#pragma once
#include <string>

// NewbieNote: this class does not need to be named the same as the .cpp file.....
// (this file may also contain more than one class).

class IsogramGame {

    // constructors
    IsogramGame();

public:
    void Reset(); // TODO enhanced return value, i.e. int iWordLength
    void IncrementGuess();
    void EvaluateGuess();
    int iGetMaxGuesses();
    int iGetCurrentGuessNumber();
    int iGetIsogramLength();
    bool IsGuessMatch();
    std::string SelectIsogram();

    // set values in constructor definition IsogramGame::Reset()

    int iCurrentIsogramLength;
    int iCurrentGuessNumber;
    int iMaxGuesses;
    int iLevel;
    int iWordsMatched;
    int iWordsMismatched;
    int iScore;
    int iLetterOnlyMatches;
    int iLetterPositionMatches;

    std::string sGuess;
    std::string sIsogram;

    bool bNewGameInitialized;
    bool bPlayerGuessMatches;

    bool IsWordAlpha(const std::string&) const;
    bool IsWordIsogram(const std::string&) const;

private:
};