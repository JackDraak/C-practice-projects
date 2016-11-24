#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>    /* std::random_shuffle */
#include <string>
#include <iostream>
#include "IsogramGame.h"

using int32 = int;

void IsogramGame::IncrementGuess()              { iCurrentGuess++; }
FString IsogramGame::sGetIsogram() const        { return sIsogram; }
int32 IsogramGame::iGetCurrentGuess() const     { return iCurrentGuess; }
int32 IsogramGame::iGetIsogramLength() const    { return sIsogram.length(); }
int32 IsogramGame::iGetMaxGuesses() const       { return iMaxGuesses; }
bool IsogramGame::bGetGuessMatch() const        { return bGuessMatch; }

IsogramGame::IsogramGame()
{
    iMaxGuesses = 4;
    Reset();
}

Analysis IsogramGame::AnalyzeGuess(FString sGuess)
{
    srand(unsigned(time(NULL)));
    Analysis analysis; // setup return variable
    int32 iIsogramLength = sIsogram.length();
    char guessHash = '-';
    analysis.sHint = FString(iIsogramLength, guessHash);

    for (int32 GuessLetter = 0; GuessLetter < iIsogramLength; GuessLetter++) {
        for (int32 IsogramLetter = 0; IsogramLetter < iIsogramLength; IsogramLetter++) {
            if (sGuess[GuessLetter] == sIsogram[IsogramLetter]) {
                if (GuessLetter == IsogramLetter) 
                {
                    analysis.iPositionMatches++; // TODO score
                    analysis.sHint[GuessLetter] = sGuess[GuessLetter];
                }
                else // implicit: if (iGuessLetter != iIsogramLetter) {
                { 
                    analysis.iLetterMatches++; // TODO score
       // TODO finish letter hints            std::random_shuffle(myvector.begin(), myvector.end());
                }
            }
        }
    }

    if (analysis.iPositionMatches == iIsogramLength) 
    {
   //     analysis.bDoesGuessMatchIsogram = true; 
        bGuessMatch = true;
    } else {
  //      analysis.bDoesGuessMatchIsogram = false;
        bGuessMatch = false;
    }
    return analysis;
}

FString IsogramGame::SelectIsogram()
{
    FString Dictionary[] = {
        "toads", "brick", "stick", "roads", "stand", "trick", "thick", "loads", "talks", "locks",
        "thing", "miles", "lives", "facts", "cloth", "dwarf", "empty", "trash", "envoy", "enact",
        "faith", "farms", "farce", "fairy", "laugh", "lingo", "litre", "march", "marsh", "swift",
        "jaunts", "abound", "tricks", "bricks", "crawls", "crowns", "around", "orgasm", "bounty", "gizmos",
        "travel", "wealth", "second", "curled", "loving", "belfry", "fables", "factor", "fairly", "famine",
        "farces", "nailed", "nebula", "nickel", "muster", "buster", "myrtle", "nachos", "mythos", "phrase",
        "isogram"
    };
    int32 DICTIONARY_SIZE = 61;
    int32 iSelection;
    srand(unsigned(time(NULL)));
    iSelection = rand() % DICTIONARY_SIZE;
    FString sSelection = Dictionary[iSelection];
    return sSelection; 
}


void IsogramGame::Reset()
{
    if (!bInitialized) 
    {
        bInitialized = true;
        iLossCount = 0;
        iScore = 0;
        iWinCount = 0;
    }
    iCurrentGuess = 1;
    sIsogram = SelectIsogram();
    return;
}
