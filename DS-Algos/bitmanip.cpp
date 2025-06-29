#include <bits/stdc++.h>
using namespace std;
int main()
{
    return 0;
}
int setbit(int v, int n)
{
    return v | (1 << n);
}
int getbit(int v, int n)
{
    return v & (1 << n);
}

int clearbit(int v, int n)
{
    return v & comp(1 << n);
}

int mask(int n)
{
    return (1 << n) - 1;
}

int comp(int n)
{
    return ~n;
}

int count(int n)
{
    int k = 0;
    while (n)
    {
        k += 1;
        n = clearlsb(n);
    };
}
int countzero() {}
int clearlsb(int n)
{
    return n & (n - 1);
}
int clearmsb(int n)
{
    return n ^ getmsb(n);
}
int getlsb(int n)
{
    return n & -n;
}
int getmsb(int n)
{
    return 1 << int(log2(n));
}