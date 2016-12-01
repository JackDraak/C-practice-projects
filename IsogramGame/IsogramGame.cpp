#pragma once
#include "IsogramGame.h"

bool bIsIsogram(FString);
FString sStringsToLower(FString);

IsogramGame::IsogramGame()                          { Reset(); }

bool IsogramGame::bGetGuessMatch() const            { return bGuessMatch; }
FString IsogramGame::sGetIsogram() const            { return sIsogram; }
FString IsogramGame::sGetSubmittedLetters() const   { return sSubmittedLetters; }
int32 IsogramGame::iGetCurrentGuess() const         { return iCurrentGuess; }
int32 IsogramGame::iGetIsogramLength() const        { return sIsogram.length(); }
int32 IsogramGame::iGetLossCount() const            { return iLossCount; }
int32 IsogramGame::iGetScore() const                { return iScore; }
int32 IsogramGame::iGetWinCount() const             { return iWinCount; }
void IsogramGame::IncrementGuess()                  { iCurrentGuess++; }
void IsogramGame::IncrementLoss()                   { iLossCount++; }

void IsogramGame::Reset()
{
    if (!bInitialized) 
    {
        bValidDictionary = false;
        bInitialized = true;
        bDisplayHints = true;
        iLossCount = 0;
        iScore = 0;
        iWinCount = 0;
    }
    iCurrentGuess = 1;
    bFirstGuess = true;
    sSubmittedLetters = "";
    sIsogram = SelectIsogram();
    return;
}

int32 IsogramGame::iGetMaxGuesses() const 
{
    std::map <int32, int32> mapWordSizeToGuessCount { 
        { 3,4 }, { 4,6 }, { 5,8 }, { 6,9 }, 
        { 7,10 }, { 8,9 }, { 9,8 }, { 10,7 }, 
        { 11,6 }, { 12,5 }, { 13,4 }, { 14,3 } 
    };
    return mapWordSizeToGuessCount[sGetIsogram().length()];
}

Analysis IsogramGame::AnalyzeGuess(FString sGuess)
{
    Analysis analysis;

    if (bFirstGuess)
    {
        bFirstGuess = false;
        sSubmittedLetters = sGuess;
    }

    FString letterComplement = sSubmittedLetters;
    letterComplement += sGuess;
    FString carryLetter = "";
    FString newLetters = ""; 

/*

do something useful here

*/

//    std::sort(letterComplement.begin(), letterComplement.end());
//    std::unique(letterComplement.begin(), letterComplement.end());

    int32 iIsogramLength = sIsogram.length();
    analysis.sPositionHint = FString(iIsogramLength, '-');
    analysis.sLetterHint = analysis.sPositionHint;
    
    for (int32 GuessLetter = 0; GuessLetter < iIsogramLength; GuessLetter++) {
        for (int32 IsogramLetter = 0; IsogramLetter < iIsogramLength; IsogramLetter++) {
            if (sGuess[GuessLetter] == sIsogram[IsogramLetter]) {
                if (GuessLetter == IsogramLetter) 
                {
                    analysis.iPositionMatches++;
                    iScore++;
                    analysis.sPositionHint[GuessLetter] = sGuess[GuessLetter];
                }
                else
                { 
                    analysis.iLetterMatches++;
                    iScore = iScore + 3;
                    analysis.sLetterHint[GuessLetter] = sGuess[GuessLetter];
                }
            }
        }
    }
    if (analysis.iPositionMatches == iIsogramLength) 
    {
        bGuessMatch = true;
        iWinCount++;
    } else {
        bGuessMatch = false;
    }
    return analysis;
}

FString IsogramGame::SelectIsogram()
{
    std::vector<FString> Dictionary = {
        "bye", "art", "car", "yam", "lab", "the", "cut", "lot", "lie", "par",
        "say", "pay", "may", "jam", "mit", "din", "was", "pot", "pie", "mar",
        "ray", "elf", "fly", "fit", "lit", "sin", "put", "rot", "cry", "coy",
        "sand", "pair", "raid", "care", "sock", "fair", "hair", "land", "walk", "talk", "expo",
        "same", "dart", "this", "from", "suit", "acre", "ages", "bale", "bail", "fast",
        "felt", "fawn", "nape", "army", "navy", "sold", "soda", "soup", "wave", "yarn",
        "toads", "brick", "stick", "roads", "stand", "trick", "thick", "loads", "talks", "locks",
        "thing", "miles", "lives", "facts", "cloth", "dwarf", "empty", "trash", "envoy", "enact",
        "faith", "farms", "farce", "fairy", "laugh", "lingo", "litre", "march", "marsh", "swift",
        "jaunts", "abound", "tricks", "bricks", "crawls", "crowns", "around", "orgasm", "bounty", "gizmos", "angel",
        "travel", "wealth", "second", "curled", "loving", "belfry", "fables", "factor", "fairly", "famine",
        "farces", "nailed", "nebula", "nickel", "muster", "buster", "myrtle", "nachos", "mythos", "phrase", "quartz",
        "isogram", "mindful",
        "jukebox", "ziplock", "lockjaw", "quickly", "crazily", "jaybird", "jackpot", "quicken", "quicker", "imports",
        "clothes", "polearm", "jockeys", "subject", "cliquey", "apricot", "anxiety", "domains", "dolphin", "exclaim",
        "fabrics", "factory", "haircut", "pulsing", "scourge", "schlump", "turbine", "wrongly", "wyverns", "yoghurt",
        "wasp"
    };
    int32 iNumberOfIsograms = size(Dictionary);

    // ----- validate dictionary ONCE ONLY ----- //
    // this is somewhat anachronistic, as now the secret word is validated immediately prior to use (as well)
    // but there's no harm keeping it for extra data, i.e. in a case where new words are added to the dictionary...
    // in one run of the program they will all be immediately flagged on the console.
    if (!bValidDictionary) // TODO: invalid dictionaries re-validate between rounds... not a high priority to fix, really
    {
        bValidDictionary = true;
        FString sTestString;
        bool oops = true;

        for (int32 i = 0; i < iNumberOfIsograms; i++)
        {
            sTestString = Dictionary[i];
            if (!bIsIsogram(sTestString))
            {
                bValidDictionary = false;
                if (oops)
                {
                    std::cout << "E R R O R . V A L I D A T I N G -" << iNumberOfIsograms << "- W O R D S\n";
                    std::cout << "INTERNAL ERROR z-13: Dictionary validation failures detected:\n";
                    oops = false;
                }
                std::cout << " -- Dictionary[" << i << "] = \"" << sTestString << "\"\n";
            }
        }
        if (!oops)
        {
            std::cout << "\nWARNING: Any words listed above will be ignored as unplayable.\n\n";
        }
    }
    FString sSelection;
    int32 iSelection;
    do {
        srand(unsigned(time(NULL)));
        iSelection = rand() % iNumberOfIsograms;
        sSelection = Dictionary[iSelection];
    } while (!bIsIsogram(sSelection));
    return sSelection;
}

// ----- Internal Functions ----- //

bool bIsIsogram(FString sTestString)
{
    sTestString = sStringsToLower(sTestString);
    std::map<char, bool> observedLetter;

    for (auto Letter : sTestString) {
        if (!observedLetter[Letter]) { observedLetter[Letter] = true; }
        else return false;
    } return true;
}

FString sStringsToLower(FString convertString)
{
    int32 iLength = convertString.length();
    for (int32 i = 0; i < iLength; i++) { convertString[i] = tolower(convertString[i]); }
    return convertString;
}

void Tracker::SetIn() const
{
}

void Tracker::SetOut() const
{
}

void Tracker::SetChar(char)
{
}

bool Tracker::bGetStatus() const
{
    return false;
}

char Tracker::sGetChar() const
{
    return 0;
}

void LetterBox::Reset() const
{
}

FString LetterBox::sGetLetters() const
{
    return FString();
}

void LetterBox::SetLetter(char)
{
}
