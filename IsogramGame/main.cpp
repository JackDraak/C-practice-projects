/*
    Isogram Game
    based on https://www.udemy.com/unrealcourse/ by Ben Tristem (Thanks, Ben!)
    coded by Jack Draak
*/
#include <iostream>

using namespace std;

int main()
{
    int iWordLen = 9; // TODO iWordLen should be determined based on player level and/or score 
    cout << "INTRO: Thank you for playing my \'Guess the Isogram\' console game!\n";
    cout << " - what is an isogram?\n";
    cout << " - how do I play?\n";
    cout << "...details, detials... We'll get to that later!\n\n";
    cout << "Can you guess the " << iWordLen << " letter isogram that has been randomly pre-selected?";
    cout << endl;
    return 0;
}
