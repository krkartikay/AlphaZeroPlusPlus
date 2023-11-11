#pragma once

#include <array>
#include <optional>
#include <vector>

#include "chess.hpp"

constexpr int kNumActions = 64 * 64;

enum class Player {
  NONE = 0,
  WHITE = 1,
  BLACK = -1,
};

Player other_player(Player p);

class GameState {
 public:
  GameState();
  GameState(const GameState& other);

  GameState(const std::string& start_fen);

  Player player() const;
  Player winner() const;

  bool terminated() const;
  std::vector<int> legal_actions() const;

  GameState next_state(int action) const;

  void to_image() const;  // TODO implement this one later

  void print_board() const;

 private:
  chess::Board position_;

  bool isCastlingMove(chess::Square source, chess::Square destination) const;

  chess::Move createMove(int source, int destination, int action) const;
};
