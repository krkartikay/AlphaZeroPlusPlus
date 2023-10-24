#pragma once

#include <array>
#include <optional>
#include <vector>

enum class Player { NONE = 0, WHITE = 1, BLACK = -1 };

class GameState {
 public:
  GameState();
  GameState(const GameState& other);

  void printBoard() const;

 private:
};