import sys
sys.setrecursionlimit(2000)
def solve():

    def find_initial_value(steps_left, x_rn):

        if steps_left == 0:
            return x_rn

        res_from_even = find_initial_value(steps_left - 1, x_rn * 2)
        if res_from_even is not None:
            return res_from_even

        if (x_rn - 1) % 3 == 0:
            prev_from_odd = (x_rn - 1) // 3

            if prev_from_odd % 2 != 0:
                res_from_odd = find_initial_value(steps_left - 1, prev_from_odd)
                if res_from_odd is not None:
                    return res_from_odd
        
        return None

    k, x = map(int, sys.stdin.readline().split())

    print(find_initial_value(k, x))

def main():

    try:
        num_test_cases = int(sys.stdin.readline())
        for _ in range(num_test_cases):
            solve()
    except (IOError, ValueError):
        pass

if __name__ == "__main__":
    main()