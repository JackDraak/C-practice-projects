#pragma once
#include "IsogramGame.h"

IsogramGame::IsogramGame()                          { Reset(); return; }

bool IsogramGame::bGetGuessMatch() const            { return bGuessMatch; }
FString IsogramGame::sGetIsogram() const            { return sIsogram; }
int32 IsogramGame::iGetCurrentGuess() const         { return iCurrentGuess; }
int32 IsogramGame::iGetIsogramLength() const        { return sIsogram.length(); }
int32 IsogramGame::iGetLossCount() const            { return iLossCount; }
int32 IsogramGame::iGetRunningScore() const         { return iRunningScore; }
int32 IsogramGame::iGetScore() const                { return iScore; }
int32 IsogramGame::iGetWinCount() const             { return iWinCount; }
void IsogramGame::IncrementGuess()                  { iCurrentGuess++; return; }
void IsogramGame::IncrementLoss()                   { iLossCount++; return; }

void IsogramGame::Reset()
{
    if (!bInitialized) 
    {
        bDisplayHints = true;
        bInitialized = true;
        bValidDictionary = false;
        iLossCount = 0;
        iScore = 0;
        iWinCount = 0;
    }
    iCurrentGuess = 1;
    sIsogram = sSelectIsogram(iGetChallengeNum());
    return;
}

void IsogramGame::Tally()
{
    iRunningScore += iScore;
    iScore = 0;
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

// Set game difficulty arc
int32 IsogramGame::iGetChallengeNum() const 
{
    if      (iScore < 40)   { return 3; }
    else if (iScore < 80)   { return 4; }
    else if (iScore <120)   { return 5; }
    else if (iScore <160)   { return 6; }
    else                    { return 7; }
}

Analysis IsogramGame::AnalyzeGuess(FString sGuess)
{
    Analysis analysis;

    int32 iIsogramLength = sIsogram.length();
    analysis.sPositionHint = FString(iIsogramLength, '-');
    analysis.sLetterHint = analysis.sPositionHint;
    
    for (int32 GuessLetter = 0; GuessLetter < iIsogramLength; GuessLetter++) {
        for (int32 IsogramLetter = 0; IsogramLetter < iIsogramLength; IsogramLetter++) {
            if (sGuess[GuessLetter] == sIsogram[IsogramLetter]) {
                bool bPosScore = false;
                bool bLetterScore = false;
                if (GuessLetter == IsogramLetter) 
                {
                    analysis.iPositionMatches++;
                    bPosScore = true;
                    analysis.sPositionHint[GuessLetter] = sGuess[GuessLetter];
                } else
                { 
                    analysis.iLetterMatches++;
                    bLetterScore = true;
                    analysis.sLetterHint[GuessLetter] = sGuess[GuessLetter];
                }
                if (!bLetterScore && bPosScore)         { iScore = (iScore + 3); }
                else if (bLetterScore && !bPosScore)    { iScore++; }
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

FString IsogramGame::sSelectIsogram(int challengeNum)
{
    std::vector<FString> Dictionary = {
        "bye", "art", "car", "yam", "lab", "the", "cut", "lot", "lie", "par",
        "say", "pay", "may", "jam", "mit", "din", "was", "pot", "pie", "mar",
        "ray", "elf", "fly", "fit", "lit", "sin", "put", "rot", "cry", "coy",
        "sand", "pair", "raid", "care", "sock", "fair", "hair", "land", "walk", "talk", "expo", "wasp",
        "same", "dart", "this", "from", "suit", "acre", "ages", "bale", "bail", "fast",
        "felt", "fawn", "nape", "army", "navy", "sold", "soda", "soup", "wave", "yarn",
        "toads", "brick", "stick", "roads", "stand", "trick", "thick", "loads", "talks", "locks", "angel",
        "thing", "miles", "lives", "facts", "cloth", "dwarf", "empty", "trash", "envoy", "enact", 
        "faith", "farms", "farce", "fairy", "laugh", "lingo", "litre", "march", "marsh", "swift",
        "jaunts", "abound", "tricks", "bricks", "crawls", "crowns", "around", "orgasm", "bounty", "gizmos", 
        "travel", "wealth", "second", "curled", "loving", "belfry", "fables", "factor", "fairly", "famine", "bronze",
        "farces", "nailed", "nebula", "nickel", "muster", "buster", "myrtle", "nachos", "mythos", "phrase", "quartz",
        "jukebox", "ziplock", "lockjaw", "quickly", "crazily", "jaybird", "jackpot", "quicken", "quicker", "imports",
        "clothes", "polearm", "jockeys", "subject", "cliquey", "apricot", "anxiety", "domains", "dolphin", "exclaim",
        "fabrics", "factory", "haircut", "pulsing", "scourge", "schlump", "turbine", "wrongly", "wyverns", "yoghurt",
        "isogram", "mindful",
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
        do {
            srand(unsigned(time(NULL)));
            iSelection = rand() % iNumberOfIsograms;
            sSelection = Dictionary[iSelection];
        } while (!bIsIsogram(sSelection));
    } while (sSelection.length() != challengeNum);
    return sSelection; // Break and watch here to cheat
}

bool IsogramGame::bIsIsogram(FString testString)
{
    testString = sStringToLower(testString);
    std::map<char, bool> observedLetter;

    for (auto Letter : testString) {
        if (!observedLetter[Letter]) { observedLetter[Letter] = true; }
        else return false;
    } return true;
}

FString IsogramGame::sStringToLower(FString convertString)
{
    int32 iLength = convertString.length();
    for (int32 i = 0; i < iLength; i++) { convertString[i] = tolower(convertString[i]); }
    return convertString;
}

// ----- Letter Box Area ----- //

FString LetterBox::sGetLetters() const      { return sBoxOfLetters; }
void LetterBox::Reset()                     { sBoxOfLetters = ""; return; }

void LetterBox::SubmitLetter(char letter)
{
    if (sBoxOfLetters == "") { sBoxOfLetters += letter; }
    else
    {
        int32 boxSize = sBoxOfLetters.length();
        int32 letterMatches = 0;
        bool bNewChar = false;
        for (int32 i = 0; i < boxSize; i++) 
        {
            if (!(sBoxOfLetters[i] == letter)) { letterMatches++; bNewChar = true; }
        }
        if (bNewChar && (letterMatches == boxSize)) { 
            sBoxOfLetters += letter; 
        }
    }
    std::sort(sBoxOfLetters.begin(), sBoxOfLetters.end());
    return;
}
