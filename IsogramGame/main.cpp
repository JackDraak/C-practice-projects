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
    Invalid_Status,
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

    for (int32 i = 1; i <= cMaxGuesses; i++)
    {
        sGuess = GetGuess();
        Analysis analysis = ActiveGame.AnalyzeGuess(sGuess);
        // TODO enhance printed results of the guess
        std::cout << "\nCorrect letters in the wrong position(s): " << analysis.iLetterMatches;
        std::cout << "\nCorrect letters in the proper position(s): " << analysis.iPositionMatches;
    }
    // TODO summarize game phase
}

bool bIsAlpha(FString sTestString)
{
    int iLength = sTestString.length();
    for (int i = 0; i < iLength; i++)
    {
        if (!isalpha(sTestString[i])) { return true; } // TODO obv needs to be false, set TRUE now to move on
    }

    return true;
}

bool bIsIsogram(FString sTestString) // presently broken, as it checks pos 1 vs pos 1, etc.....
{
    int iLength = sTestString.length();
    for (int i = 0; i < iLength; i++)
    {
        for (int j = 0; j < iLength; j++)
        {
            if (sTestString[i] == sTestString[j]) { 
                std::cout << "\nGuessChar " << i << ":" << sTestString[i] << " == GuessChar " << j << ":" << sTestString[j];
                return true; } // TODO obv needs to be false, set TRUE now to move on
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
    eGuessValidation Status = eGuessValidation::Invalid_Status;
    FText sGuess = "";
    do {
        std::cout << "\nPlease, enter your guess (#" << ActiveGame.iGetCurrentGuess() << ") now: ";
        getline(std::cin, sGuess);
        Status = ValidateGuess(sGuess);
        switch (Status)
        {
        case eGuessValidation::Not_Alpha:
            std::cout << "\nERROR: Your submission, \"" << sGuess << "\" contains non-alpha input.";
            break;
        case eGuessValidation::Not_Isogram:
            std::cout << "\nERROR: Your submission, \"" << sGuess << "\" contains repeating characters.";
            break;
        case eGuessValidation::Too_Long:
            std::cout << "\nERROR: Your submission, \"" << sGuess << "\" is too long.";
            std::cout << "\nPlease use a " << ActiveGame.iGetIsogramLength() << " - letter word.";
            break;
        case eGuessValidation::Too_Short:
            std::cout << "\nERROR: Your submission, \"" << sGuess << "\" contains non-alpha input.";
            break;
        case eGuessValidation::Okay:
            std::cout << "\nYour submission was, \"" << sGuess << "\"";
            break;
        }
    } while (Status != eGuessValidation::Okay);
    ActiveGame.IncrementGuess();
    return sGuess;
}

eGuessValidation ValidateGuess(FString sGuess)
{
    FString sIsogram = ActiveGame.sGetIsogram();
    if (!bIsAlpha(sGuess)) { 
        std::cout << "\nbIsAlpha(sGuess) for " << sGuess << " :" << bIsAlpha(sGuess); // DEBUG
        return eGuessValidation::Not_Alpha; 
    }
    else if (sGuess.length() > sIsogram.length()) { 
        std::cout << "\nsGuess.length() for " << sGuess << " :" << sGuess.length(); // DEBUG
        return eGuessValidation::Too_Long; }
    else if (sGuess.length() < sIsogram.length()) { 
        std::cout << "\nsGuess.length() for " << sGuess << " :" << sGuess.length(); // DEBUG
        return eGuessValidation::Too_Short; }
    else if (!bIsIsogram(sGuess)) { 
        std::cout << "\nsbIsIsogram(sGuess) for " << sGuess << " :" << bIsIsogram(sGuess); // DEBUG
        return eGuessValidation::Not_Isogram; }
    else return eGuessValidation::Okay; // default return
}
