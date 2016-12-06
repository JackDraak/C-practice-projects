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

bool bContinuePlaying();
bool bIsAlpha(FString);
eGuessValidation eValidateGuess(FString);
FString sGetValidGuess();
int main();
void PlayGame();
void PrintIntro();
void PrintScoringHelp();

// instantiate objects (ActiveGame & ActiveLetterBox) for manipulation.
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
    FString sGuess = "";
    int32 cMaxGuesses = ActiveGame.iGetMaxGuesses();

    for (int32 iGuessNum = 1; iGuessNum <= cMaxGuesses; iGuessNum++)
    {
        sGuess = sGetValidGuess(); 
        sGuess = ActiveGame.sStringToLower(sGuess);
        int32 iGuessLength = sGuess.length();

        for (int32 iIndex = 0; iIndex < iGuessLength; iIndex++ ) { ActiveLetterBox.SubmitLetter(sGuess[iIndex]); }
        Analysis zAnalysis = ActiveGame.AnalyzeGuess(sGuess);
        if (ActiveGame.bIsGuessMatch()) { break; } 
        ActiveGame.IncrementGuess();

        // ----- Output phase (turn) results ----- //

        std::cout << "\nComplement of letters used this round: " << ActiveLetterBox.sGetLetters();
        std::cout << "\n...Correct letters in the wrong place(s): " << zAnalysis.iLetterMatches;
        if (ActiveGame.bDisplayHints) 
        {
            std::random_shuffle(zAnalysis.sLetterHint.begin(), zAnalysis.sLetterHint.end());
            std::cout << "  [shuffled hint: '" << zAnalysis.sLetterHint << "']";
        }
        std::cout << "\n...Correct letters in the proper position(s): " << zAnalysis.iPositionMatches;
        if (ActiveGame.bDisplayHints) 
        {
            std::cout << "       [hint: '" << zAnalysis.sPositionHint << "']";
        }
    }
        // ----- Output round results ----- //
        
        if (ActiveGame.bIsGuessMatch()) { std::cout << "\nCongratulations! You guessed "; }
        else { ActiveGame.IncrementLoss(); std::cout << "\nBummer! You didn't guess "; }
        std::cout<< "the secret isogram : " << ActiveGame.sGetIsogram() << ".\nIt took you ";
        if (ActiveGame.bIsGuessMatch()) { std::cout << ActiveGame.iGetCurrentGuessNum() << " guesses. You earned "; }
        else { std::cout << (ActiveGame.iGetCurrentGuessNum() -1) << " guesses. You earned "; }
        std::cout << ActiveGame.iGetPhaseScore() << " points."; 
        ActiveGame.Tally();
        std::cout << "\nTotal score: " << ActiveGame.iGetRunningScore() << " points. (win/loss ";
        std::cout << ActiveGame.iGetWinCount() << "/" << ActiveGame.iGetLossCount() << ")";
        return;
}

bool bContinuePlaying()
{
    bool bContinue = true;
    do {
        FString sResponce = "";
        std::cout << "\n\nPlease, enter: (P)lay again, toggle (H)ints ";
        if (ActiveGame.bDisplayHints) { std::cout << "off"; } else { std::cout << "on"; }
        std::cout << ", (R)epeat intro, \n               show (S)coring algorithm, or (Q)uit...";
        getline(std::cin, sResponce);

        if ((sResponce[0] == 'h') || (sResponce[0] == 'H')) { ActiveGame.bDisplayHints = !ActiveGame.bDisplayHints; }
        else if ((sResponce[0] == 'q') || (sResponce[0] == 'Q')) { bContinue = false; break; }
        else if ((sResponce[0] == 'p') || (sResponce[0] == 'P')) { ActiveGame.Reset(); break; }
        else if ((sResponce[0] == 'r') || (sResponce[0] == 'R')) { PrintIntro(); }
        else if ((sResponce[0] == 's') || (sResponce[0] == 'S')) { PrintScoringHelp(); }
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

void PrintScoringHelp()
{
    std::cout << "\nEach time you make a guess you have a chance to score points....";
    std::cout << "\nIf you guess a letter correctly (but in the wrong place) you get +1 point,";
    std::cout << "\nand if you guess a correct letter in the proper position you get +3 points.";
    std::cout << "\nYour score is cumulative from round-to-round. (Also, the higher your score,";
    std::cout << "\nthe longer the challenge word may be.)";
    return;
}

FString sGetValidGuess()
{
    eGuessValidation zStatus = eGuessValidation::Invalid_Status;
    FString sGuess = "";
    int32 iWordLen = ActiveGame.iGetIsogramLength();

    do {
        std::cout << "\n\nCan you guess the " << iWordLen << " letter isogram that has been randomly pre-selected?";
        std::cout << "\nPlease, enter your guess (#" << ActiveGame.iGetCurrentGuessNum();
        std::cout << " of " << ActiveGame.iGetMaxGuesses() << ") now: ";
        getline(std::cin, sGuess);

        zStatus = eValidateGuess(sGuess);
        switch (zStatus)
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
    } while (zStatus != eGuessValidation::Okay);
    return sGuess;
}

eGuessValidation eValidateGuess(FString sGuess)
{
    int32 iGuessLength = sGuess.length();
    int32 iIsogramLength = (ActiveGame.sGetIsogram()).length();

    if      (!bIsAlpha(sGuess))                     { return eGuessValidation::Not_Alpha; }
    else if (!ActiveGame.bIsIsogram(sGuess))        { return eGuessValidation::Not_Isogram; }
    else if (iGuessLength < iIsogramLength)         { return eGuessValidation::Too_Short; }
    else if (iGuessLength > iIsogramLength)         { return eGuessValidation::Too_Long; }
    else                                              return eGuessValidation::Okay; 
}

bool bIsAlpha(FString sTestString)
{
    int32 iLength = sTestString.length();
    for (int32 iPosition = 0; iPosition < iLength; iPosition++)
    {
        char cThisChar = tolower(sTestString[iPosition]);
        if (!(cThisChar >= 'a' && cThisChar <= 'z')) { return false; }
    }
    return true;
}
