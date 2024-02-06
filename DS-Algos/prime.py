from math import sqrt


def sieve(n):
    sieve_arr = [1] * (n + 1)  # Initialize with all elements as 1
    sieve_arr[0] = sieve_arr[1] = 0  # Mark 0 and 1 as non-prime

    for i in range(2, int(n**0.5) + 1):  # Optimized loop for efficiency
        if sieve_arr[i]:
            for j in range(i * i, n + 1, i):
                sieve_arr[j] = 0

    primes = [i for i in range(2, n + 1) if sieve_arr[i]]  # Collect primes
    return primes


def segmented_sieve(low, high, primes):
    low = max(low, 2)  # Handle cases of 0 and 1
    is_prime = [1] * (high - low + 1)
    if low > high:
        return []
    for p in primes:
        s = (low // p) * p
        if s < low:
            s += p
        if s == p:
            s += p

        for i in range(s, high + 1, p):
            is_prime[i - low] = 0

    ans = [i + low for i, prime in enumerate(is_prime) if prime]
    return ans


def extended_gcd(A, B):
    if B == 0:
        return (1, 0, A)
    xd, yd, gcd = extended_gcd(B, A % B)
    x = yd
    y = xd - (A // B) * yd
    return (x, y, gcd)


def modulo_inv(A, mod):
    ans = extended_gcd(A, mod)
    x = ans[0]
    return (x + mod) % mod


def diophantine(A, B, C):
    x, y, gcd = extended_gcd(A, B)
    if C % gcd != 0:
        return (-1, -1)
    return (x * C // gcd, y * C // gcd)


if __name__ == "__main__":
    # low, high = [int(i) for i in input().split()]
    # primes = sieve(int(sqrt(high) + 1))
    # N = 1e5 + 1
    # primes = sieve(N)
    # ans = segmented_sieve(low, high, primes)
    # print(*ans)
    print(modulo_inv(9, 10**9 + 5), (7 * modulo_inv(9, 10**9 + 5)) % (10**9 + 7))
