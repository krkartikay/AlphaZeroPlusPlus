#include "game.h"

#include <iostream>

GameState::GameState() {}

void GameState::printBoard() const {
  libchess::Position p("startpos");
  auto moves = p.legal_moves();
  std::cout << p << std::endl;
  for (auto m : moves) {
    std::cout << m << std::endl;
  }
}