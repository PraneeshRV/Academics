def solve():
    n = int(input())
    p = list(map(int, input().split()))
    current = p[:]
    for k in range(n, 0, -1):
        found = False

        for start in range(n - k + 1):
            can_subtract = True
            for i in range(start, start + k):
                if current[i] < 1:
                    can_subtract = False
                    break


            if can_subtract:
                # Subtract 1 from this subarray
                for i in range(start, start + k):
                    current[i] -= 1
                found = True
                break

        if not found:
            return "NO"
        
    return "YES" if all(x == 0 for x in current) else "NO"

t = int(input())
for _ in range(t):
    print(solve())
        