#include <bits/stdc++.h>
#define vi vector<int>
#define tii tuple<int, int, int>
#define pii pair<int, int>
#define int long long int
using namespace std;
int n = 1e5 + 1;
vi sieve(int n);
vi segmentedSieve(int low, int high, vi &primes);
tii extended_gcd(int A, int B);
int modulo_inv(int A, int mod);
pii diophantine(int A, int B, int C);
vi primes = sieve(n);
int32_t main()
{
    int t = 1;
    // cin >> t;
    while (t--)
    {
        int low, high;
        cin >> low >> high;
        // vi ans = segmentedSieve(low, high, primes);
        tii ans = extended_gcd(low, high);
        cout << get<0>(ans) << " " << get<1>(ans) << " " << get<2>(ans) << endl;
        cout << "Modulo inverse of " << low << " is " << modulo_inv(low, 22) << endl;
        cout << "Modulo inverse of " << high << " is " << modulo_inv(high, 22) << endl;
        auto p = diophantine(low, high, 40);
        cout << "Solution " << p.first << " " << p.second << endl;
    }
    cout << endl;
    return 0;
}

vi sieve(int n)
{
    vi sieve_arr = vi(n + 1, 1);
    sieve_arr[0] = sieve_arr[1] = 0;
    for (int i = 2; i <= n; i++)
    {
        if (!sieve_arr[i])
        {
            for (int p = i * i; p <= n; p += i)
            {
                sieve_arr[p] = 1;
            }
        }
    }
    // return sieve_arr;
    vi primes;
    for (int i = 2; i <= n; i++)
    {
        if (sieve_arr[i])
            primes.push_back(i);
    }
    return primes;
}

vi segmentedSieve(int low, int high, vi &primes)
{
    // handling case of 0 and 1
    low = max(low, (int)2);
    if (low > high)
    {
        return {};
    }
    vi isPrime(high - low + 1, 1);
    vi ans;
    for (int p : primes)
    {
        int s = (low / p) * p;
        if (s < low)
            s += p;
        if (s == p)
            s += p;

        for (int i = s; i <= high; i += p)
        {
            isPrime[i - low] = 0;
        }
    }

    for (int i = 0; i < isPrime.size(); i++)
    {
        if (isPrime[i])
        {
            ans.push_back(i + low);
        }
    }
    return ans;
}

tii extended_gcd(int A, int B)
{
    if (B == 0)
        return {1, 0, A};
    auto [xd, yd, gcd] = extended_gcd(B, A % B);
    int x = yd;
    int y = xd - A / B * yd;
    return {x, y, gcd};
}

int modulo_inv(int A, int mod)
{
    tii ans = extended_gcd(A, mod);
    int x = get<0>(ans);
    return (x + mod) % mod;
}

pii diophantine(int A, int B, int C)
{
    auto [x, y, gcd] = extended_gcd(A, B);
    if (C % gcd != 0)
        return make_pair(-1, -1);
    return make_pair(x * C / gcd, y * C / gcd);
}