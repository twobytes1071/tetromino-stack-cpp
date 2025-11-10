#include "board.hpp"
#include <iostream>
#include <vector>
#include <string>

const std::vector<std::string> Board::valid_user_inputs {"a", "d", "s", "q", "e", " ", ""};

Board::Board()
	: length_i{16}, max_fill_line{3}, length_j{10},
	board(length_i, std::vector<bool>(length_j, false)), active_piece(), has_active_piece{false} {}

void Board::display(const int score, const int high_score) const {
	std::vector<std::vector<bool>> display_board = board;
	if (has_active_piece)
		active_piece.imprint(display_board);
	for (int i{0}; i < display_board.size(); ++i) {
		if (i == max_fill_line)
			std::cout << "--";
		else
			std::cout << " |";
		for (const bool square: display_board.at(i)) {
			if (square == true)
				std::cout << "##";
			else
				std::cout << "  ";
		}
		if (i == max_fill_line)
			std::cout << "-- Score:       " << score << std::endl;
		else if (i == max_fill_line + 1)
			std::cout << "|  High Score:  " << high_score << std::endl;
		else
			std::cout << "| " << std::endl;
	}
	for (int i{0}; i < length_j + 2; ++i)
		std::cout << "--";
	std::cout << std::endl;
}

void Board::summon_new_piece() {
	active_piece = Piece();
	active_piece.new_piece_setup(length_j);
	has_active_piece = true;
}

void Board::move_piece(const std::string& user_input) {
	Piece move_projection_piece = active_piece;
	if (user_input == "a") {
		move_projection_piece.move_left();
		if (move_projection_piece.valid_position(board))
			active_piece.move_left();
	} else if (user_input == "d") {
		move_projection_piece.move_right();
		if (move_projection_piece.valid_position(board))
			active_piece.move_right();
	} else if (user_input == "s") {
		move_projection_piece.move_down();
		while (move_projection_piece.valid_position(board)) {
			active_piece.move_down();
			move_projection_piece.move_down();
		}
	} else if (user_input == "q") {
		move_projection_piece.rotate_counterclockwise();
		if (move_projection_piece.valid_position(board))
			active_piece.rotate_counterclockwise();
	} else if (user_input == "e") {
		move_projection_piece.rotate_clockwise();
		if (move_projection_piece.valid_position(board))
			active_piece.rotate_clockwise();
	}
	move_projection_piece = active_piece;
	move_projection_piece.move_down();
	if (move_projection_piece.valid_position(board)) {
		active_piece.move_down();
	} else {
		active_piece.imprint(board);
		has_active_piece = false;
	}
}

int Board::clear_full_rows() {
	int rows_cleared{0};
	for (int i{0}; i < board.size(); ++i) {
		bool full_row = true;
		for (int j{0}; j < board.at(i).size(); ++j) {
			if (board.at(i).at(j) == false) {
				full_row = false;
				break;
			}
		}
		if (full_row) {
			for (int i2{i}; i2 > 0; --i2)
				for (int j2{0}; j2 < board.at(i2).size(); ++j2)
					board.at(i2).at(j2) = board.at(i2 - 1).at(j2);
			rows_cleared++;
		}
	}
	return rows_cleared * rows_cleared * 10;
}

bool Board::get_has_active_piece() const {
	return has_active_piece;
}

bool Board::game_over() const {
	for (const bool square: board.at(max_fill_line))
		if (square == true)
			return true;
	return false;
}
