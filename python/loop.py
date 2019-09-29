#!/bin/python

tup = (1, 2, 3)

for item in tup:
    print(item)

# every single item of this list is a tupple pair
myList = [(1, 2), (3, 4), (5, 6), (7, 8)]
len(myList)

for item in myList:
    print(item)

# toople unpaking. It can be used when passing params to a method/function
for (a, b) in myList:
    print(a)
    print(b)

dic = {'k1':1, 'k2': 2, 'k3': 3}

for item in dic:
    print(item) # It will interate over the keys only

for item in dic.items():
    print(item) # It will return tuples

# because it returns a tuple we can use tuple unpacking \o/
for key,item in dic.items():
    print(key)
    print(item)

# if you want the values of a dic only
for item in dic.values():
    print(item)
