"""
Some properties of bitwise operations:
    a|b = a⊕b + a&b
    (a&b)⊕(a|b) = a⊕b
Addition:
    a+b = a|b + a&b             
    a+b = a⊕b + 2(a&b)
Subtraction:
    a-b = (a⊕(a&b))-(b⊕(a&b))
    a-b = ((a|b)⊕b)-((a|b)⊕a)
"""
from math import log2


def setbit(v, n):
    return v | (1 << n)


def getbit(v, n):
    return v & (1 << n)


def clearbit(v, n):
    return v & comp(1 << n)


def mask(n):
    return (1 << n) - 1


def comp(n):
    return ~n


def count(n):
    k = 0
    while n:
        k += 1
        n = clearlsb(n)


def countzero():
    pass


def clearlsb(n):
    return n & (n - 1)


def clearmsb(n):
    return n ^ getmsb(n)


def getlsb(n):
    return n & -n


def getmsb(n):
    return 1 << int(log2(n))
