/* 
    Isogram Game
    based on https://www.udemy.com/unrealcourse/ by Ben Tristem (Thanks, Ben!)
    coded by Jack Draak

    requires: 
        main.cpp        - this source code, used for Input/Output with user/console
        IsogramGamne.h  - shared header file
        IsogramGame.cpp - game mechanics source code as a class called IsogramGame
*/
#include <iostream>
#include <string>
#include "IsogramGame.h"

// function prototypes
bool bContinuePlaying();
std::string GetGuess();
void PrintIntro();
void PlayGame();
void PrintGuess(std::string);

IsogramGame LiveGame;

// application entry-point
int main()
{
    PrintIntro();
    do { PlayGame(); } 
    while (bContinuePlaying());
    return 0;
}

void PlayGame()
{
    constexpr int cMaxGuesses = 5;
    std::string sGuess = "";
    for (int i = 1; i <= cMaxGuesses; i++)
    {
        sGuess = GetGuess();
        PrintGuess(sGuess);
        std::cout << std::endl;
    }
}

// method implenentations
bool bContinuePlaying()
{
    std::cout << "\nWould you like to continue playing? (y/n) ";
    std::string sResponce = "";
    getline(std::cin, sResponce);
    if ((sResponce[0] == 'y') || (sResponce[0] == 'Y')) { return true; }
    return false; // implicit else
}

void PrintIntro()
{
    int iWordLen = 9; // TODO iWordLen should be determined based on player level and/or score 
    std::cout << "INTRO: Thank you for playing my \'Guess the Isogram\' console game!\n";
    std::cout << " - what is an isogram?\n";
    std::cout << " - how do I play?\n";
    std::cout << "...details, detials... We'll get to that later!\n\n";
    std::cout << "Can you guess the " << iWordLen << " letter isogram that has been randomly pre-selected?";
    std::cout << std::endl;
}

void PrintGuess(std::string sGuess)
{
    std::cout << "\nYour guess was: " << sGuess << ", was it not?";
    std::cout << std::endl;
}

std::string GetGuess() 
{
    std::string sGuess = "";
    std::cout << "Isogram Length: " << LiveGame.iGetIsogramLength();
    std::cout << ", turn #" << LiveGame.iGetCurrentGuessNumber();
    std::cout << " of " << LiveGame.iGetMaxGuesses();
    std::cout << "Please, enter your guess now: ";
    getline(std::cin, sGuess);
    std::string Valid_Guess = sGuess; // TODO implement validation
    return Valid_Guess;
}
