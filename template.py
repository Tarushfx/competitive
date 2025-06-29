import sys

# sys.stdin = open('input.txt', 'r')
# sys.stdout = open('output.txt', 'w')
sys.setrecursionlimit(10**6)

MOD = 10**9 + 7


def inplist():
    return [int(i) for i in input().split()]


def pow(a, b, mod):
    x = 1
    while b:
        if b & 1:
            x = (x * a) % mod
        a = (a * a) % mod
        b >>= 1
    return x


def debug(**kwargs):
    st = [f"{name}: {val}" for (name, val) in kwargs.items()]
    print(*st, sep=" | ")


def solve():
    n = 5
    debug(n=n, p=12)
    pass


def main():
    t = 1
    # t=int(input())
    for _ in range(t):
        solve()


if __name__ == "__main__":
    main()
