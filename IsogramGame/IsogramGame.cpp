#include "IsogramGame.h"

void IsogramGame::IncrementGuess()          { IsogramGame::iCurrentGuessNumber++; }
int IsogramGame::iGetMaxGuesses()           { return IsogramGame::iMaxGuesses; }
int IsogramGame::iGetCurrentGuessNumber()   { return IsogramGame::iCurrentGuessNumber; }
int IsogramGame::iGetIsogramLength()        { return IsogramGame::iCurrentIsogramLength; }

bool IsogramGame::IsWordAlpha(const std::string &) const    { return false; }
bool IsogramGame::IsWordIsogram(const std::string &) const  { return false; }
bool IsogramGame::IsGuessMatch()                            { return false; }

std::string IsogramGame::SelectIsogram()
{
    return std::string("isogram");
}

void IsogramGame::EvaluateGuess() {
    // perform scoring:
    // compare guess with isogram
    // correct letters are worth 1 point
    // if the letter is also in the correct position it is worth 3 points
    // provide facility to inform which letters scored points (here?)
}
 
void IsogramGame::Reset() {
    if (!IsogramGame::bNewGameInitialized) {
        IsogramGame::iMaxGuesses = 5;
        IsogramGame::iLevel = 1;
        IsogramGame::iScore = 0;
        IsogramGame::bNewGameInitialized = true;
    }
        std::string sIsogram = SelectIsogram();
        IsogramGame::iCurrentIsogramLength = IsogramGame::iGetIsogramLength();
        std::string sGuess = "";
        int iCurrentGuessNumber = 1;
}

