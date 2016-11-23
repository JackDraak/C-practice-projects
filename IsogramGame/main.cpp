/*
Isogram Game
based on https://www.udemy.com/unrealcourse/ by Ben Tristem (Thanks, Ben!)
coded by Jack Draak

A rudimentary console-based application used in learning about C++, which
acts as the view in an MVC pattern and is responsible for all user interaction.
Game logic operates from IsogramGame.cpp
*/

#include <iostream>
#include <string>
#include "IsogramGame.h"

using FText = std::string;
using int32 = int;

enum class eGuessValidation
{
    Not_Alpha,
    Not_Isogram,
    Too_Long,
    Too_Short,
    Okay
};

// -- Function prototypes follow:
eGuessValidation ValidateGuess(FString);
bool bIsAlpha(FString);
bool bIsIsogram(FString);
bool bContinuePlaying();
void PlayGame();
void PrintIntro();
FText GetGuess();

// instantiate an object of the Isogramgame class named: ActiveGame
IsogramGame ActiveGame;

// -- Application entry-point
int main()
{
    PrintIntro();
    do { PlayGame(); } while (bContinuePlaying());
    return 0;
}

// -- Method implementations follow:

void PlayGame()
{
    int32 cMaxGuesses = ActiveGame.iGetMaxGuesses();
    FText sGuess = "";

    // TODO use while once validating input
    for (int32 i = 1; i <= cMaxGuesses; i++)
    {
        sGuess = GetGuess(); // TODO validate input
        Analysis analysis = ActiveGame.AnalyzeGuess(sGuess);
        // TODO enhance printed results of the guess
        std::cout << "\nCorrect letters in the wrong position(s): " << analysis.iLetterMatches;
        std::cout << "\nCorrect letters in the proper position(s): " << analysis.iPositionMatches;
    }
    // TODO summarize game phase
}

bool bIsAlpha(FString sTestString) // TODO finish test
{
    int iLength = sTestString.length();
    for (int i = 0; i < iLength; i++)
    {
        if (!isalpha(sTestString[i])) return false;
    }
    return true;
}

bool bIsIsogram(FString sTestString) // TODO finish test
{
    int iLength = sTestString.length();
    for (int i = 0; i < iLength; i++)
    {
        for (int j = 0; j < iLength; j++)
        {
            if (sTestString[i] == sTestString[j]) { return false; }
        }
    }
    return true;
}

bool bContinuePlaying()
{
    std::cout << "\nWould you like to continue playing? (y/n) ";
    FText sResponce = "";
    getline(std::cin, sResponce);
    if ((sResponce[0] == 'y') || (sResponce[0] == 'Y')) 
    {
        ActiveGame.Reset();
        return true;
    }
    return false; 
}

void PrintIntro()
{
    int32 iWordLen = ActiveGame.iGetIsogramLength();
    std::cout << "\n\nINTRO: Thank you for playing my \'Guess the Isogram\' console game!\n";
    std::cout << " - what is an isogram?\n";
    std::cout << " - how do I play?\n\n";
    std::cout << "...details, detials... We'll get to that later!\n";
    std::cout << "Can you guess the " << iWordLen << " letter isogram that has been randomly pre-selected?";
}

FText GetGuess()
{
  //  EGuessQuality Status = EGuessQuality::Invalid_Status;
    FText sGuess = "";
   // do {
        std::cout << "\nPlease, enter your guess (#" << ActiveGame.iGetCurrentGuess() << ") now: ";
        getline(std::cin, sGuess);
     //   ActiveGame.IsogramGame::AnalyzeGuess(sGuess);
    // } while (IsogramGame::ValidateGuess(sGuess));

    FText Valid_Guess = sGuess; // TODO implement validation
    ActiveGame.IncrementGuess();
    return Valid_Guess;
}
/*
// Provide meaningful feedback if the guess is invalid:
Status = BCGame.CheckGuessValidity(Guess);
switch (Status)
{
case EGuessQuality::Length_Mismatch:
    std::cout << "\nOops, that won't work! `" << Guess << "` has " << Guess.length() << " letters.\n";
    break;

    */

eGuessValidation ValidateGuess(FString sGuess)
{
    FString sIsogram = ActiveGame.sGetIsogram();
    // TODO 1st priority
    if (!bIsAlpha(sGuess)) { return eGuessValidation::Not_Alpha; }
    if (!bIsIsogram(sGuess)) { return eGuessValidation::Not_Isogram; }
    std::cout << "\nDEBUG: " << sIsogram << " " << sIsogram.length(); // Output for DEBUG
    if (sGuess.length() > sIsogram.length()) { return eGuessValidation::Too_Long; }
    if (sGuess.length() < sIsogram.length()) { return eGuessValidation::Too_Short; }
    return eGuessValidation::Okay; // default return
}
