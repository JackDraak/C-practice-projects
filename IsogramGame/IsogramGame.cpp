#pragma once
#include "IsogramGame.h"

IsogramGame::IsogramGame()                          { Reset(); return; }

bool IsogramGame::bIsGuessMatch() const             { return bDoesGuessMatch; }
FString IsogramGame::sGetIsogram() const            { return sIsogram; }
int32 IsogramGame::zGetDifficulty() const           { return zMode; }
int32 IsogramGame::iGetCurrentGuessNum() const      { return iCurrentGuess; }
int32 IsogramGame::iGetIsogramLength() const        { return sIsogram.length(); }
int32 IsogramGame::iGetLossCount() const            { return iLossCount; }
int32 IsogramGame::iGetPhaseScore() const           { return iPhaseScore; }
int32 IsogramGame::iGetRunningGuesses() const       { return iRunningGuesses; }
int32 IsogramGame::iGetRunningScore() const         { return iRunningScore; }
int32 IsogramGame::iGetWinCount() const             { return iWinCount; }
void IsogramGame::IncrementGuess()                  { iCurrentGuess++; return; }
void IsogramGame::IncrementLoss()                   { iLossCount++; return; }
void IsogramGame::FudgeGuesses()                    { iCurrentGuess--; return; }
void IsogramGame::SetEasy()                         { zMode = 1; return; }
void IsogramGame::SetHard()                         { zMode = 3; return; }
void IsogramGame::SetNormal()                       { zMode = 2; return; }

// Initialize new game or setup for next round.
void IsogramGame::Reset()
{
    if (!bInitialized) 
    {
        bDisplayClues = true;
        bDisplayLetterbox = true;
        bInitialized = true;
        bValidated = false;
        bValidDictionary = false;
        iLossCount = 0;
        iPhaseScore = 0;
        iWinCount = 0;
        zMode = 2; // Difficulty: 1 = easy, 2 = normal, 3 = hard
    }
    iCurrentGuess = 1;
    sIsogram = sSelectIsogram(iGetChallengeSize());
    return;
}

// Update total score, then reset round-score. (Also track total guesses).
void IsogramGame::Tally()
{
    iRunningScore += iPhaseScore;
    iRunningGuesses += iGetCurrentGuessNum();
    iPhaseScore = 0;
    return;
}

// Respond with # of guesses based on length of challenge word (& difficulty setting).
int32 IsogramGame::iGetMaxGuesses() const
{
    int32 iWordSize;

    if (zMode == 1) // Easy difficulty map
    {
        std::map <int32, int32> mWordSizeToGuessCount{
            { 2,10 },{ 3,9 },  { 4,10 },{ 5,11 },{ 6,11 },{ 7,11 },{ 8,11 },
            { 9,11 },{ 10,10 },{ 11,9 },{ 12,8 },{ 13,7 },{ 14,6 },{ 15,5 },
            { 16,4 },{ 17,4 }
    };
    iWordSize = mWordSizeToGuessCount[sGetIsogram().length()];
    }
    else if (zMode == 3) // Hard difficulty map
    {
        std::map <int32, int32> mWordSizeToGuessCount{
            { 2,5 }, { 3,4 }, { 4,4 }, { 5,5 }, { 6,6 }, { 7,6 }, { 8,6 },
            { 9,5 }, { 10,5 },{ 11,4 },{ 12,4 },{ 13,3 },{ 14,3 },{ 15,2 },
            { 16,2 },{ 17,2 }
        };
        iWordSize = mWordSizeToGuessCount[sGetIsogram().length()];
    }
    else if (zMode == 2) // Normal difficulty map
    {
        std::map <int32, int32> mWordSizeToGuessCount{
            { 2,7 }, { 3,6 }, { 4,7 }, { 5,8 }, { 6,9 }, { 7,9 }, { 8,9 },
            { 9,8 }, { 10,7 },{ 11,6 },{ 12,5 },{ 13,4 },{ 14,3 },{ 15,3 },
            { 16,3 },{ 17,3 }
        };
        iWordSize = mWordSizeToGuessCount[sGetIsogram().length()];
    }
        return iWordSize;
}

// Respond with maximum challenge-word size. Higher total scores give bigger challenges (longer words).
int32 IsogramGame::iGetChallengeSize() const 
{
    if      (iRunningScore < 35)        { return 3; }
    else if (iRunningScore < 35*3)      { return 4; }
    else if (iRunningScore < 35*5)      { return 5; }
    else if (iRunningScore < 35*9)      { return 6; }
    else if (iRunningScore < 35*17)     { return 7; }
    else if (iRunningScore < 35*33)     { return 8; }
    else if (iRunningScore < 35*65)     { return 9; }
    else if (iRunningScore < 35*129)    { return 10; }
    else if (iRunningScore < 35*257)    { return 11; }
    else if (iRunningScore < 35*513)    { return 12; }
    else if (iRunningScore < 35*1025)   { return 13; }
    else if (iRunningScore < 35*2049)   { return 14; }
    else if (iRunningScore < 35*4097)   { return 15; }
    else if (iRunningScore < 35*8193)   { return 16; }
    else                                { return 17; }
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
                // ----- Setup a score multiplier considering: difficulty, use of clues, use of letterbox ----- //
                int32 iMultiplier = 1;
                if (bDisplayClues) { iMultiplier++; };
                if (bDisplayLetterbox) { iMultiplier++; };
                iMultiplier += zMode; // add factor for difficulty setting

                if (!bLetterScore && bPositionScore)         { iPhaseScore = iPhaseScore + (3 * iMultiplier); }
                else if (bLetterScore && !bPositionScore)    { iPhaseScore = iPhaseScore + (1 * iMultiplier); }
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
        // 2
        "as", "at", "be", "do", "go", "he", "id", "is", "it", "no", "on", "so", "to", "we",
     
        // 3
        "age", "art", "bag", "bat", "boy", "bye", "car", "coy", "cry", "cut", "day", "dim", "din", "elf", "fit", "fly", 
        "hit", "hug", "jam", "kit", "lab", "lax", "lie", "lit", "lot", "mar", "may", "mit", "net", "nip", "par", "pay", 
        "pie", "pot", "put", "rag", "ray", "rot", "say", "sea", "sin", "tag", "tax", "tea", "the", "try", "was", "yam",

        // 4
        "acre", "ages", "army", "aunt", "bail", "bale", "belt", "care", "cave", "cure", "daft", "damn", "dart", "dime", "expo", "fair",
        "fast", "fawn", "felt", "fish", "from", "hair", "hare", "harp", "hear", "help", "hide", "huge", "jail", "july", "june", "lair", 
        "land", "lend", "lint", "love", "lynx", "lyre", "name", "nape", "navy", "nose", "oven", "pair", "pure", "raid", "rail", "same",
        "sail", "sand", "sock", "soda", "sold", "soup", "suit", "talk", "tiny", "this", "tone", "tray", "tuna", "walk", "wasp", "wave", 
        "yarn", 

        // 5
        "angel", "anger", "angry", "ankle", "april", "blast", "braid", "bread", "brick", "brush", "clear", "cloth", "drain", 
        "dregs", "dwarf", "empty", "enact", "envoy", "facts", "fairy", "faith", "farce", "farms", "gravy", "hares", "large", 
        "laugh", "light", "lingo", "litre", "lives", "loads", "locks", "march", "marsh", "miles", "money", "nasty", "nurse", "pious",
        "query", "rages", "roads", "roast", "sable", "scone", "shock", "sight", "snout", "stand", "stick", "super", "swift", 
        "table", "talks", "tango", "thick", "thing", "timer", "toads", "tongs", "trash", "trick", "tuber", "tuner", "vegan", 
        "yeast", "tiger", "large", 

        // 6
        "hybrid", "fabric", "sculpt", "sample", "baster", "turkey", "cables", "dearly", "placid", "dancer", "danger",
        "jaunts", "abound", "tricks", "bricks", "crawls", "crowns", "around", "orgasm", "bounty", "gizmos", "zealot",
        "travel", "wealth", "second", "curled", "loving", "belfry", "fables", "factor", "fairly", "famine", "bronze",
        "farces", "nailed", "nebula", "nickel", "muster", "buster", "myrtle", "nachos", "mythos", "phrase", "quartz",
        "tackle", "sunday", "monday", "friday", "custom", "quaint", "guitar", "slight", "bright", "danger", "design", 
        "sailor", "market", "tongue", "sucker", 

        // 7
        "jukebox", "ziplock", "lockjaw", "quickly", "crazily", "jaybird", "jackpot", "quicken", "quicker", "imports",
        "clothes", "polearm", "jockeys", "subject", "cliquey", "apricot", "anxiety", "domains", "dolphin", "exclaim",
        "fabrics", "factory", "haircut", "pulsing", "scourge", "schlump", "turbine", "wrongly", "wyverns", "yoghurt",
        "isogram", "mindful", "scholar", "stymied", "caribou", "consume", "nostril", "monarch", "sketchy", "smoking",
        "sparkle", "scarlet", "treason", "strange",

        // 8
        "exoplasm", "exploits", "explains", "exhaling", "handgrip", "hardiest", "hasteful", "megalith", "megatons",
        "sculptor", "minerals", "crumpets", "goldfish", "blasting", "monarchy", "rambling", "informed", "emblazon",
        "frontage", "thursday", "authored", "bankrupt", "hospital", "imported", "questing", "finagled", "question",
        "spectrum", "bunghole", "burliest", "bushland", "jockular", "gumption", "pronated", "bushmeat", "buxomest",
        "butchery", "cogently", "merciful", "minerals", "speaking", "busywork",

        // 9
        "yachtsmen", "worshiped", "workspace", "womanizer", "wolfsbane", "windstorm", "dangerous",
        "workmates", "wordgames", "inspector", "constable", "ramblings", "traveling", "vulcanism",
        "authorize", "waveforms", "binocular", "watchdogs", "vulgarity", "introduce", "nightmare", 
        "wavefront", "welcoming", "vouchsafe", "verbosity", "veracious", "uncharted", "unclamped", 
        "tribunals", "solarized", "solemnity", "revolting", "redaction", "racheting", "traveling",
        "dragonfly",

        // 10
        "abductions", "hospitable", "background", "campground", "greyhounds", "infamously", "afterglows", "shockingly",
        "duplicates", "authorizes", "farsighted", "binoculars", "destroying", "subjectify", "algorithms", "nightmares",
        "aftershock", "agonizedly", "birthnames", "benchmarks", "behaviours", "background", "capsulized", "chlorinate",
        "chipboards", "chalkstone", "exhaustion", "exfoliants", "gobsmacked", "graciously", "sympathize",
       
        // 11
        "workmanship", "palindromes", "speculation", "trampolines", "personality", "sympathizer", "abolishment", "atmospheric",
        "playgrounds", "backgrounds", "countryside", "birthplaces", "precautions", "regulations", "subcategory", "documentary",
        "birthplaces", "bodysurfing", "cabinetwork", "backlighted", "decryptions", "designatory", "delusionary", "sympathizer",
        "demographic", "discernably", "exculpatory", "factorylike", "flavourings", "francophile", "dangerously", 

        // 12
        "malnourished", "counterplays", "multipronged", "unforgivable", "subvocalized", "pyromagnetic", "stenographic",
        "productively", "stickhandler", "subnormality", "nightwalkers", "outsparkling", "locksmithery", "discountable",
        "descrambling", "overstudying", "demonstrably", "demographics", "exhaustingly", "discrepantly", "upholstering",
        "packinghouse", "questionably", "thunderclaps", "unprofitable", "lexicography",
       
        // 13
        "misconjugated", "unproblematic", "subordinately", "draughtswomen", "flowchartings", "lycanthropies", "pneumogastric", "salpingectomy",
        "subordinately", "flamethrowing", "unmaledictory", "muckspreading", "unsympathized", "unpredictably", "multibranched", "consumptively",
        "metalworkings", "musicotherapy", "chimneyboards", "copyrightable", "documentarily", "draughtswomen", "pneumogastric", "salpingectomy",

        // 14
        "ambidextrously", "hydromagnetics", "pseudomythical", "ambidextrously", "undiscoverably", "dermatoglyphic", 
        "computerizably", "subformatively", "hydropneumatic", 

        // 15 -- categories of one word are not very replayable.....  buuuut it's unlikely anyone will ever play this long, lol
        "uncopyrightable",

        // 17
        "subdermatoglyphic"
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

