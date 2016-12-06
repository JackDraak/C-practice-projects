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

// Initialize game or next round
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
    sIsogram = sSelectIsogram(iGetChallengeNum());
    return;
}

// Update total score, then reset round-score
void IsogramGame::Tally()
{
    iRunningScore += iPhaseScore;
    iPhaseScore = 0;
    return;
}

// Calculate # of guesses based on size of challenge word
int32 IsogramGame::iGetMaxGuesses() const 
{
    std::map <int32, int32> mWordSizeToGuessCount {
        { 2,6 }, { 3,5 },  { 4,6 },  { 5,8 },  { 6,9 },  { 7,10 }, { 8,9 },
        { 9,8 }, { 10,7 }, { 11,6 }, { 12,5 }, { 13,4 }, { 14,3 }, { 15,3 }
    };
    return mWordSizeToGuessCount[sGetIsogram().length()];
}

// Higher scores give higher challenges (longer words)
int32 IsogramGame::iGetChallengeNum() const 
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

Analysis IsogramGame::AnalyzeGuess(FString sGuess)
{
    Analysis analysis;

    int32 iIsogramLength = sIsogram.length();
    analysis.sPositionHint = FString(iIsogramLength, '-');
    analysis.sLetterHint = analysis.sPositionHint;
    
    for (int32 GuessLetter = 0; GuessLetter < iIsogramLength; GuessLetter++) {
        for (int32 IsogramLetter = 0; IsogramLetter < iIsogramLength; IsogramLetter++) {
            if (sGuess[GuessLetter] == sIsogram[IsogramLetter]) {
                bool bPositionScore = false;
                bool bLetterScore = false;
                if (GuessLetter == IsogramLetter) 
                {
                    analysis.iPositionMatches++;
                    bPositionScore = true;
                    analysis.sPositionHint[GuessLetter] = sGuess[GuessLetter];
                } else
                { 
                    analysis.iLetterMatches++;
                    bLetterScore = true;
                    analysis.sLetterHint[GuessLetter] = sGuess[GuessLetter];
                }
                if (!bLetterScore && bPositionScore)         { iPhaseScore = (iPhaseScore + 3); }
                else if (bLetterScore && !bPositionScore)    { iPhaseScore++; }
            }
        }
    }
    if (analysis.iPositionMatches == iIsogramLength) 
    {
        bDoesGuessMatch = true;
        iWinCount++;
    } else {
        bDoesGuessMatch = false;
    }
    return analysis;
}

// required argument INT indicates maximum word length (INT-1 = maxWL)
FString IsogramGame::sSelectIsogram(int challengeNum)
{
    std::vector<FString> Dictionary = {
        "at", "is", "to", "go", "on", "we", "be", "id", "do", "no", "he", "so",
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
        "love", "tango", "cables", "sketchy", "rambling", "ramblings", "traveling",
        "exoplasm", "exploits", "explains", "exhaling", "handgrip", "hardiest", "hasteful", "megalith", "megatons", "merciful",
        "yachtsmen", "worshiped", "workspace", "womanizer", "wolfsbane", "windstorm", "workmates", "wordgames",
        "abductions", "hospitable", "background", "campground", "greyhounds", "infamously", "afterglows", "shockingly",
        "workmanship", "palindromes", "speculation", "trampolines", "personality", "sympathizer", "abolishment", "atmospheric",
        "thunderclaps", "misconjugated", "unproblematic", "unprofitable", "questionably", "packinghouse", "upholstering",
        "draughtswomen", "flowchartings", "lycanthropies", "pneumogastric", "salpingectomy", "subordinately"
    };
    int32 iNumberOfIsograms = size(Dictionary);

    // ----- validate dictionary ONCE ONLY ----- //
    if (!bValidDictionary && !bValidated)
    {
        bValidated = true;
        bValidDictionary = true;
        FString sTestString;
        bool bReportingMode = true;

        for (int32 i = 0; i < iNumberOfIsograms; i++)
        {
            sTestString = Dictionary[i];
            if (!bIsIsogram(sTestString))
            {
                bValidDictionary = false;
                if (bReportingMode)
                {
                    std::cout << "E R R O R . V A L I D A T I N G -" << iNumberOfIsograms << "- W O R D S\n";
                    std::cout << "INTERNAL ERROR z-13: Dictionary validation failures detected:\n";
                    bReportingMode = false;
                }
                std::cout << " -- Dictionary[" << i << "] = \"" << sTestString << "\"\n";
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
            std::uniform_int_distribution<> IndexDist(0, iNumberOfIsograms - 1);
            iSelection = IndexDist(Entropy);
            sSelection = Dictionary[iSelection];
        } while (!bIsIsogram(sSelection));
        iSelectionLength = sSelection.length();
    } while (iSelectionLength > challengeNum +1);
    return sSelection; // Break and watch here to cheat
}

bool IsogramGame::bIsIsogram(FString testString)
{
    testString = sStringToLower(testString);
    std::map<char, bool> mObservedLetterTF;

    for (auto Letter : testString) {
        if (!mObservedLetterTF[Letter]) { mObservedLetterTF[Letter] = true; }
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
