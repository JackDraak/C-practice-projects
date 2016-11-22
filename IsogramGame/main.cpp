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

// -- Function prototypes follow:

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
    // implicit else
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
    FText sGuess = "";
    std::cout << "\nPlease, enter your guess (#" << ActiveGame.iGetCurrentGuess() << ") now: ";
    getline(std::cin, sGuess);
 //   sGuess = sGuess.tolower();
    FText Valid_Guess = sGuess; // TODO implement validation
    ActiveGame.IncrementGuess();
    return Valid_Guess;
}
