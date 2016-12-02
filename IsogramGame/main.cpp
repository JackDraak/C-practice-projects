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

enum class eGuessValidation
{
    Invalid_Status,
    Not_Alpha,
    Not_Isogram,
    Too_Long,
    Too_Short,
    Okay
};

// ----- Function prototypes ----- //

eGuessValidation ValidateGuess(FString);
bool bContinuePlaying();
bool bIsAlpha(FString);
int main();
void PlayGame();
void PrintIntro();
FString sGetValidGuess();
FString sStringToLower(FString); // TODO ditch this

// instantiate objects (ActiveGame & ActiveLetterBox) for manipulation
IsogramGame ActiveGame;
LetterBox ActiveLetterBox;

int main()
{
    PrintIntro();
    do { PlayGame(); } while (bContinuePlaying());
    return 0;
}

// ----- Method implementations ----- //

void PlayGame()
{
    ActiveLetterBox.Reset();
    srand(unsigned(time(NULL)));
    int32 cMaxGuesses = ActiveGame.iGetMaxGuesses();
    FString sGuess = "";

    for (int32 i = 1; i <= cMaxGuesses; i++)
    {
        sGuess = sGetValidGuess(); 
        sGuess = sStringToLower(sGuess); // TODO replace function
        int32 guessLength = sGuess.length();

        for (int32 i = 0; i < guessLength; i++ ) { ActiveLetterBox.SetLetter(sGuess[i]); }
        Analysis analysis = ActiveGame.AnalyzeGuess(sGuess);
        if (ActiveGame.bGetGuessMatch()) { break; } 
        ActiveGame.IncrementGuess();

        // ----- Output phase (turn) results ----- //

        std::cout << "\nComplement of letters used this round: " << ActiveLetterBox.sGetLetters();
        std::cout << "\n...Correct letters in the wrong place(s): " << analysis.iLetterMatches;
        if (ActiveGame.bDisplayHints) 
        {
            std::random_shuffle(analysis.sLetterHint.begin(), analysis.sLetterHint.end());
            std::cout << "  [shuffled hint: '" << analysis.sLetterHint << "']";
        }
        std::cout << "\n...Correct letters in the proper position(s): " << analysis.iPositionMatches;
        if (ActiveGame.bDisplayHints) 
        {
            std::cout << "       [hint: '" << analysis.sPositionHint << "']";
        }
    }
        // ----- Output round results ----- //
        
        if (ActiveGame.bGetGuessMatch()) {
            std::cout << "\nCongratulations! You guessed ";
        }
        else {
            ActiveGame.IncrementLoss();
            std::cout << "\nBummer! You didn't guess ";
        }
        std::cout<< "the secret isogram : " << ActiveGame.sGetIsogram() << ".";
        std::cout << "\nIt took you " << ActiveGame.iGetCurrentGuess() << " guesses, earning you ";
        std::cout << ActiveGame.iGetScore() << " points.";
        ActiveGame.Tally();
        std::cout << "\nSCORE: " << ActiveGame.iGetRunningScore() << " (win/loss ";
        std::cout << ActiveGame.iGetWinCount() << "/" << ActiveGame.iGetLossCount() << ")";
        ActiveLetterBox.Reset(); 
        return;
}

bool bContinuePlaying()
{
    bool bContinue = true;
    do {
        FString sResponce = "";
        std::cout << "\nPlease enter (P)lay again, toggle (H)ints ";
        if (ActiveGame.bDisplayHints) { std::cout << "off"; } else { std::cout << "on"; }
        std::cout << ", (R)epeat intro, or (Q)uit...";
        getline(std::cin, sResponce);

        if ((sResponce[0] == 'h') || (sResponce[0] == 'H')) { ActiveGame.bDisplayHints = !ActiveGame.bDisplayHints; }
        else if ((sResponce[0] == 'q') || (sResponce[0] == 'Q')) { bContinue = false; break; }
        else if ((sResponce[0] == 'p') || (sResponce[0] == 'P')) { ActiveGame.Reset(); break; }
        else if ((sResponce[0] == 'r') || (sResponce[0] == 'R')) { PrintIntro(); }
    } while (true);
    if (bContinue) { return true; } else { return false; }
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
    std::cout << "      - how do I play?\n";
    std::cout << "        ...details, details... We'll get to that!";
    return;
}

FString sGetValidGuess()
{
    eGuessValidation status = eGuessValidation::Invalid_Status;
    int32 iWordLen = ActiveGame.iGetIsogramLength();
    FString sGuess = "";

    do {
        std::cout << "\n\nCan you guess the " << iWordLen << " letter isogram that has been randomly pre-selected?";
        std::cout << "\nPlease, enter your guess (#" << ActiveGame.iGetCurrentGuess();
        std::cout << " of " << ActiveGame.iGetMaxGuesses() << ") now: ";
        getline(std::cin, sGuess);

        status = ValidateGuess(sGuess);
        switch (status)
        {
        case eGuessValidation::Not_Alpha:
            std::cout << "\nERROR: Your guess, \"" << sGuess << "\" contains non-alpha input.";
            std::cout << "\nPlease use only letters (this *is* a word-game, y'know! [think Scrabble].)";
            break;
        case eGuessValidation::Not_Isogram:
            std::cout << "\nERROR: Your guess, \"" << sGuess << "\" contains repeated characters.";
            std::cout << "\nPlease enter an isogram (a word comprised of all unique letters,";
            std::cout << "\ni.e. book:INVALID, two 'o's, but bark:GREAT!)";
            break;
        case eGuessValidation::Too_Long:
            std::cout << "\nERROR: Your guess, \"" << sGuess << "\" is too long.";
            std::cout << "\nPlease use a " << ActiveGame.iGetIsogramLength() << " - letter word.";
            break;
        case eGuessValidation::Too_Short:
            std::cout << "\nERROR: Your guess, \"" << sGuess << "\" is too short.";
            std::cout << "\nPlease use a " << ActiveGame.iGetIsogramLength() << " - letter word.";
            break;
        case eGuessValidation::Okay:
            std::cout << "\nYour guess was, \"" << sGuess << "\"";
            break;
        default:
            break;
        }
    } while (status != eGuessValidation::Okay);
    return sGuess;
}

eGuessValidation ValidateGuess(FString sGuess)
{
    int32 iIsogramLength = (ActiveGame.sGetIsogram()).length();

    if      (!bIsAlpha(sGuess))                     { return eGuessValidation::Not_Alpha; }
    else if (!ActiveGame.bIsIsogram(sGuess))        { return eGuessValidation::Not_Isogram; }
    else if (sGuess.length() < iIsogramLength)      { return eGuessValidation::Too_Short; }
    else if (sGuess.length() > iIsogramLength)      { return eGuessValidation::Too_Long; }
    else                                            { return eGuessValidation::Okay; }
}

FString sStringToLower(FString convertString) // TODO ditch this for the one in IsogramGame
{
    int32 iStringLength = convertString.length();
    for (int32 i = 0; i < iStringLength; i++) 
        { convertString[i] = tolower(convertString[i]); }
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
