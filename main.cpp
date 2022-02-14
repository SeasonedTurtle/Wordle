#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>

std::vector<std::string> wordList;

bool validityCheck(std::string guess, std::vector<std::string> list) {
	int count = 0;
	for (std::string &w : list) {
		if (guess == w) {
			count++;
		}
	}
	if (count > 0) {
		return true;
	}
	return false;
}

void lowerCase(std::string &userInput) {
    std::for_each(userInput.begin(), userInput.end(), [](char & c) {
        c = ::tolower(c);
    });
}

void lenCheck(std::string &guess) {
	while (guess.size() != 5) {
		if (guess.size() < 5) {
			std::cout << "The word you entered is too short!" << "\n";
		} else {
			std::cout << "The word you entered is too long!" << "\n";
		} 
		std::cin >> guess;
		lowerCase(guess);
	}
}

int randomNumber() {
	srand (time(NULL));
    int rng = rand() % 12972 + 1;
    
    return rng;
}

int wordListAppender(std::vector<std::string> &list) {
	std::string word;
	std::ifstream inFile;
	inFile.open("wordleWordList.txt");
	if (!inFile) {
		std::cout << "File did not open."
				  << "Program Terminated." 
				  << "\n";
		return 1;
	}
	while (!inFile.eof()) {
		inFile >> word;
		list.push_back(word);
	}
	inFile.close();

	return 0;
}

int main() {
	wordListAppender(wordList);

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
		
		int num = randomNumber();
		std::string randomWord = wordList[num];

		std::cout << randomWord;

		gamesPlayed += 1;

		while (currentGameRunning) {
			int count = 0;
			std::string guess = "";
			std::cout << "Enter a five letter word." << "\n";
			std::cin >> guess;
			
			lowerCase(guess);
			lenCheck(guess);
				while (!validityCheck(guess, wordList)) {
					std::cout << "Please enter a valid word." << "\n";
					std::cin >> guess;
					lowerCase(guess);
					lenCheck(guess);
				}

			guessCount += 1;
			
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

