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

// Avoids repeating chars by removing the repeated chars from the word then checking
void charRepeat(std::string guess, std::vector<char> &guesses) {
	for (int i = 0; i < guess.size(); i++) {
		int count = 0;
		for (int j = 0; j < guess.size(); j++) {
			if (guess[i] == guess[j]) {
				count++;
			}
			// remove repeated char from the string
			if (guess[i] == guesses[j] && count >= 1) {
				guess.erase(guess.begin() + j);
			}
		}
	}
	// append all of the chars in the string to the vector.
	for (char &c : guess) {
		guesses.push_back(c);
	}
}

int wordListAppender(std::vector<std::string> &list) {
	std::string word;
	std::ifstream inFile;
	inFile.open("wordleWordList.txt");
	if (!inFile) {
		std::cout << "File did not open." << "\n\n";
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
		if (guess.size() < 5) {
			std::cout << "Word is too short!" << "\n"; 
		} else {
			std::cout << "Word is too long!" << "\n"; 
		}
		std::cin >> guess;
		lowerCase(guess);
	}
	charCheckPrompt(guess);
}

int randomNumber() {
	srand (time(NULL));
	int rng = rand() % 12972 + 1;
    
    return rng;
}
// Needs Work
void vectorOutput(std::vector<char> list) {
	std::cout << "\n";	
	for (char &c : list) {
		std::cout << c;
	}
	std::cout << "\n";
}

void endGame(bool &currentGameRunning, bool &running) {
	std::string playAgain;
	std::cout << "Do you want to play again? (yes/no)" << "\n";
	std::cin >> playAgain;
	lowerCase(playAgain);
			
	if (playAgain == "yes") {
		currentGameRunning = false;
	} else {
		running = false;
		currentGameRunning = false;
	}
}

void wordCheck(std::string &guess) {
	lowerCase(guess);
	lenCheck(guess);
	charCheckPrompt(guess);
}

int main() {
	wordListAppender(wordList);

	bool running = true;
	int wins = 0;
	int bestWinStreak = 0;
	int gamesPlayed = 0;
	
	std::cout << "WORDLE: The Game" << "\n\n";
	
	// Main loop
	while (running) {
		std::vector<char> guesses;
		std::vector<char> greenChars;
		std::vector<char> yellowChars;
		int guessCount = 0;
		bool currentGameRunning = true;
		bool wordGuessed = false;
		
		int num = randomNumber();
		std::string randomWord = wordList[num];
		// Testing
		std::cout << randomWord << "\n";
		
		gamesPlayed += 1;
		
		// sub loop
		while (currentGameRunning) {
			int count = 0;
			std::string guess = "";
			
			std::cout << "Enter a five letter word." << "\n";
			std::cin >> guess;
			
			wordCheck(guess);
			
			while (!validityCheck(guess, wordList)) {
				std::cout << "Please enter a valid word." << "\n";
				std::cin >> guess;
				wordCheck(guess);
			}
			
			charRepeat(guess, guesses);
			
			std::cout << "Chars Guessed: " << "\n";
			vectorOutput(guesses);
			std::cout << "\n";
			
			guessCount += 1;
			
			/* 
			If the guess is not correct it shows how many are in the right spot
			and shows how many are in the word but not in the right spot
			
			#1 - Currently there is a bug where a green letter thats is supposed to be 
			     only green goes into the yellow list.
			 
			#2 - Can show multiple yellows for words that don't have that many letters. 
			     Ex: Word ~ Sista and guess ~ sissy
			     results in three yellows when there should be 2
			*/
			if (guess == randomWord) {
				wordGuessed = true;
			} else {
				for (int i = 0; i < guess.size(); i++) {
					for (int j = 0; j < randomWord.size(); j++) {
						// If the chars are the same letter and index it's a green
						if (guess[i] == randomWord[j] && i == j) {
							greenChars.push_back(guess[i]);
						} 
						else if (guess[i] == randomWord[i] && i != j) {
							yellowChars.push_back(guess[i]); 
						}
					}
				}	
			  }
			
			
			if (guessCount >= 6 || wordGuessed) {
				endGame(currentGameRunning, running);
			}
		}
	}
	std::cout << "\nWins: " << wins << "\n";
	std::cout << "Best Win Streak: " << bestWinStreak << "\n";
	std::cout << "Games Played: " << gamesPlayed << "\n";
	
	return 0;
}
