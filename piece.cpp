#include "piece.hpp"
#include <vector>
#include <random>
#include <cmath>

const std::vector<std::vector<std::vector<bool>>> Piece::valid_piece_conigurations {
	{
		{
			{false, false, false, false},
			{false, false, false, false},
			{true, true, true, true},
			{false, false, false, false}
		},
		{
			{true, true},
			{true, true}
		},
		{
			{false, true, false},
			{true, true, true},
			{false, false, false}
		},
		{
			{false, false, false},
			{false, true, true},
			{true, true, false}
		},
		{
			{false, false, false},
			{true, true, false},
			{false, true, true}
		},
		{
			{false, false, false},
			{false, false, true},
			{true, true, true}
		},
		{
			{false, false, false},
			{true, false, false},
			{true, true, true}
		}
	}
};

Piece::Piece()
	: configuration{}, i_position{0}, j_position{0} {}

void Piece::new_piece_setup(int board_length_j) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<int> dist(0, valid_piece_conigurations.size() - 1);
	configuration = valid_piece_conigurations.at(dist(gen));
	i_position = 0;
	j_position = static_cast<int>(floor(board_length_j / 2.0) - ceil(configuration.size() / 2.0));
}

void Piece::move_left() {
	j_position--;
}

void Piece::move_right() {
	j_position++;
}

void Piece::move_down() {
	i_position++;
}

void Piece::rotate_clockwise() {
	const std::vector<std::vector<bool>> previous_configuration = configuration;
	for (int i{0}; i < configuration.size(); ++i)
		for (int j{0}; j < configuration.at(i).size(); ++j)
			configuration.at(j).at(configuration.size() - 1 - i) = previous_configuration.at(i).at(j);
}

void Piece::rotate_counterclockwise() {
	const std::vector<std::vector<bool>> previous_configuration = configuration;
	for (int i{0}; i < configuration.size(); ++i)
		for (int j{0}; j < configuration.at(i).size(); ++j)
			configuration.at(configuration.size() - 1 - j).at(i) = previous_configuration.at(i).at(j);
}

bool Piece::valid_position(const std::vector<std::vector<bool>>& board) const {
	for (int i{0}; i < configuration.size(); ++i)
		for (int j{0}; j < configuration.at(i).size(); ++j)
			if (configuration.at(i).at(j) == true) {
				if (i_position + i < 0 || i_position + i >= board.size())
					return false;
				if (j_position + j < 0 || j_position + j >= board.at(i).size())
					return false;
				if (board.at(i_position + i).at(j_position + j) == true)
					return false;
			}
	return true;
}

void Piece::imprint(std::vector<std::vector<bool>>& board) const {
	for (int i{0}; i < configuration.size(); ++i)
		for (int j{0}; j < configuration.size(); ++j)
			if (configuration.at(i).at(j) == true)
				board.at(i_position + i).at(j_position + j) = true;
}
