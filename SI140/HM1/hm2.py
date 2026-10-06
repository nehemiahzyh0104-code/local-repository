"""SI 140A Homework 1, Problem 5(c)."""

from itertools import combinations
from pathlib import Path

import matplotlib.pyplot as plt


unequal_prob = (0.05, 0.15, 0.20, 0.25, 0.35)
uniform_prob = (0.20,) * 5
target = 0.90


def solve(n, probabilities):
    """Calculate Q_n using the inclusion-exclusion formula from part (a)."""
    result = 0.0
    for size in range(len(probabilities) + 1):
        for subset in combinations(range(len(probabilities)), size):
            missing_mass = sum(probabilities[i] for i in subset)
            result += (-1) ** size * (1 - missing_mass) ** n
    return result


def first_n(probabilities):
    n = 1
    while solve(n, probabilities) < target:
        n += 1
    return n


n_uniform = first_n(uniform_prob)
n_unequal = first_n(unequal_prob)

print(f"Uniform: Q_{n_uniform - 1} = {solve(n_uniform - 1, uniform_prob):.12f}")
print(f"Uniform: Q_{n_uniform} = {solve(n_uniform, uniform_prob):.12f}")
print(f"Smallest n in the uniform case: {n_uniform}")
print(f"Unequal: Q_{n_unequal - 1} = {solve(n_unequal - 1, unequal_prob):.12f}")
print(f"Unequal: Q_{n_unequal} = {solve(n_unequal, unequal_prob):.12f}")
print(f"At n = {n_uniform}: uniform Q_n = {solve(n_uniform, uniform_prob):.6f}, "
      f"unequal Q_n = {solve(n_uniform, unequal_prob):.6f}")

draw_counts = range(1, 61)
uniform_values = [solve(n, uniform_prob) for n in draw_counts]
unequal_values = [solve(n, unequal_prob) for n in draw_counts]

plt.figure(figsize=(8, 5))
plt.plot(draw_counts, uniform_values,
         label=r"Uniform: each $p_i = 0.20$", linewidth=2)
plt.plot(draw_counts, unequal_values,
         label="Unequal: p = (0.05, 0.15, 0.20, 0.25, 0.35)", linewidth=2)
plt.axhline(target, color="gray", linestyle="--", linewidth=1,
            label=r"Target $Q_n = 0.90$")
plt.scatter([n_uniform, n_unequal],
            [solve(n_uniform, uniform_prob), solve(n_unequal, unequal_prob)],
            color="black", zorder=3)
plt.annotate(f"n = {n_uniform}, Q = {solve(n_uniform, uniform_prob):.3f}",
             (n_uniform, solve(n_uniform, uniform_prob)),
             xytext=(7, -20), textcoords="offset points")
plt.annotate(f"n = {n_unequal}, Q = {solve(n_unequal, unequal_prob):.3f}",
             (n_unequal, solve(n_unequal, unequal_prob)),
             xytext=(7, -20), textcoords="offset points")
plt.xlabel("Number of draws n")
plt.ylabel(r"Probability of collecting all five types, $Q_n$")
plt.title("Collecting all five card types")
plt.xlim(1, 60)
plt.ylim(0, 1.02)
plt.grid(alpha=0.25)
plt.legend(loc="lower right")
plt.tight_layout()

output_path = Path(__file__).with_name("hm2_plot.png")
plt.savefig(output_path, dpi=200)
print(f"Plot saved to: {output_path}")
