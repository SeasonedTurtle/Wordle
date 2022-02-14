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


bool charCheck(std::string guess) {
	int count = 0;
	std::string chars = "abcdefghijklmnopqrstuvwxyz";
	for (char &c : guess) {
		for (char &d : chars) { 
			if (c == d) {
				count += 1;
			}
		}
	}
	if (count >= 5) {
		return true;
	}
	return false;
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

void lowerCase(std::string &userInput) {
    std::for_each(userInput.begin(), userInput.end(), [](char & c) {
        c = ::tolower(c);
    });
}

void charCheckPrompt(std::string &guess) {
	while (!charCheck(guess)) {
		std::cout << "Please enter valid characters." << "\n";
		std::cin >> guess;
		lowerCase(guess);
	}
}

void lenCheck(std::string &guess) {
	while (guess.size() != 5) {
		std::cout << "Please enter a 5 letter word." << "\n";
		std::cin >> guess;
		lowerCase(guess);
		charCheckPrompt(guess);
	}
}

int randomNumber() {
	srand (time(NULL));
	int rng = rand() % 12972 + 1;
    
    return rng;
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

		std::cout << randomWord << "\n";

		gamesPlayed += 1;
		
		while (currentGameRunning) {
			int count = 0;
			std::string guess = "";
			std::cout << "Enter a five letter word." << "\n";
			std::cin >> guess;
			
			lowerCase(guess);
			charCheckPrompt(guess);
			lenCheck(guess);
			
			while (!validityCheck(guess, wordList)) {
				std::cout << "Please enter a valid word." << "\n";
				std::cin >> guess;
				lowerCase(guess);
				lenCheck(guess);
				charCheckPrompt(guess);
			}
			
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
			
			std::cout << guess << "\n";
			
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
	std::cout << "\nWins: " << wins << "\n";
	std::cout << "Best Win Streak: " << bestWinStreak << "\n";
	std::cout << "Games Played: " << gamesPlayed << "\n";
	
	return 0;
}
