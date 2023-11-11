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

bool GameState::isCastlingMove(chess::Square source,
                               chess::Square destination) const {
  chess::Piece sourcePiece = position_.at(source);
  chess::Piece destinationPiece = position_.at(destination);
  return chess::utils::typeOfPiece(sourcePiece) == chess::PieceType::KING &&
         chess::utils::typeOfPiece(destinationPiece) ==
             chess::PieceType::ROOK &&
         position_.color(sourcePiece) == position_.color(destinationPiece);
}

chess::Move GameState::createMove(int source, int destination,
                                  int action) const {
  int promotionPiece = action % 5;
  chess::Square sourceSquare = static_cast<chess::Square>(source);
  chess::Square destinationSquare = static_cast<chess::Square>(destination);
  if (promotionPiece != 0) {
    return chess::Move::make<chess::Move::PROMOTION>(
        sourceSquare, destinationSquare,
        static_cast<chess::PieceType>(promotionPiece));
  } else if (isCastlingMove(sourceSquare, destinationSquare)) {
    return chess::Move::make<chess::Move::CASTLING>(sourceSquare,
                                                    destinationSquare);
  }
  return chess::Move::make<chess::Move::NORMAL>(sourceSquare,
                                                destinationSquare);
}

GameState GameState::next_state(int action) const {
  GameState new_state(*this);
  int sourceSquare = action / (64 * 5);
  int destinationSquare = (action / 5) % 64;
  chess::Move move = createMove(sourceSquare, destinationSquare, action);
  new_state.position_.makeMove(move);
  return new_state;
}

void GameState::to_image() const {}  // TODO: to be implemented later

void GameState::print_board() const { std::cout << position_ << std::endl; }

Player other_player(Player p) {
  if (p == Player::NONE) return Player::NONE;
  return p == Player::WHITE ? Player::BLACK : Player::WHITE;
}
