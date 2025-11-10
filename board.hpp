#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <string>
#include "piece.hpp"

// represents the playing board as a bitmap of fallen pieces and an actively falling piece
class Board {
public:

	// a list of all valid movement inputs
	static const std::vector<std::string> valid_user_inputs;

private:

	// the height of the board
	const int length_i;

	// the i-position of the maximum height of the stack before ending the game
	const int max_fill_line;

	// the width of the board
	const int length_j;

	// a bitmap representing the locations of previously-fallen pieces
	std::vector<std::vector<bool>> board;

	// the piece being actively moved by the player
	Piece active_piece;

	// a flag representing whether an active piece is in play
	bool has_active_piece;

public:

	Board();

	// prints the entire game screen to the console
	void display(const int score, const int high_score) const;

	// creates a new active piece at the top of the board
	void summon_new_piece();

	// applies the user's input to move the active piece
	void move_piece(const std::string& user_input);

	// clears all complete rows from the board, shifting higher rows downward
	// returns the score corresponding to the amount of rows cleared
	int clear_full_rows();

	// returns has_active_piece
	bool get_has_active_piece() const;

	// returns true when a fallen piece has reached the max fill line
	bool game_over() const;

};

#endif // BOARD_HPP
