import numpy as np
import matplotlib.pyplot as plt
import math

def sieve(x):
    return 1.9223 * np.power(x, 1.0/3) * np.power(np.log2(x), 2.0/3)

print sieve(390)
print sieve(1024)
print sieve(2048)



x = 1
while 1:
    y = sieve(x)
    if y < 256:
        x = x * 2
    else:
        break
low = x / 2
high = x
while low < high:
    mid = low + (high - low) / 2
    if sieve(mid) < 256:
        low = mid + 1
    else:
        high = mid

print low
