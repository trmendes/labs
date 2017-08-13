#!/usr/bin/python

#https://projecteuler.net/problem=2

def even_fibonacci_numbers():
    m = 4000000
    f = 1
    s = 2
    n = 0
    r = 0
    while (n < m):
        n = next(f,s)
        print("%d\t%d\t=\t%d" % (f,s,n))
        f = s
        s = n
        if (f % 2 == 0):
            r = r + f
    print("The sum of the even numbers is: %d" % (r))

def next(_p, _n):
    return _p+_n

even_fibonacci_numbers()