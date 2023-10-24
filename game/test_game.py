import game
import random

g = game.GameState()

n_moves = 0
while not g.terminated():
    action = random.choice(g.legal_actions())
    g = g.next_state(action)
    g.print_board()
    n_moves += 1
    print(n_moves)

print(g.winner())