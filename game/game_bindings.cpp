#include <pybind11/pybind11.h>
#include <pybind11/stl.h>  // For automatic conversion of STL types

#include "game.h"

namespace py = pybind11;

PYBIND11_MODULE(game, m) {
  m.doc() = "Python module for GameState";

  py::enum_<Player>(m, "Player")
      .value("NONE", Player::NONE)
      .value("WHITE", Player::WHITE)
      .value("BLACK", Player::BLACK)
      .export_values();

  py::class_<GameState>(m, "GameState")
      .def(py::init<>())
      .def(py::init<const GameState &>())
      .def("player", &GameState::player)
      .def("winner", &GameState::winner)
      .def("terminated", &GameState::terminated)
      .def("legal_actions", &GameState::legal_actions)
      .def("next_state", &GameState::next_state)
      .def("print_board", &GameState::print_board);
}
