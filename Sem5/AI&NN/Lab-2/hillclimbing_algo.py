import random

def evaluate(x):
    return -1 * (x ** 2) + 12  

def simple_hill_climb(initial_guess):
    current = initial_guess
    delta = 0.2          
    max_steps = 100     

    for _ in range(max_steps):
        neighbors = [current + delta, current - delta]

        best_neighbor = max(neighbors, key=evaluate)

        if evaluate(best_neighbor) > evaluate(current):
            current = best_neighbor
        else:
            break  
    return current, evaluate(current)


initial_value = random.uniform(-8, 8)

optimum = simple_hill_climb(initial_value)

print(f"Initial Guess: {initial_value:.2f}")
print(f"Local Optimum at x = {optimum[0]:.2f}, f(x) = {optimum[1]:.2f}")
