#!/usr/bin/python

#https://projecteuler.net/problem=3

# rules
# all the natural numbers except 0 and 1 (positives)
# divided by 1 and it self only
# even numbers (except the number 2) are not prime
# all numbers (except the number 5) divided by 5 are not prime

def find_next_prime(primes,m):
    s = primes[-1]+2
    
    for x in range(s,m):
        prime = True
        if (x % 2 != 0): #not even
            for item in primes:
                if (x % item == 0):
                    prime = False
                    break
            if (prime == True):
                return x
    return 0

def find_next_factor(r,item):
    if (r < item):
        return False

    if (r % item == 0):
        return True

    return False

def largest_prime_factor():
    r = 600851475143
    done = False
    primes = [2,3,5,7,11,13,17,19]
    factors = []
    res = 1

    for item in reversed(primes):
        if (find_next_factor(r,item) == True):
            factors.insert(0,item)
            res = res * item
            if (res == r):
                break;

    while (True):
        if (r < primes[-1]):
            break
        nprime = find_next_prime(primes,r)
        if (nprime != 0):
            primes.append(nprime)
            if (find_next_factor(r,nprime) == True):
                factors.append(nprime)
                res = res * nprime
                if (res == r):
                    break

    #print("---- Primes ----")
    #for item in primes:
    #    print("%d" % (item))

    #print("---- Factors ----")
    #for item in factors:
    #    print("%d" % (item))

    print("---- Largest prime factor of %d is %d" % (r, factors[-1]))
largest_prime_factor()
