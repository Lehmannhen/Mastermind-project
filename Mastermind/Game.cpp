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

int Game::numOfCorrectLetters(bool isCorrect[]) {
   int numOfCorrectLetters = 0;
   for (int i = 0; i < secretCode.length(); i++) {
      if (secretCode[i] == toupper(userGuess[i])) {
         isCorrect[i] = true;
         numOfCorrectLetters++;
      }
      else {
         isCorrect[i] = false;
      }
   }
   return numOfCorrectLetters;
}

int Game::numOfMisplacedLetters(bool isCorrect[]) {
   int numOfMisplacedLetters = 0;
   bool isGuessMarked[LENGTH_OF_CODE];
   bool isCodeMarked[LENGTH_OF_CODE];

   for (int i = 0; i < LENGTH_OF_CODE; i++) {
      if (isCorrect[i]) {
         isGuessMarked[i] = true;
         isCodeMarked[i] = true;
      }
      else {
         isGuessMarked[i] = false;
         isCodeMarked[i] = false;
      }
   }
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

void Game::play() {
   int blackPegs = 0;
   int whitePegs = 0;
   int numberOfTries = 0;
   bool isCorrect[LENGTH_OF_CODE];
   setSecretCode();
   while (true) {
      setUserGuess(getGuessFromUser());
      blackPegs = numOfCorrectLetters(isCorrect);
      whitePegs = numOfMisplacedLetters(isCorrect);
      giveFeedback(blackPegs, whitePegs);
      numberOfTries++;
      if (blackPegs == LENGTH_OF_CODE) {
         cout << "Congratulations you got it! It took you " << numberOfTries
         << " tries!" << endl << endl;
         break;
      }
   }
}
