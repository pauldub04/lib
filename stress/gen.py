from random import randint

n = randint(1, 10)
print(n)

for i in range(n):
    x = randint(0, n-1)
    print(x, end=' ')
