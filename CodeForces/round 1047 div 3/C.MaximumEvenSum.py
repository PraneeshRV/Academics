import sys

num_test_cases = int(sys.stdin.readline())

for _ in range(num_test_cases):
    a, b = map(int, sys.stdin.readline().split())

    if a % 2 != 0 and b % 2 != 0:
        print(max(a + b, a * b + 1))
    elif a % 2 == 0 and b % 2 != 0:
        print(-1)
    elif a % 2 == 0 and b % 2 == 0:
        print(max(a + b, a * (b // 2) + 2))
    else:
        if b % 4 != 0:
            print(-1)
        else:
            print(max(2 * a + b // 2, a * (b // 2) + 2))