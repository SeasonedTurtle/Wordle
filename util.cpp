#include "consts.cpp"

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
	int size = guess.size();
	for (int i = 0; i < size; i++) {
		int count = 0;
		for (int j = 0; j < size; j++) {
			if (guess[i] == guess[j]) {
				count++;
			}
			// remove repeated char from the string
			if (guess[i] == guess[j] && count > 1) {
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
	int size = guess.size();
	while (size != 5) {
		if (size < 5) {
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