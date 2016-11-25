/*
Isogram Game
based on https://www.udemy.com/unrealcourse/ by Ben Tristem (Thanks, Ben!)
coded by Jack Draak

A rudimentary console-based application used in learning about C++. Main.cpp, which
acts as the view in an MVC pattern and is responsible for all user interaction also 
utilizes Isogramgame.cpp for game logic operations.

Built in VisualStudio 2015, ostensibly for Windows, but it should be easy to port,
assuming anyone would desire to do so.
*/

#pragma once
#include "IsogramGame.h"

// substitutions to maintain UnrealEngine compatability
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
bool bIsIsogramN(FString);
bool bIsIsogramN2(FString);
bool bContinuePlaying();
int main();
void PlayGame();
void PrintIntro();
FString sGetValidGuess();
FString sStringToLower(FString);

// instantiate an object of the IsogramGame class named: ActiveGame
IsogramGame ActiveGame;

// ----- Application entry-point ----- //

int main()
{
//    ActiveGame.bValidateDictionary();
    PrintIntro();
    do { PlayGame(); } while (bContinuePlaying());
    return 0;
}

// ----- Method implementations follow ----- //

void PlayGame()
{
    srand(unsigned(time(NULL)));
    int32 cMaxGuesses = ActiveGame.iGetMaxGuesses();
    FString sGuess = "";

    for (int32 i = 1; i <= cMaxGuesses; i++)
    {
        sGuess = sGetValidGuess();
        sGuess = sStringToLower(sGuess);
        Analysis analysis = ActiveGame.AnalyzeGuess(sGuess);
        if (ActiveGame.bGetGuessMatch()) { break; } 
        ActiveGame.IncrementGuess();

        // ----- Output phase (turn) results ----- //              admutz

        // TODO track letter's used for the player:  "              a b c d e f g h i j k l m n o p q r s t u v w x y z" 
        //                                           "             |x| |x| |x|x| |x|x| | | |x| | |x| |x| |x|x|x| |x| |x|" a = 16, z = 66
        std::cout << "\n...Correct letters in the wrong place(s): " << analysis.iLetterMatches;
        if (true) { // TODO if hints are enabled, otherwise do not print
            std::random_shuffle(analysis.sLetterHint.begin(), analysis.sLetterHint.end());
            std::cout << ". [shuffled hint: '" << analysis.sLetterHint << "']";
        }
        std::cout << "\n...Correct letters in the proper position(s): " << analysis.iPositionMatches << ".";
        if (true) { // TODO if hints are enabled, otherwise do not print
            std::cout << "      [hint: '" << analysis.sPositionHint << "']";
        }
    }

        // ----- Output round results ----- //
        if (ActiveGame.bGetGuessMatch()) {
            std::cout << "\nCongratulations! You guessed the secret isogram: " << ActiveGame.sGetIsogram() << ".";
            std::cout << "\nIt took you " << ActiveGame.iGetCurrentGuess() << " guesses!";
        }
        else {
            std::cout << "\nBummer! You didn't guess the secret isogram: " << ActiveGame.sGetIsogram() << ".";
            std::cout << "\n(You had " << (ActiveGame.iGetCurrentGuess() - 1) << " guesses.)";
    } return;
}

FString sStringToLower(FString convertString)
{
    int32 iLength = convertString.length();
    for (int32 i = 0; i < iLength; i++) { convertString[i] = tolower(convertString[i]); }
    return convertString;
}

bool bIsAlpha(FString sTestString)
{
    int32 iLength = sTestString.length();
    for (int32 i = 0; i < iLength; i++)
    {
        char thisChar = tolower(sTestString[i]);
        if (!(thisChar >= 'a' && thisChar <= 'z')) { return false; } 
    }
    return true;
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
    std::cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
    std::cout << "\n      INTRO: Thank you for playing my \'Guess the Isogram\' console game!\n";
    std::cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
    std::cout << "\n      - what is an isogram?\n";
    std::cout << "        An isogram is a word comprised of unique letters, for example:\n";
    std::cout << "           - step: is an isogram, each letter is unique in the word\n";
    std::cout << "           - book: is NOT an isogram; it contains two 'o's\n";
    std::cout << "\n";
    std::cout << "         - how do I play?\n\n";
    std::cout << "         ...details, details... We'll get to that!";
    return;
}

FString sGetValidGuess()
{
    eGuessValidation Status = eGuessValidation::Invalid_Status;
    int32 iWordLen = ActiveGame.iGetIsogramLength();
    FString sGuess = "";

    do {
        std::cout << "\n\nCan you guess the " << iWordLen << " letter isogram that has been randomly pre-selected?";
        std::cout << "\nPlease, enter your guess (#" << ActiveGame.iGetCurrentGuess();
        std::cout << " of " << ActiveGame.iGetMaxGuesses() << ") now: ";
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
            std::cout << "\ni.e. book:INVALID, two 'o's, but bark:GREAT!)";
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
    else if (!bIsIsogramN(sGuess))                  { return eGuessValidation::Not_Isogram; }
    else if (sGuess.length() < sIsogram.length())   { return eGuessValidation::Too_Short; }
    else if (sGuess.length() > sIsogram.length())   { return eGuessValidation::Too_Long; }
    else                                              return eGuessValidation::Okay;
}

// Theoretical minimum/maximum itterations: 2-26
bool bIsIsogramN(FString sTestString)
{
    sTestString = sStringToLower(sTestString);
    std::map<char, bool> observedLetter;

    for (auto Letter : sTestString) {
        if (!observedLetter[Letter]) { observedLetter[Letter] = true; }
        else return false;
    } return true;
}

// Depreciated. Historical artifact status granted.
// Theoretical minimum/maximum itterations: 2-702
bool bIsIsogramN2(FString sTestString)
{
    int32 iLength = sTestString.length();
    for (int32 i = 0; i < iLength; i++) {
        for (int32 j = 0; j < iLength; j++) {
            if (i != j && sTestString[i] == sTestString[j]) { return false; }
        }
    } return true;
}
