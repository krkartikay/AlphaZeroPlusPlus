#include "game.h"

#include <iostream>

const std::string kStartFen =
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

GameState::GameState()
    : position_(kStartFen) {
}  // Initializes with a default position (initial board position)

GameState::GameState(const GameState& other) : position_(other.position_) {}

GameState::GameState(const std::string& start_fen) : position_(start_fen) {}

Player GameState::player() const {
  return position_.sideToMove() == chess::Color::WHITE ? Player::WHITE
                                                       : Player::BLACK;
}

Player GameState::winner() const {
  auto gameResult = position_.isGameOver();
  if (gameResult.first == chess::GameResultReason::CHECKMATE) {
    return gameResult.second == chess::GameResult::WIN ? player()
                                                       : other_player(player());
  }
  return Player::NONE;
}

bool GameState::terminated() const {
  return position_.isGameOver().first != chess::GameResultReason::NONE;
}

std::vector<int> GameState::legal_actions() const {
  chess::Movelist moves;
  chess::movegen::legalmoves(moves, position_);

  std::vector<int> actions;
  for (const auto& move : moves) {
    int source = static_cast<int>(move.from());
    int destination = static_cast<int>(move.to());
    if (move.typeOf() == chess::Move::PROMOTION) {
      int promotionPiece = static_cast<int>(move.promotionType());
      actions.push_back(source * 64 * 5 + destination * 5 + promotionPiece);
    } else {
      actions.push_back(source * 64 * 5 + destination * 5);
    }
  }

  return actions;
}

GameState GameState::next_state(int action) const {
  GameState new_state(*this);
  int source = action / (64 * 5);
  int destination = (action / 5) % 64;
  int promotionPiece = action % 5;
  if (promotionPiece != 0) {
    chess::Move move = chess::Move::make<chess::Move::PROMOTION>(
        static_cast<chess::Square>(source),
        static_cast<chess::Square>(destination),
        static_cast<chess::PieceType>(promotionPiece));
    new_state.position_.makeMove(move);
  } else {
    chess::Move move = chess::Move::make<chess::Move::NORMAL>(
        static_cast<chess::Square>(source),
        static_cast<chess::Square>(destination));
    new_state.position_.makeMove(move);
  }
  return new_state;
}

void GameState::to_image() const {}  // TODO: to be implemented later

void GameState::print_board() const { std::cout << position_ << std::endl; }

Player other_player(Player p) {
  if (p == Player::NONE) return Player::NONE;
  return p == Player::WHITE ? Player::BLACK : Player::WHITE;
}
