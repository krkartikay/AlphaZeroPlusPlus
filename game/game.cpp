#include "game.h"

#include <iostream>

// const std::string kStartFen = "startpos";
const std::string kStartFen = "8/8/8/8/K7/7Q/8/k7 w - - 1 1";

GameState::GameState()
    : position_(kStartFen) {
}  // Initializes with a default position (initial board position)

GameState::GameState(const GameState& other) : position_(other.position_) {}

Player GameState::player() const {
  return position_.turn() == libchess::Side::White ? Player::WHITE
                                                   : Player::BLACK;
}

Player GameState::winner() const {
  if (!position_.is_terminal()) return Player::NONE;

  if (position_.is_checkmate()) {
    // If the current player is in checkmate, then the opposite player wins.
    return position_.turn() == libchess::Side::White ? Player::BLACK
                                                     : Player::WHITE;
  }
  return Player::NONE;  // Draw or stalemate cases
}

bool GameState::terminated() const { return position_.is_terminal(); }

std::vector<int> GameState::legal_actions() const {
  std::vector<int> actions = {};
  std::vector<libchess::Move> legal_moves = position_.legal_moves();
  for (const auto& move : legal_moves) {
    int from = static_cast<int>(move.from());
    int to = static_cast<int>(move.to());
    int index = from * 64 + to;
    actions.push_back(index);
  }
  return actions;
}

GameState GameState::next_state(int action) const {
  GameState new_state(*this);
  int from = action / 64;
  int to = action % 64;

  for (const auto& move : position_.legal_moves()) {
    if (static_cast<int>(move.from()) == from &&
        static_cast<int>(move.to()) == to) {
      new_state.position_.makemove(move);
      break;
    }
  }

  return new_state;
}

void GameState::to_image() const {}  // TODO: to be implemented later

void GameState::print_board() const { std::cout << position_ << std::endl; }
