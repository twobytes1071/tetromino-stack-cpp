#include <iostream>
#include <algorithm>
#include "board.hpp"

// displays a welcome message, continuing after user input
void welcome();

// clears the console screen by displaying new lines
void clear_screen();

// gets user input, enforcing specific choices
std::string user_input(const std::string& message, std::vector<std::string> valid_user_inputs);

// gets the last character of user input, enforcing specific choices
std::string game_input(const std::string& message, std::vector<std::string> valid_user_inputs);

int main() {
	welcome();
	int high_score{0};
	bool continue_playing{true};
	do {
		Board board = Board();
		int score{0};
		while (!board.game_over()) {
			if (!board.get_has_active_piece())
				board.summon_new_piece();
			clear_screen();
			board.display(score, high_score);
			std::string user_input = game_input("Make your move: ", Board::valid_user_inputs);
			board.move_piece(user_input);
			if (!board.get_has_active_piece()) {
				score += board.clear_full_rows();
				if (score > high_score)
					high_score = score;
			}
		}
		clear_screen();
		board.display(score, high_score);
		std::cout << "Game over! Score: " << score << std::endl;
		if (user_input("Press [ENTER] to play again. Type 'quit' to exit. ", {"", "quit"}) == "quit")
			continue_playing = false;
	} while (continue_playing);
	return 0;
}

void welcome() {
	std::cout << "Welcome to Tetronimo Stack!\n\nBlocky pieces will fall from the top, and the goal is to stack them as neatly as possible. "
				 "Every complete row will disappear to make room for more blocks. The game ends when the blocks stack too high; keep them below the line!\n\n"
				 "Scoring:\nSingle row clear:     10 points\nDouble row clear:     40 points\nTriple row clear:     90 points\nQuadruple row clear:  160 points\n\n"
				 "Controls:\n[A]:      Move left\n[D]:      Move right\n[Q]:      Rotate counterclockwise\n[E]:      Rotate clockwise\n[S]:      Drop to bottom\n[ENTER]:  Drop one space\n\n"
				 "Press [ENTER] to start. ";
	std::string input{};
	std::getline(std::cin, input);
}

void clear_screen() {
	for (int i{0}; i < 30; ++i) {
		std::cout << "\n";
	}
	std::cout << std::endl;
}

std::string user_input(const std::string& message, std::vector<std::string> valid_user_inputs) {
	std::string user_input{};
	do {
		std::cout << message;
		std::getline(std::cin, user_input);
	} while (std::find(valid_user_inputs.begin(), valid_user_inputs.end(), user_input) == valid_user_inputs.end());
	return user_input;
}

std::string game_input(const std::string& message, std::vector<std::string> valid_user_inputs) {
	std::string user_input{};
	do {
		std::cout << message;
		std::getline(std::cin, user_input);
		if (user_input.length() >= 1)
			user_input = user_input.back();
	} while (std::find(valid_user_inputs.begin(), valid_user_inputs.end(), user_input) == valid_user_inputs.end());
	return user_input;
}
