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

class Game {
private:
   std::string secretCode;
   std::string userGuess;
   std::vector<std::string> wordsInGame;

public:
   static const int LENGTH_OF_CODE = 4;

   // constructor
   Game(std::string fileName);

   // Game methods
   std::string getGuessFromUser();
   void giveFeedback(int numOfCorrectLetters, int numOfMisplacedLetters);
   void play();
   std::string getUserGuess();
   static bool isValidString(std::string guess);
   static void printGameInfoToUser();
   int numOfCorrectLetters(bool isCodeMarked[], bool isGuessMarked[]);
   int numOfMisplacedLetters(bool isCodeMarked[], bool isGuessMarked[]);

   // accessors and mutators
   bool setWordsInGame(std::string fileName);
   bool setSecretCode();
   bool setUserGuess(std::string userGuess);
   std::vector<std::string> getWordsInGame() { return wordsInGame; }
   std::string getSecretCode() { return secretCode; }

};
#endif /* Game_hpp */
