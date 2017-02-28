import math
x = 2
while 1:
    if ( x**17 ) % 3127 == x:
        print x
        print (x ** 17) % 3127 == x
        break
    x+=1
