#pragma once
#include "IsogramGame.h"

IsogramGame::IsogramGame()                          { Reset(); return; }

bool IsogramGame::bIsGuessMatch() const             { return bDoesGuessMatch; }
FString IsogramGame::sGetIsogram() const            { return sIsogram; }
int32 IsogramGame::iGetCurrentGuessNum() const      { return iCurrentGuess; }
int32 IsogramGame::iGetIsogramLength() const        { return sIsogram.length(); }
int32 IsogramGame::iGetLossCount() const            { return iLossCount; }
int32 IsogramGame::iGetPhaseScore() const           { return iPhaseScore; }
int32 IsogramGame::iGetRunningScore() const         { return iRunningScore; }
int32 IsogramGame::iGetWinCount() const             { return iWinCount; }
void IsogramGame::IncrementGuess()                  { iCurrentGuess++; return; }
void IsogramGame::IncrementLoss()                   { iLossCount++; return; }

// Initialize new game or setup for next round.
void IsogramGame::Reset()
{
    if (!bInitialized) 
    {
        bDisplayHints = true;
        bInitialized = true;
        bValidated = false;
        bValidDictionary = false;
        iLossCount = 0;
        iPhaseScore = 0;
        iWinCount = 0;
    }
    iCurrentGuess = 1;
    sIsogram = sSelectIsogram(iGetChallengeSize());
    return;
}

// Update total score, then reset round-score.
void IsogramGame::Tally()
{
    iRunningScore += iPhaseScore;
    iPhaseScore = 0;
    return;
}

// Respond with # of guesses based on length of challenge word.
int32 IsogramGame::iGetMaxGuesses() const 
{
    std::map <int32, int32> mWordSizeToGuessCount {
        { 2,7 }, { 3,6 },  { 4,7 },  { 5,8 },  { 6,9 },  { 7,9 }, { 8,9 },
        { 9,8 }, { 10,7 }, { 11,6 }, { 12,5 }, { 13,4 }, { 14,3 }, { 15,3 }
    };
    return mWordSizeToGuessCount[sGetIsogram().length()];
}

// Respond with maximum challenge-word size. Higher total scores give bigger challenges (longer words).
int32 IsogramGame::iGetChallengeSize() const 
{
    if      (iRunningScore < 15)   { return 3; }
    else if (iRunningScore < 45)   { return 4; }
    else if (iRunningScore < 75)   { return 5; }
    else if (iRunningScore <135)   { return 6; }
    else if (iRunningScore <255)   { return 7; }
    else if (iRunningScore <495)   { return 8; }
    else if (iRunningScore <975)   { return 9; }
    else if (iRunningScore <1935)  { return 10; }
    else if (iRunningScore <3855)  { return 11; }
    else if (iRunningScore <7695)  { return 12; }
    else if (iRunningScore <15375) { return 13; }
    else                           { return 14; }
}

// Update the active game Analysis <struct>, comparing challenge word aganist submitted guess.
Analysis IsogramGame::AnalyzeGuess(FString sGuess)
{
    Analysis zAnalysis;

    int32 iIsogramLength = sIsogram.length();
    zAnalysis.sPositionHint = FString(iIsogramLength, '-');
    zAnalysis.sLetterHint = zAnalysis.sPositionHint;
    
    for (int32 iGuessLetter = 0; iGuessLetter < iIsogramLength; iGuessLetter++) {
        for (int32 iIsogramLetter = 0; iIsogramLetter < iIsogramLength; iIsogramLetter++) {
            if (sGuess[iGuessLetter] == sIsogram[iIsogramLetter]) {
                bool bLetterScore = false;
                bool bPositionScore = false;
                if (iGuessLetter == iIsogramLetter) 
                {
                    bPositionScore = true;
                    zAnalysis.iPositionMatches++;
                    zAnalysis.sPositionHint[iGuessLetter] = sGuess[iGuessLetter];
                } else
                { 
                    bLetterScore = true;
                    zAnalysis.iLetterMatches++;
                    zAnalysis.sLetterHint[iGuessLetter] = sGuess[iGuessLetter];
                }
                if (!bLetterScore && bPositionScore)         { iPhaseScore = (iPhaseScore + 3); }
                else if (bLetterScore && !bPositionScore)    { iPhaseScore++; }
            }
        }
    }
    if (zAnalysis.iPositionMatches == iIsogramLength) 
    {
        bDoesGuessMatch = true;
        iWinCount++;
    } else {
        bDoesGuessMatch = false;
    }
    return zAnalysis;
}

// Set and respond with next challenge-word; required argument INT indicates maximum word length (INT-1 = maxWL).
FString IsogramGame::sSelectIsogram(int iChallengeNum)
{
    if (iChallengeNum < 3) { iChallengeNum = 3; }
    std::vector<FString> aDictionary = {
        "at", "is", "to", "go", "on", "we", "be", "id", "do", "no", "he", "so", "it", 
        "bye", "art", "car", "yam", "lab", "the", "cut", "lot", "lie", "par", "age", "tax", "lax", 
        "say", "pay", "may", "jam", "mit", "din", "was", "pot", "pie", "mar",
        "ray", "elf", "fly", "fit", "lit", "sin", "put", "rot", "cry", "coy",
        "sand", "pair", "raid", "care", "sock", "fair", "hair", "land", "walk", "talk", "expo", "wasp",
        "same", "dart", "this", "from", "suit", "acre", "ages", "bale", "bail", "fast", "lynx",
        "felt", "fawn", "nape", "army", "navy", "sold", "soda", "soup", "wave", "yarn",
        "toads", "brick", "stick", "roads", "stand", "trick", "thick", "loads", "talks", "locks", "angel", "dregs",
        "thing", "miles", "lives", "facts", "cloth", "dwarf", "empty", "trash", "envoy", "enact", "pious",
        "faith", "farms", "farce", "fairy", "laugh", "lingo", "litre", "march", "marsh", "swift", "rages",
        "hybrid", "fabric", "sculpt", "sample",
        "jaunts", "abound", "tricks", "bricks", "crawls", "crowns", "around", "orgasm", "bounty", "gizmos", "zealot",
        "travel", "wealth", "second", "curled", "loving", "belfry", "fables", "factor", "fairly", "famine", "bronze",
        "farces", "nailed", "nebula", "nickel", "muster", "buster", "myrtle", "nachos", "mythos", "phrase", "quartz",
        "jukebox", "ziplock", "lockjaw", "quickly", "crazily", "jaybird", "jackpot", "quicken", "quicker", "imports",
        "clothes", "polearm", "jockeys", "subject", "cliquey", "apricot", "anxiety", "domains", "dolphin", "exclaim",
        "fabrics", "factory", "haircut", "pulsing", "scourge", "schlump", "turbine", "wrongly", "wyverns", "yoghurt",
        "isogram", "mindful", 
        "love", "tango", "cables", "sketchy", "rambling", "ramblings", "traveling",
        "exoplasm", "exploits", "explains", "exhaling", "handgrip", "hardiest", "hasteful", "megalith", "megatons", "merciful",
        "sculptor", "minerals",
        "yachtsmen", "worshiped", "workspace", "womanizer", "wolfsbane", "windstorm", "workmates", "wordgames", "inspector", "constable",
        "abductions", "hospitable", "background", "campground", "greyhounds", "infamously", "afterglows", "shockingly",
        "workmanship", "palindromes", "speculation", "trampolines", "personality", "sympathizer", "abolishment", "atmospheric",
        "thunderclaps", "misconjugated", "unproblematic", "unprofitable", "questionably", "packinghouse", "upholstering",
        "draughtswomen", "flowchartings", "lycanthropies", "pneumogastric", "salpingectomy", "subordinately"
    };
    int32 iNumberOfIsograms = size(aDictionary);

    // ----- Validate dictionary ONCE ONLY ----- //
    if (!bValidated && !bValidDictionary)
    {
        bool bReportingMode = true;
        bValidated = true;
        bValidDictionary = true;
        FString sTestString;

        for (int32 iIndex = 0; iIndex < iNumberOfIsograms; iIndex++)
        {
            sTestString = aDictionary[iIndex];
            if (!bIsIsogram(sTestString))
            {
                bValidDictionary = false;
                if (bReportingMode)
                {
                    std::cout << "E R R O R . V A L I D A T I N G -" << iNumberOfIsograms << "- W O R D S\n";
                    std::cout << "INTERNAL ERROR z-13: Dictionary validation failures detected:\n";
                    bReportingMode = false;
                }
                std::cout << " -- Dictionary[" << iIndex << "] = \"" << sTestString << "\"\n";
            }
        }
        if (!bReportingMode)
        {
            std::cout << "\nWARNING: Any words listed above will be ignored as unplayable.\n\n";
        }
    }
    FString sSelection;
    int32 iSelection;
    int32 iSelectionLength;
    do {
        do {
            std::uniform_int_distribution<> zIndexDist(0, iNumberOfIsograms - 1);
            iSelection = zIndexDist(Entropy);
            sSelection = aDictionary[iSelection];
        } while (!bIsIsogram(sSelection));
        iSelectionLength = sSelection.length();
    } while (iSelectionLength > iChallengeNum +1);
    return sSelection; // Break and watch here to cheat.
}

bool IsogramGame::bIsIsogram(FString sTestString)
{
    sTestString = sStringToLower(sTestString);
    std::map<char, bool> mObservedLetterTF;

    for (auto cLetter : sTestString) {
        if (!mObservedLetterTF[cLetter]) { mObservedLetterTF[cLetter] = true; }
        else return false;
    } return true;
}

FString IsogramGame::sStringToLower(FString sConvertString)
{
    int32 iLength = sConvertString.length();
    for (int32 iPosition = 0; iPosition < iLength; iPosition++) 
        { sConvertString[iPosition] = tolower(sConvertString[iPosition]); }
    return sConvertString;
}

// ----- Letter-Box Methods ----- //

FString LetterBox::sGetLetters() const      { return sBoxOfLetters; }
void LetterBox::Reset()                     { sBoxOfLetters = ""; return; }

void LetterBox::SubmitLetter(char cLetter)
{
    if (sBoxOfLetters == "") { sBoxOfLetters += cLetter; }
    else
    {
        int32 iBoxSize = sBoxOfLetters.length();
        int32 iLetterMatches = 0;
        bool bNovelChar = false;
        for (int32 iSlot = 0; iSlot < iBoxSize; iSlot++) 
        {
            if (!(sBoxOfLetters[iSlot] == cLetter)) 
                { iLetterMatches++; bNovelChar = true; }
        }
        if (bNovelChar && (iLetterMatches == iBoxSize)) { 
            sBoxOfLetters += cLetter; 
        }
    }
    std::sort(sBoxOfLetters.begin(), sBoxOfLetters.end());
    return;
}
