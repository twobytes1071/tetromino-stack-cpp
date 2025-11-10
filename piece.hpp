#ifndef PIECE_HPP
#define PIECE_HPP

#include <vector>

// represents an active game piece as a square bitmap
class Piece {
public:

	// a list of all valid piece configurations, not accounting for rotational symmetry
	static const std::vector<std::vector<std::vector<bool>>> valid_piece_conigurations;

private:

	// a bitmap representing the shape of the piece
	std::vector<std::vector<bool>> configuration;

	// the i-position of the piece on the board
	int i_position;

	// the j-position of the piece on the board
	int j_position;

public:

	Piece();

	// randomizes the configuration and rotation of the piece and places it in the top-middle of the board
	void new_piece_setup(int board_length_j);

	// moves the piece left
	void move_left();

	// moves the piece right
	void move_right();

	// moves the piece down
	void move_down();

	// rotates the piece counterclockwise
	void rotate_clockwise();

	// rotates the piece clockwise
	void rotate_counterclockwise();

	// returns true if the piece in its current location does not overlap any fallen pieces on the board
	bool valid_position(const std::vector<std::vector<bool>>& board) const;

	// places the piece on the board as a fallen piece
	void imprint(std::vector<std::vector<bool>>& board) const;

};

#endif // PIECE_HPP
