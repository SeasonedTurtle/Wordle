#include "consts.cpp"

/*
	Bugs: 	

	- Breaks the entire program if there are three of same letter in a guess 
	  or two or more letters within the word. Ex: Asses and Peeps
*/

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
				count++;
			}
		}
	}
	if (count >= 5) {
		return true;
	}
	return false;
}

/*  
	Avoids repeating chars by removing the repeated chars from the word then checking
	For Word Bank which will replicate the keyboard functionality

	- This could use a touch up as the two loops are practically the same
*/
void charRepeat(std::string guess, std::vector<char> &guesses, int round) {
	int size = guess.size();
	for (int i = 0; i < size; i++) {
		int count = 0;
		for (int j = 0; j < size; j++) {
			if (guess[i] == guess[j]) { count++; }
			// remove repeated char from the string
			if (guess[i] == guess[j] && count > 1) {
				guess.erase(guess.begin() + j);
			}
		}
	}
	// Epic way of checking if round == 0
	if (!round) {
		for (char &c : guess) {
			guesses.push_back(c);
		}
	} else {
		// Compare the letters in the vector with the chars in the guess
		for (char &c : guess) {
			int count = 0;
			for (char &d : guesses) {
				if (c == d) { count++; }
			}
			if (!count) {
				guesses.push_back(c);	
			}
		}
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
	int rng = rand() % 2315 + 1;
    
    return rng;
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
	charCheckPrompt(guess);
	lenCheck(guess);
}

void output(std::vector<char> vector) {
	for (char &c : vector) {
		std::cout << c << ", ";
	}
	std::cout << "\n\n";
}

// Returns a 2D Table of a vector
void grid(std::string guess, std::vector<std::vector<char>> &vect, int guessCount)
{
    std::string line = "__";
    int b = ROWS - 1;

	for (int i = guessCount - 1; i < guessCount; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			vect[i][j] = guess[j];
		}
	}

    for (int i = 0; i < ROWS; i++)
    {
        line.append("____"); 
    }

    for (int i = 0; i < COLUMNS; i++)
    {
        std::cout << line << "\n";
        for (int j = 0; j < ROWS; j++)
        {
			if (j == 0) 
			{
				std::cout << "| ";
			}
            if (j == b)
            {
                std::cout << vect[i][j] << "  |\n";
            }
            else 
            {
                std::cout << vect[i][j] << " | ";
            }
        }
    }
    std::cout << "\n";
}
