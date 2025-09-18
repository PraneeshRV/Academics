import sys

num_test_cases = int(sys.stdin.readline())

for _ in range(num_test_cases):
    n = int(sys.stdin.readline())
    p = list(map(int, sys.stdin.readline().split()))

    q = [n + 1 - val for val in p]

    print(*q)