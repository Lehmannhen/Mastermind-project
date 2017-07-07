//
//  Game.cpp
//  Mastermind
//
//  Created by Henrik Lehmann on 2017-05-16.
//  Copyright © 2017 Henrik Lehmann. All rights reserved.
//

#include "Game.hpp"
#include <fstream>
#include <vector>

using namespace std;

Game::Game(string fileName) {
   setWordsInGame(fileName);   
}

bool Game::setWordsInGame(string fileName) {
   string line;
   ifstream myFile(fileName);

   if (!myFile){
      return false;
   }
   while (getline(myFile, line)) {
      this->wordsInGame.push_back(line);
   }
   myFile.close();
   return true;
}

bool Game::setSecretCode() {
   if (wordsInGame.size() <= 0) {
      return false;
   }
   this->secretCode = wordsInGame[rand() % wordsInGame.size()];
   return true;
}

bool Game::setUserGuess(string userGuess) {
   if (!isValidString(userGuess)) {
      return false;
   }
   this->userGuess = userGuess;
   return true;
}

bool Game::isValidString(string theString) {
   if (theString.length() != LENGTH_OF_CODE) {
      return false;
   }
   return true;
}

int Game::numOfCorrectLetters(bool isCodeMarked[], bool isGuessMarked[]) {
   int numOfCorrectLetters = 0;
   
   for (int i = 0; i < secretCode.length(); i++) {
      if (secretCode[i] == toupper(userGuess[i])) {
         isCodeMarked[i] = true;
         isGuessMarked[i] = true;
         numOfCorrectLetters++;
      }
      else {
         isCodeMarked[i] = false;
         isGuessMarked[i] = false;
      }
   }
   return numOfCorrectLetters;
}

int Game::numOfMisplacedLetters(bool isCodeMarked[], bool isGuessMarked[]) {
   int numOfMisplacedLetters = 0;

   for (int i = 0; i < LENGTH_OF_CODE; i++) {
      for (int j = 0; j < LENGTH_OF_CODE; j++) {
         if ((secretCode[i] == toupper(userGuess[j])) &&
            (!isCodeMarked[i] && !isGuessMarked[j])) {
            isCodeMarked[i] = true;
            isGuessMarked[j] = true;
            numOfMisplacedLetters++;
         }
      }
   }
   return numOfMisplacedLetters;
}

string Game::getGuessFromUser() {
   string userGuess = "";
   while(true) {
      cout << "Enter a 4 letter word as a guess: ";
      getline(cin, userGuess);
      if (!isValidString(userGuess)) {
         cout << "Word must be of length " << LENGTH_OF_CODE << endl;
         continue;
      }
      break;
   }
   return userGuess;
}

void Game::giveFeedback(int numOfCorrectLetters, int numOfMisplacedLetters) {
   string feedback = "";

   if ((numOfCorrectLetters == 0) && (numOfMisplacedLetters == 0)) {
      cout << "You have no correct pegs " << endl;
      return;
   }
   for (int i = 0; i < numOfCorrectLetters; i++) {
      feedback += "*";
   }
   for (int j = 0; j < numOfMisplacedLetters; j++) {
      feedback += "-";
   }
   cout << feedback << endl;
}

void Game::printGameInfoToUser() {
   cout << "------------------ MASTERMIND ------------------\n" << endl;
   cout << "         Welcome to the game Mastermind\n"
      << "Try to guess the secret code that consists of a "
      << Game::LENGTH_OF_CODE << " letter word.\nYou will get feedback how "
      << "well your guess was:\n   " << "* = Correct letter.\n   "
      << "- = Letters that exists in code but are in wrong position.\n"
      << "   When you're correct you will get the number of guesses you needed"
      << endl << endl;
}

void Game::play() {
   int blackPegs = 0;
   int whitePegs = 0;
   int numberOfTries = 0;
   bool isCodeMarked[LENGTH_OF_CODE];
   bool isGuessMarked[LENGTH_OF_CODE];
   if (!setSecretCode()) {
      cout << "Couldn't find file" << endl;
      return;
   }
   
   while (true) {
      setUserGuess(getGuessFromUser());
      blackPegs = numOfCorrectLetters(isCodeMarked, isGuessMarked);
      whitePegs = numOfMisplacedLetters(isCodeMarked, isGuessMarked);
      giveFeedback(blackPegs, whitePegs);
      numberOfTries++;
      if (blackPegs == LENGTH_OF_CODE) {
         cout << "Congratulations you got it! It took you " << numberOfTries
            << " tries!" << endl << endl;
         break;
      }
   }
}
