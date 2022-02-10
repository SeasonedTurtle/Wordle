#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>

void wordListAppender(std::vector<std::string> &list) {
	std::ifstream inFile;
	inFile.open("wordleWordList.txt");
	inFile.close();
}

void lenCheck(std::string &guess) {
	while (guess.size() != 5) {
		std::cout << "Please enter a 5 letter word." << "\n";
		std::cin >> guess;
	}
}

void lowerCase(std::string &userInput) {
    std::for_each(userInput.begin(), userInput.end(), [](char & c) {
        c = ::tolower(c);
    });
}

bool validityCheck(std::string guess) {
	// Loop through entire text file and check if the guessed word is one of them
	// If it's not, then return false otherwise return true
	return false;
}

int randomNumber() {
	srand (time(NULL));
    int rng=rand() %12972 + 1;
    
    return rng;
}

int main() {
	std::vector<std::string> wordList;
	
	bool running = true;
	int wins = 0;
	int bestWinStreak = 0;
	int gamesPlayed = 0;
	
	std::cout << "WORDLE: The Game" << "\n\n";
	
	while (running) {
		std::vector<char> guesses;
		int guessCount = 0;
		bool currentGameRunning = true;
		bool wordGuessed = false;
		char playAgain;
		//int randomIndex = std::experimental::randint(100, 999);
		//std::string randomWord = wordList[randomIndex];
		int num = randomNumber();
		std::cout << num << "\n";
		gamesPlayed += 1;
		
		while (currentGameRunning) {
			int count = 0;
			std::string guess = "";
			std::cout << "Enter a five letter word." << "\n";
			std::cin >> guess;
			
			lowerCase(guess);
			lenCheck(guess);
			
			/*
			if (!validityCheck(guess)) {
				std::cout << "Please enter a valid word." << "\n";
				std::cin >> guess;
				lowerCase(guess);
			} 
			*/
			
			guessCount += 1;
			
			/*
			for (char &c : guess) {
				for (char &d: guesses) {
					if (c != d) {
						int count += 1;
					} 
					if (count == 0) {
						guesses.push_back(c);
					}
				}
			}
			*/
			
			for (int i = 0; i < guess.size(); i++) {
				std::cout << guess[i];
			}
			
			if (guessCount >= 6 || wordGuessed) {
				std::cout << "Do you want to play again? (y/n)" << "\n";
				std::cin >> playAgain;
				lowerCase(guess);
				
				if (playAgain == 'y') {
					currentGameRunning = false;
				} else {
					running = false;
					currentGameRunning = false;
				}
			}
		}
	}
	std::cout << "Wins: " << wins << "\n";
	std::cout << "Best Win Streak: " << bestWinStreak << "\n";
	std::cout << "Games Played: " << gamesPlayed << "\n";
	
	return 0;
}

