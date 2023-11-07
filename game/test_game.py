import game
import random
import time

# kKQFen = "8/8/8/8/K7/7Q/8/k7 w - - 1 1"
# kCheckMateFen = "rnbqkbnr/ppppp2p/5p2/6pQ/4PP2/8/PPPP2PP/RNB1KBNR b KQkq - 1 3"

while True:
    g = game.GameState()
    n_moves = 0

    while not g.terminated():
        legal_actions = g.legal_actions()
        print(f"{n_moves=}, {legal_actions=}")
        action = random.choice(legal_actions)
        print(f"Performing Action: {action=}")
        g = g.next_state(action)
        g.print_board()
        n_moves += 1

    print(g.winner())
    time.sleep(1)
