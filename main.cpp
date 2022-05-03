#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>

template<std::size_t size>
void printBoard(std::ostream& os, const std::array<int, size>& board, std::size_t rows, std::size_t cols)
{
	constexpr std::size_t tileWidth = 3;

	for (std::size_t i = 0; i < rows; ++i)
	{
		for (std::size_t j = 0; j < cols; ++j)
		{
			os << std::setw(tileWidth) << std::left;

			if (board[cols * i + j] == 0) {
				os << ' ';
			}
			else
			{
				os << board[cols * i + j];
			}

			os << ' ';
		}
		os << '\n';
	}
}


int main()
{
	constexpr std::size_t ROWS = 4;
	constexpr std::size_t COLS = 4;
	std::array<int, ROWS * COLS> board;

	std::iota(board.begin(), board.end(), 0);
	std::shuffle(board.begin(), board.end(), std::random_device{});

	auto it = std::find(board.begin(), board.end(), 0);
	std::size_t emptyPosition = std::distance(board.begin(), it);
	bool win = false;
	std::size_t step = 1;

	while (true)
	{
		win = true;
		for (std::size_t i = 0; i < board.size() - 1; ++i) 
		{
			if (board[i] != i + 1)
			{
				win = false;
			}
		}

		if (win)
		{
			std::system("cls");
			printBoard(std::cout, board, ROWS, COLS);
			std::cout << "\nYou win!\n";
			break;
		}

		std::system("cls");
		printBoard(std::cout, board, ROWS, COLS);

		std::size_t move = 0;
		std::cout << "\nYour move: ";
		std::cin >> move;

		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore();
			continue;
		}

		if (move == -1)
		{
			break;
		}

		const int emptyRow = static_cast<int>(emptyPosition / ROWS);
		const int emptyCol = emptyPosition % COLS;

		int posToCheck = COLS * (emptyRow + 1) + emptyCol;
		if (posToCheck < board.size() && board[posToCheck] == move)
		{
			std::swap(board[posToCheck], board[emptyPosition]);
			emptyPosition = posToCheck;
			continue;
		}

		posToCheck = COLS * (emptyRow - 1) + emptyCol;
		if (posToCheck >= 0 && board[posToCheck] == move)
		{
			std::swap(board[posToCheck], board[emptyPosition]);
			emptyPosition = posToCheck;
			continue;
		}

		posToCheck = COLS * emptyRow + (emptyCol + 1);
		if (posToCheck < board.size() && board[posToCheck] == move)
		{
			std::swap(board[posToCheck], board[emptyPosition]);
			emptyPosition = posToCheck;
			continue;
		}

		posToCheck = COLS * emptyRow + (emptyCol - 1);
		if (posToCheck >= 0 && board[posToCheck] == move)
		{
			std::swap(board[posToCheck], board[emptyPosition]);
			emptyPosition = posToCheck;
			continue;
		}
	}

	return 0;
}