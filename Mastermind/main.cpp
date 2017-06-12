//
//  main.cpp
//  Mastermind
//
//  Created by Henrik Lehmann on 2017-05-16.
//  Copyright © 2017 Henrik Lehmann. All rights reserved.
//

#include <iostream>
#include "Game.hpp"

using namespace std;


void giveFeedback(int numOfCorrectLetters, int numOfMisplacedLetters);
void printGameInfoToUser();

int main(int argc, const char * argv[]) {
   srand((unsigned)time(NULL));
   Game theGame("fourLetterWords.txt");
   printGameInfoToUser();
   theGame.play();
   cout << theGame.getSecretCode() << endl;

   return 0;
}

// ------------------------------ Global methods ------------------------------
void printGameInfoToUser() {
   cout << "------------------ MASTERMIND ------------------\n" << endl;
   cout << "         Welcome to the game Mastermind\n"
      << "Try to guess the secret code that consists of a "
      << Game::LENGTH_OF_CODE << " letter word.\nYou will get feedback how "
      << "well your guess was:\n   " << "* = Correct letter.\n   "
      << "- = Letters that exists in code but are in wrong position.\n"
      << "   When you're correct you will get the number of guesses you needed"
      << endl << endl;

}
