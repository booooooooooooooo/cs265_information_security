
# convert key to decimal key
key = ["0x1A","0x2B", "0x3C", "0x4D", "0x5E", "0x6F", "0x77" ]
for p in xrange(0, len(key)):
    key[p] = int(key[p], 16)


s = []
k = []
i = 0
j = 0

keyStream = []

#functions
def show():
    global s, i, j
    print "i = %d"%i
    print "j = %d"%j
    for p in xrange(0, len(s)):
        if(p % 16 == 15):
            print hex(s[p]) + "\\\\"
        else:
            print hex(s[p]),
def initialize():
    global key
    global s, k, i, j, keyStream
    #initlaize s and k
    s = []
    k = []
    for p in xrange(0, 256):
        s.append(p)
        k.append(key[p % len(key)])
    q = 0
    for p in xrange(0, 256):
        q = (q + s[p] + k[p]) % 256
        s[p], s[q] = s[q], s[p]
    #initialze i,j and keyStream
    i = 0
    j = 0
    keyStream = []




##initialize and show
initialize()
show()

##produce keyStream according to requirement

while 1:
    initialize()
    l = raw_input("How many bytes are in key stream (q to exit):\n")
    if(l == 'q'):
        break
    for iteration in xrange(0, int(l)):
        i = (i + 1) % 256
        j = (j + s[i]) % 256
        s[i], s[j] = s[j], s[i]
        t = (s[i] + s[j]) % 256
        keyStream.append(s[t])
    show()
