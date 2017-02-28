'''
e = 3

n1 = 5356488760553659
n2 = 8021928613673473
n3 = 56086910298885139

c1 = 4324345136725864
c2 = 2102800715763550
c3 = 46223668621385973
'''

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

print nthRoot(n[0], 3)
print nthRoot(n[1], 3)
print nthRoot(n[2], 3)
