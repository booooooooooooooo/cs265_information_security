'''
e = 3

n1 = 5356488760553659
n2 = 8021928613673473
n3 = 56086910298885139

c1 = 4324345136725864
c2 = 2102800715763550
c3 = 46223668621385973
'''

def extendEuclid(a, b):
    if b == 0:
        return [1, 0, a]
    else:
        [x, y, gcd] = extendEuclid(b, a%b)
        return [y, x - (a/b) * y, gcd]

def mul_inverse(a, N):
    [x, y, gcd] = extendEuclid(a, N)
    return x % N

def chinese_remainder(n, c):
    sum = 0
    N = n[0] * n[1] * n[2]
    for i in range(len(n)):
        a = N / n[i]
        mulInv = mul_inverse(a, n[i])
        # sum += ((c[i] * mulInv * a) % N + N) % N
        sum += c[i] * mulInv * a
    return sum % N
def nthRoot(x, n):
    low = 0
    high = 1
    while high**3 < x:
        low = high
        high = high * 2
    while low < high:
        mid = low + (high - low) / 2
        if mid**3 < x:
            low = mid + 1
        else:
            high = mid
    if low ** n == x:
        return low
    else:
        return "No answer"

n = [5356488760553659, 8021928613673473, 56086910298885139]
c = [4324345136725864, 2102800715763550, 46223668621385973]
#233207856253273728845841162057496863547659
cube = chinese_remainder(n, c)
# 61552787537619
message = nthRoot(cube, 3)
print "Message value is: %d"%message
