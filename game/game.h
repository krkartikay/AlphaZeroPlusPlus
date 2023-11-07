#pragma once

#include <array>
#include <optional>
#include <vector>

#include "chess.hpp"

constexpr int kNumActions = 64 * 64;

enum class Player { NONE = 0, WHITE = 1, BLACK = -1 };

class GameState {
 public:
  GameState();
  GameState(const GameState& other);

  Player player() const;
  Player winner() const;

  bool terminated() const;
  std::vector<int> legal_actions() const;

  GameState next_state(int action) const;

  void to_image() const;  // TODO implement this one later

  void print_board() const;

 private:
  chess::Board position_;
};