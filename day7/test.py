from typing import List, Callable

# Function to convert a string to an integer
def conv(s: str) -> int:
    return int(s)

# Function to split a string into a list of integers using a custom converter
def split(s: str, converter: Callable[[str], int]) -> List[int]:
    return list(map(converter, s.split()))

# Recursive solve function
def solve(aa: List[int], i: int, curr: int, target: int, hard: bool) -> int:
    if curr == target:
        return target
    if i == len(aa) or curr > target:
        return 0
    # Try multiplying
    if solve(aa, i + 1, curr * aa[i], target, hard) > 0:
        return target
    # Try adding
    if solve(aa, i + 1, curr + aa[i], target, hard) > 0:
        return target
    # Try the custom "concatenation" operator if allowed
    if hard:
        s_curr = str(curr) + str(aa[i])
        if len(s_curr) > len(str(target)):
            return 0
        if solve(aa, i + 1, int(s_curr), target, hard) > 0:
            return target
    return 0

def main():
    # Read input
    s = []
    try:
        while True:
            line = input().strip()
            if line:
                s.append(line)
    except EOFError:
        pass

    n = len(s)
    res = [0] * n
    a = [[] for _ in range(n)]

    # Parse input
    for i in range(n):
        t = split(s[i], conv)
        res[i] = t[0]
        t.pop(0)  # Remove the first element
        a[i] = t

    # Solve for both parts
    ans1, ans2 = 0, 0
    for i in range(n):
        ans1 += solve(a[i], 1, a[i][0], res[i], False)
        ans2 += solve(a[i], 1, a[i][0], res[i], True)

    # Output results
    print(f"PART 1: {ans1}")
    print(f"PART 2: {ans2}")

if __name__ == "__main__":
    main()