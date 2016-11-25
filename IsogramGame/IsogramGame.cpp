#pragma once
#include "IsogramGame.h"

using int32 = int;

IsogramGame::IsogramGame()                      { Reset(); }

void IsogramGame::IncrementGuess()              { iCurrentGuess++; }
FString IsogramGame::sGetIsogram() const        { return sIsogram; }
int32 IsogramGame::iGetCurrentGuess() const     { return iCurrentGuess; }
int32 IsogramGame::iGetIsogramLength() const    { return sIsogram.length(); }
bool IsogramGame::bGetGuessMatch() const        { return bGuessMatch; }

int32 IsogramGame::iGetMaxGuesses() const 
{
    std::map <int32, int32> mapWordSizeToGuessCount { 
        { 3,4 }, { 4,6 }, { 5,8 }, { 6,9 }, { 7,10 },
        { 8,9 }, { 9,8 }, { 10,7 }, { 11,6 }, { 12,5 },
        { 13,4 }, { 14,3 } 
    };
    return mapWordSizeToGuessCount[sGetIsogram().length()];
}

Analysis IsogramGame::AnalyzeGuess(FString sGuess)
{
    Analysis analysis;

    char guessHash = '-';
    int32 iIsogramLength = sIsogram.length();
    analysis.sPositionHint = FString(iIsogramLength, guessHash);
    analysis.sLetterHint = analysis.sPositionHint;

    for (int32 GuessLetter = 0; GuessLetter < iIsogramLength; GuessLetter++) {
        for (int32 IsogramLetter = 0; IsogramLetter < iIsogramLength; IsogramLetter++) {
            if (sGuess[GuessLetter] == sIsogram[IsogramLetter]) {
                if (GuessLetter == IsogramLetter) 
                {
                    analysis.iPositionMatches++; // TODO calculate a score
                    analysis.sPositionHint[GuessLetter] = sGuess[GuessLetter];
                }
                else // implicit: if (iGuessLetter != iIsogramLetter) {
                { 
                    analysis.iLetterMatches++; // TODO calculate a score
                    analysis.sLetterHint[GuessLetter] = sGuess[GuessLetter];
                }
            }
        }
    }

    if (analysis.iPositionMatches == iIsogramLength) 
    {
        bGuessMatch = true;
    } else {
        bGuessMatch = false;
    }
    return analysis;
}

FString IsogramGame::SelectIsogram()
{
    FString Dictionary[] = { // TODO feature request 3-7 letter words
        "sand", "pair", "raid", "care", "sock", "fair", "hair", "land", "walk", "talk",
        "same", "dart", "this", "from", "suit", "acre", "ages", "bale", "bail", "fast",
        "felt", "fawn", "nape", "army", "navy", "sold", "soda", "soup", "wave", "yarn",
        "toads", "brick", "stick", "roads", "stand", "trick", "thick", "loads", "talks", "locks",
        "thing", "miles", "lives", "facts", "cloth", "dwarf", "empty", "trash", "envoy", "enact",
        "faith", "farms", "farce", "fairy", "laugh", "lingo", "litre", "march", "marsh", "swift",
        "jaunts", "abound", "tricks", "bricks", "crawls", "crowns", "around", "orgasm", "bounty", "gizmos",
        "travel", "wealth", "second", "curled", "loving", "belfry", "fables", "factor", "fairly", "famine",
        "farces", "nailed", "nebula", "nickel", "muster", "buster", "myrtle", "nachos", "mythos", "phrase", "quartz"
        "isogram", "mindful",
        "jukebox", "ziplock", "lockjaw", "quickly", "crazily", "jaybird", "jackpot", "quicken", "quicker", "imports",
        "clothes", "polearm", "jockeys", "subject", "cliquey", "apricot", "anxiety", "domains", "dolphin", "exclaim",
        "fabrics", "factory", "haircut", "pulsing", "scourge", "schlump", "turbine", "wrongly", "wyverns", "yoghurt"
    };
    int32 DICTIONARY_SIZE = 123;
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
