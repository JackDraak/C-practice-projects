/*
Isogram Game
based on https://www.udemy.com/unrealcourse/ by Ben Tristem (Thanks, Ben!)
coded by Jack Draak
*/
#include <iostream>
#include <string>
#include "IsogramGame.h"

// function prototypes
bool bContinuePlaying();
void PlayGame();
void PrintGuess(std::string);
void PrintIntro();
std::string GetGuess();

// instantiate an object of the Isogramgame class named: ActiveGame
IsogramGame ActiveGame;

// application entry-point
int main()
{
    PrintIntro();
    do { PlayGame(); } while (bContinuePlaying());
    return 0;
}

// method implenentations
void PlayGame()
{
    int cMaxGuesses = ActiveGame.iGetMaxGuesses();
    std::string sGuess = "";

    // TODO use while once validating input
    for (int i = 1; i <= cMaxGuesses; i++)
    {
        sGuess = GetGuess(); // TODO validate input
        // TODO submit valid guess to game engine
        // TODO print results of the guess
        PrintGuess(sGuess);
        std::cout << std::endl;
    }
    // TODO summarize game phase
}

bool bContinuePlaying()
{
    std::cout << "\nWould you like to continue playing? (y/n) ";
    std::string sResponce = "";
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
    int iWordLen = ActiveGame.iGetIsogramLength();
    std::cout << "\n\nINTRO: Thank you for playing my \'Guess the Isogram\' console game!\n";
    std::cout << " - what is an isogram?\n";
    std::cout << " - how do I play?\n\n";
    std::cout << "...details, detials... We'll get to that later!\n";
    std::cout << "Can you guess the " << iWordLen << " letter isogram that has been randomly pre-selected?";
}

void PrintGuess(std::string sGuess)
{
    std::cout << "\nYour guess was: \"" << sGuess << "\", was it not?";
}

std::string GetGuess()
{
    std::string sGuess = "";
    std::cout << "\nPlease, enter your guess (#" << ActiveGame.iGetCurrentGuess() << ") now: ";
    getline(std::cin, sGuess);
    std::string Valid_Guess = sGuess; // TODO implement validation
    ActiveGame.IncrementGuess();
    return Valid_Guess;
}
