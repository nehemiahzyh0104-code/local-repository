from itertools import combinations
import numpy as np

prob = np.array([0.05, 0.15, 0.20, 0.25, 0.35])
n = 1

def solve(x, y):
    result = 0.0
    for size in range(len(y) + 1):
        for subset in combinations(range(len(y)), size):
            result += (-1) ** size * (1 - sum(y[i] for i in subset)) ** x
    return result

while True:
    if solve(n, prob) >= 0.90:
        print(f"The smallest integer n such that Q_n >= 0.90 is {n}, with Q_n = {solve(n, prob):.12f}")
        break

    else:
        print(f"Q_{n} is {solve(n, prob):.12f}")
        n += 1
        continue
