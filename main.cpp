#include "util.cpp"

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
		std::string randomWord = validWords[num];

		// Testing
		std::cout << randomWord << "\n";
		
		gamesPlayed += 1;
		
		// Sub loop
		while (currentGameRunning) {
			std::string guess = "";
			
			std::cout << "Enter a five letter word." << "\n";
			std::cin >> guess;
			
			wordCheck(guess);
			
			while (!validityCheck(guess, wordList)) {
				std::cout << "Please enter a valid word." << "\n";
				std::cin >> guess;
				wordCheck(guess);
			}
			// Word Bank
			charRepeat(guess, guesses, guessCount);
			std::cout << "\nLetters Guessed:\n";
			output(guesses);
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
						// If the chars are the same letter and the same location in the word it's a green
						if (guess[i] == randomWord[j] && i == j) {
							greenChars.push_back(guess[i]);
						} 
						else if (guess[i] == randomWord[i] && i != j) {
							yellowChars.push_back(guess[i]); 
							break;
						}
					}
				}	
			  }
			// Testing
			std::cout << "\nGreen Letters:\n";
			output(greenChars);

			std::cout << "\nYellow Letters:\n";
			output(yellowChars);

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
