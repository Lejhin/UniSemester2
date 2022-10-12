#include "Board.h"

const int WIDTH {600};

Board::Board(int n) {
    this->n = n;
    this->square_size = WIDTH * 2 / (3 * n);
    this->board = new sf::Color[n * n]{sf::Color::Black};
    // make sure the pixels fit
    this->pixels = new Pixels{WIDTH}; // scaling does not work? scale here
    this->reset();
}

Board::~Board() {
    delete[] this->board;
    delete this->pixels;
}

void Board::setSize(int n) {
    delete[] this->board; // keep the pixels
    this->n = n;
    this->square_size = WIDTH * 2 / (3 * n);
    // forget old settings
    this->board = new sf::Color[n * n]{sf::Color::Black};
    this->reset();
}

void Board::setSquare(int row, int column, sf::Color color) {
    if (row < 0 || row >= n || column < 0 || column >= n) {
        throw std::runtime_error("row/column not with [0..n[");
    }
    board[(n - row - 1) * n + column] = color;
}

void Board::resetSquare(int row, int column) {
    if (row < 0 || row >= n || column < 0 || column >= n) {
        throw std::runtime_error("row/column not with [0..n[");
    }
    board[(n - row - 1) * n + column] =
        (row + column) % 2 == 0 ? sf::Color::Black : sf::Color::White;
}

void Board::reset() {
    for (int row = 0; row < n; row += 1) {
        for (int column = 0; column < n; column += 1) {
            resetSquare(row, column);
        }
    }
}

void Board::log(const std::string& text) {
    if (logid == -1) {
        logid = pixels->add_text(0, 0, text);
    }
    pixels->change_text(logid, text);
}

void Board::render() {
    for (int row = 0; row < n; row += 1) {
        for (int col = 0; col < n; col += 1) {
            for (int i = 0; i < square_size; i += 1) {
                for (int j = 0; j < square_size; j += 1) {
                    pixels->set(col * square_size + j, row * square_size + i,
                                this->board[row * n + col]);
                }
            }
        }
    }
}
