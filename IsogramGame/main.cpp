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
string GetGuess();

// Application Entry-Point
int main()
{
    string sGuess = "";

    PrintIntro();
    sGuess = GetGuess();

    // Repeat Player Guess
    cout << "\nYour guess was: " << sGuess << ", was it not?";
    cout << endl;

    return 0;
}

// Implementation of functions
void PrintIntro()
{
    // Game Intro
    int iWordLen = 9; // TODO iWordLen should be determined based on player level and/or score 
    cout << "INTRO: Thank you for playing my \'Guess the Isogram\' console game!\n";
    cout << " - what is an isogram?\n";
    cout << " - how do I play?\n";
    cout << "...details, detials... We'll get to that later!\n\n";
    cout << "Can you guess the " << iWordLen << " letter isogram that has been randomly pre-selected?";
    cout << endl;
}

string GetGuess() 
{
    // Get Player Guess
    string sGuess = "";
    cout << "Please, enter your guess now: ";
    getline(cin, sGuess);
    string Valid_Guess = sGuess; // TODO implement validation
    return Valid_Guess;
}
