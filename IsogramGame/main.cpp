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


// ----- Function prototypes follow ----- //

eGuessValidation ValidateGuess(FString);
bool bIsAlpha(FString);
bool bIsIsogram(FString);
bool bContinuePlaying();
void PlayGame();
void PrintIntro();
FString sGetValidGuess();
FString sStringToLower(FString);

// instantiate an object of the IsogramGame class named: ActiveGame
IsogramGame ActiveGame;


// ----- Application entry-point ----- //

int main()
{
    PrintIntro();
    do { PlayGame(); } while (bContinuePlaying());
    return 0;
}

// ----- Method implementations follow ----- //

void PlayGame()
{
    int32 cMaxGuesses = ActiveGame.iGetMaxGuesses();
    FString sGuess = "";

    for (int32 i = 1; i <= cMaxGuesses; i++)
    {
        sGuess = sGetValidGuess();
        sGuess = sStringToLower(sGuess);
        Analysis analysis = ActiveGame.AnalyzeGuess(sGuess);
        if (analysis.bDoesGuessMatchIsogram) { break; }
        ActiveGame.IncrementGuess();

        // ----- Output phase (turn) results ----- //
        std::cout << "\nCorrect letters in the wrong position(s): " << analysis.iLetterMatches;
        std::cout << "\nCorrect letters in the proper position(s): " << analysis.iPositionMatches;
    }

    // ----- Output round results ----- //
    std::cout << "\nCongratulations! You guessed the secret isogram: " << ActiveGame.sGetIsogram() << ".";
    std::cout << "\nIt took you " << ActiveGame.iGetCurrentGuess() << " guesses!";
    return;
}

FString sStringToLower(FString convertString)
{
    int iLength = convertString.length();
    for (int i = 0; i < iLength; i++) { convertString[i] = tolower(convertString[i]); }
    return convertString;
}

bool bIsAlpha(FString sTestString)
{
    int iLength = sTestString.length();
    for (int i = 0; i < iLength; i++)
    {
        char thisChar = tolower(sTestString[i]);
        if (!(thisChar >= 'a' && thisChar <= 'z')) { return false; } 
    }
    return true;
}

bool bIsIsogram(FString sTestString) // order of sort: (n^2 -n) /2 .. // TODO but can use hash table for order n
{
    int iLength = sTestString.length();
    for (int i = 0; i < iLength; i++) {
        for (int j = 0; j < iLength; j++) {
            if (i != j && sTestString[i] == sTestString[j]) { return false; }
        }
    } return true;
}

bool bContinuePlaying()
{
    std::cout << "\nWould you like to continue playing? (y/n) ";
    FString sResponce = "";
    getline(std::cin, sResponce);
    if ((sResponce[0] == 'y') || (sResponce[0] == 'Y')) {
        ActiveGame.Reset();
        return true;
    } return false; 
}

void PrintIntro()
{
    int32 iWordLen = ActiveGame.iGetIsogramLength();
    std::cout << "\n\nINTRO: Thank you for playing my \'Guess the Isogram\' console game!\n";
    std::cout << " - what is an isogram?\n";
    std::cout << " - how do I play?\n\n";
    std::cout << "...details, detials... We'll get to that later!\n";
    std::cout << "Can you guess the " << iWordLen << " letter isogram that has been randomly pre-selected?";
    return;
}

FString sGetValidGuess()
{
    eGuessValidation Status = eGuessValidation::Invalid_Status;
    FString sGuess = "";

    do {
        std::cout << "\nPlease, enter your guess (#" << ActiveGame.iGetCurrentGuess() << ") now: ";
        getline(std::cin, sGuess);
        Status = ValidateGuess(sGuess);
        switch (Status)
        {
        case eGuessValidation::Not_Alpha:
            std::cout << "\nERROR: Your submission, \"" << sGuess << "\" contains non-alpha input.";
            std::cout << "\nPlease use only letters (this *is* a word-game, y'know! [think Scrabble].)";
            break;
        case eGuessValidation::Not_Isogram:
            std::cout << "\nERROR: Your submission, \"" << sGuess << "\" contains repeated characters.";
            std::cout << "\nPlease enter an isogram (a word comprised of all unique letters,";
            std::cout << "\ni.e.book:NO, but bark : YES.)";
            break;
        case eGuessValidation::Too_Long:
            std::cout << "\nERROR: Your submission, \"" << sGuess << "\" is too long.";
            std::cout << "\nPlease use a " << ActiveGame.iGetIsogramLength() << " - letter word.";
            break;
        case eGuessValidation::Too_Short:
            std::cout << "\nERROR: Your submission, \"" << sGuess << "\" is too short.";
            std::cout << "\nPlease use a " << ActiveGame.iGetIsogramLength() << " - letter word.";
            break;
        case eGuessValidation::Okay:
            std::cout << "\nYour submission was, \"" << sGuess << "\"";
            break;
        default:
            break;
        }
    } while (Status != eGuessValidation::Okay);
    return sGuess;
}

eGuessValidation ValidateGuess(FString sGuess)
{
    FString sIsogram = ActiveGame.sGetIsogram();

    if (!bIsAlpha(sGuess))                          { return eGuessValidation::Not_Alpha; }
    else if (!bIsIsogram(sGuess))                   { return eGuessValidation::Not_Isogram; }
    else if (sGuess.length() < sIsogram.length())   { return eGuessValidation::Too_Short; }
    else if (sGuess.length() > sIsogram.length())   { return eGuessValidation::Too_Long; }
    else                                              return eGuessValidation::Okay;
}
