from pycipher import SimpleSubstitution
import NGram
import random
import sys
import collections




#####functions####
def getFreqCounts(ctext):
    letters = collections.Counter(ctext)
    return letters

####global variables####
grader = NGram.NGram('quadgrams.txt')
finalKey = list('ABCDEFGHIJKLMNOPQRSTUVWXYZ')
finalScore = -float("inf")

midKey = finalKey
midScore = finalScore

ITERATION = 100

#####main work flow#####
#read in cipher from input and strip punctuations
inputFile = open("ciphertext")
ctext = ""
for line in inputFile:
    ctext += line.strip('\n')
#decypt automately and log result to console
print "Automate decryption (This may last several seconds)"
i = 0
while i < ITERATION:
    i = i + 1
    random.shuffle(midKey)
    ptext = SimpleSubstitution(midKey).decipher(ctext)
    midScore = grader.getScore(ptext)
    count = 0
    # One iteration ends when midKey keeps stable in 1000 continuous random swapping
    while count < 1000:
        a = random.randint(0,25)
        b = random.randint(0,25)
        midKey[a],midKey[b] = midKey[b], midKey[a]
        ptext = SimpleSubstitution(midKey).decipher(ctext)
        score = grader.getScore(ptext)
        # if the child was better, replace the parent with it
        if score > midScore:
            midScore = score
            count = 0
        else:
            midKey[a],midKey[b] = midKey[b], midKey[a]
        count = count+1
    # keep track of best score so far
    if midScore > finalScore:
        finalScore,finalKey = midScore,midKey[:]#caution: list is mutable
        print "****Best Score so far %d on Iteration %d****"%(midScore,i)
        print SimpleSubstitution(midKey).decipher(ctext)
print "****Automate decryption result****"
print SimpleSubstitution(finalKey).decipher(ctext)

# Let analyst decides whether do manual decryption
nextStep = raw_input("Enter E to ends program; Enter M to do manual decryption:")
while nextStep != "E" and nextStep != "M":
    nextStep = raw_input("Enter E to ends program; Enter C to do manual decryption:")
if nextStep == "E":
    sys.exit()

# do manual decryption or end program.
print "Frequcy counts of ciphertext"
print getFreqCounts(ctext)
while 1:
    manualKey = raw_input("Enter your key corresponding to ABCDEFGHIJKLMNOPQRSTUVWXYZ of ciphertext:")
    ptext = SimpleSubstitution(manualKey).decipher(ctext)
    print "Manual decryition"
    print SimpleSubstitution(manualKey).decipher(ctext)
    nextStep = raw_input("Enter E to end program; Enter C to continue")
    if nextStep == "E":
        break
    elif nextStep == "C":
        continue
    else:
        nextStep = raw_input("Enter E to end program; Enter C to continue")
