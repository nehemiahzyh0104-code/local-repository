p = 0.30 * 0.02 + 0.45 * 0.03 + 0.25 * 0.05
q = 1 - p

n = 0
prob = 0.0
while prob < 0.95:
    n += 1
    prob = 1 - q ** n

print(f"P(D) = {p}")
print(f"P(both defective) = {p ** 2}")
print(f"P(at least one in 3) = {1 - q ** 3}")
print(f"smallest n = {n}, P(at least one) = {prob}")
