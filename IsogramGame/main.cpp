/*
    Isogram Game
    based on https://www.udemy.com/unrealcourse/ by Ben Tristem (Thanks, Ben!)
    coded by Jack Draak
*/
#include <iostream>
#include <string>

using namespace std;

// function prototypes
void PrintIntro();
void PlayGame();
string GetGuess();
void PrintGuess(string);
bool bContinuePlaying();

// application entry-point
int main()
{
    PrintIntro();
    do 
    {
        PlayGame();
    } 
    while (bContinuePlaying() == true);

    return 0;
}

void PlayGame()
{
    constexpr int cMaxGuesses = 5;
    string sGuess = "";

    for (int i = 1; i <= cMaxGuesses; i++)
    {
        sGuess = GetGuess();
        PrintGuess(sGuess);
        cout << endl;
    }
}


// method implenentations
bool bContinuePlaying()
{
    cout << "\nWould you like to continue playing?\n";
    string sResponce = "";
    getline(cin, sResponce);
    if ((sResponce[0] == 'y') || (sResponce[0] == 'Y')) { return true; }
    return false; // implicit else
}

void PrintIntro()
{
    int iWordLen = 9; // TODO iWordLen should be determined based on player level and/or score 
    cout << "INTRO: Thank you for playing my \'Guess the Isogram\' console game!\n";
    cout << " - what is an isogram?\n";
    cout << " - how do I play?\n";
    cout << "...details, detials... We'll get to that later!\n\n";
    cout << "Can you guess the " << iWordLen << " letter isogram that has been randomly pre-selected?";
    cout << endl;
}

void PrintGuess(string sGuess)
{
    cout << "\nYour guess was: " << sGuess << ", was it not?";
    cout << endl;
}

string GetGuess() 
{
    string sGuess = "";
    cout << "Please, enter your guess now: ";
    getline(cin, sGuess);
    string Valid_Guess = sGuess; // TODO implement validation
    return Valid_Guess;
}
