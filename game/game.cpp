#include "game.h"

#include <iostream>

// const std::string kStartFen = "startpos";
const std::string kStartFen = "8/8/8/8/K7/7Q/8/k7 w - - 1 1";

GameState::GameState()
    : position_(kStartFen) {
}  // Initializes with a default position (initial board position)

GameState::GameState(const GameState& other) : position_(other.position_) {}

Player GameState::player() const { return Player::NONE; }

Player GameState::winner() const { return Player::NONE; }

bool GameState::terminated() const { return true; }

std::vector<int> GameState::legal_actions() const {
  std::vector<int> actions = {};
  return actions;
}

GameState GameState::next_state(int action) const {
  GameState new_state(*this);
  return new_state;
}

void GameState::to_image() const {}  // TODO: to be implemented later

void GameState::print_board() const { std::cout << position_ << std::endl; }
