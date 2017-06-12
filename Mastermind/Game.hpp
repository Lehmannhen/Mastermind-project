//
//  Game.hpp
//  Mastermind
//
//  Created by Henrik Lehmann on 2017-05-16.
//  Copyright © 2017 Henrik Lehmann. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class Game {
private:
   string secretCode;
   string userGuess;
   vector<string> wordsInGame;

public:
   static const int LENGTH_OF_CODE = 4;

   // constructor
   Game(string fileName);

   // Game methods
   string getGuessFromUser();
   void giveFeedback(int numOfCorrectLetters, int numOfMisplacedLetters);
   void play();
   string getUserGuess();
   static bool isValidString(string theString);
   int numOfCorrectLetters(bool isCorrect[]);
   int numOfMisplacedLetters(bool isCorrect[]);

   // accessors and mutators
   bool setWordsInGame(string fileName);
   bool setSecretCode();
   bool setUserGuess(string userGuess);
   vector<string> getWordsInGame() { return wordsInGame; }
   string getSecretCode() { return secretCode; }

};
#endif /* Game_hpp */
