/*
Isogram Game
based on https://www.udemy.com/unrealcourse/ by Ben Tristem (Thanks, Ben!)
coded by Jack Draak

A rudimentary console-based application used in learning about C++. Main.cpp, which
acts as the view in an MVC pattern and is responsible for all user interaction also 
utilizes Isogramgame.cpp for game logic operations.

Built with VisualStudio 2015, ostensibly for Windows, but it should be easy to port,
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
void PrintLetterBox(FString);
void PrintRoundSummary();
void PrintScoringHelp();

// Instantiate objects (ActiveGame & ActiveLetterBox) for manipulation.
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
    int32 iMaxGuesses = ActiveGame.iGetMaxGuesses();

    for (int32 iGuessNum = 1; iGuessNum <= iMaxGuesses; iGuessNum++)
    {
        sGuess = sGetValidGuess(); 
        sGuess = ActiveGame.sStringToLower(sGuess);
        int32 iGuessLength = sGuess.length();

        // ----- Update Letterbox ----- //
        for (int32 iIndex = 0; iIndex < iGuessLength; iIndex++ ) { ActiveLetterBox.SubmitLetter(sGuess[iIndex]); }

        // ----- Process a turn ----- //
        Analysis zAnalysis = ActiveGame.AnalyzeGuess(sGuess);
        if (ActiveGame.bIsGuessMatch()) { break; } // skip outputting turn results if the guess matches
        ActiveGame.IncrementGuess(); // this is why FudgeGuesses() is needed, it goes one too high in a lost-round scenario

        // ----- Output phase (turn) results ----- //
        std::cout << " (used so far: " << ActiveLetterBox.sGetLetters() << ")";
        PrintLetterBox(ActiveLetterBox.sGetLetters());
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
    PrintRoundSummary();
    return;
}

bool bContinuePlaying()
{
    bool bContinue = true;
    do {
        FString sResponce = "";
        int32 iMode = ActiveGame.zGetDifficulty();

        std::cout << "\n\nPlease, choose one of the following: \n  (P)lay again, \n  turn (C)lues ";
        if (ActiveGame.bDisplayHints) { std::cout << "off,"; } else { std::cout << "on,"; }
        std::cout << "\n  (R)epeat intro, \n  show how to (S)core, \n  switch to "; 
        if (iMode == 1)       { std::cout << "(N)ormal or \n  (H)ard difficulty,"; }
        else if (iMode == 2)  { std::cout << "(E)asy or \n  (H)ard difficulty,"; }
        else if (iMode == 3)  { std::cout << "(E)asy or \n  (N)ormal difficulty,"; }
        std::cout << "\n  or (Q)uit.....";
        getline(std::cin, sResponce);

        if ((sResponce[0] == 'c') || (sResponce[0] == 'C')) { ActiveGame.bDisplayHints = !ActiveGame.bDisplayHints; }
        else if ((sResponce[0] == 'q') || (sResponce[0] == 'Q')) { bContinue = false; break; }
        else if ((sResponce[0] == 'p') || (sResponce[0] == 'P')) { ActiveGame.Reset(); break; }
        else if ((sResponce[0] == 'r') || (sResponce[0] == 'R')) { PrintIntro(); }
        else if ((sResponce[0] == 's') || (sResponce[0] == 'S')) { PrintScoringHelp(); }
        else if ((sResponce[0] == 'e') || (sResponce[0] == 'E')) { ActiveGame.SetEasy(); }
        else if ((sResponce[0] == 'n') || (sResponce[0] == 'N')) { ActiveGame.SetNormal(); }
        else if ((sResponce[0] == 'h') || (sResponce[0] == 'H')) { ActiveGame.SetHard(); }
    } while (true);
    if (bContinue) { return true; } else { return false; }
}

void PrintLetterBox(FString sUsedLetters) {
    int32 iBoxSize = sUsedLetters.length();

    std::cout << "\n           ---------------------------------------------------";
    std::cout << "\n           a b c d e f g h i j k l m n o p q r s t u v w x y z";
    std::cout << "\n           ";
    for (int32 iAlphabet = 0; iAlphabet < 26; iAlphabet++) 
    {
        bool bInSet = false;
        char cTestChar = 'a' + iAlphabet;

        for (int32 iLetter = 0; iLetter < iBoxSize; iLetter++)
        {
            if (sUsedLetters[iLetter] == cTestChar) { bInSet = true; }
        }
        if (bInSet) { std::cout << "x "; }
        else { std::cout << "  "; }
    }
    std::cout << "\n           ---------------------------------------------------";
    return;
}

void PrintRoundSummary() {
    if (ActiveGame.bIsGuessMatch()) { std::cout << "\nCongratulations! You guessed "; }
    else {
        ActiveGame.IncrementLoss();
        ActiveGame.FudgeGuesses();
        std::cout << "\nBummer! You didn't guess ";
    }
    std::cout << "the secret isogram : " << ActiveGame.sGetIsogram() << ".\nIt took you ";
    std::cout << ActiveGame.iGetCurrentGuessNum();
    std::cout << " guesses. You earned " << ActiveGame.iGetPhaseScore() << " points.";
    ActiveGame.Tally();
    std::cout << "\nTotal score: " << ActiveGame.iGetRunningScore() << " points. (win/loss: ";
    std::cout << ActiveGame.iGetWinCount() << "/" << ActiveGame.iGetLossCount() << ", total guesses: ";
    std::cout << ActiveGame.iGetRunningGuesses() << ")";
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
            std::cout << "\nERROR: Your guess, \"" << sGuess << "\" is too long. (" << sGuess.length() << " letters)";
            std::cout << "\nPlease use a " << ActiveGame.iGetIsogramLength() << " - letter word.";
            break;
        case eGuessValidation::Too_Short:
            std::cout << "\nERROR: Your guess, \"" << sGuess << "\" is too short. (" << sGuess.length() << " letters)";
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
    std::cout << "\nIf you guess a letter correctly (but in the wrong place) you get* +2 points,";
    std::cout << "\nand if you guess a correct letter in the proper position you get* +6 points.";
    std::cout << "\nYour score is cumulative from round-to-round. As your score increases, the";
    std::cout << "\nlonger the next challenge word may be.";
    std::cout << "\n[*Normal score; Easy: 1 or 3 points, Hard: 3 or 9 points, respectively]";
    return;
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
