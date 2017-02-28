import math

class NGram(object):
    def __init__(self, gramFile):
        #read file
        inputFile = open("quadgrams.txt")

        #make a gram-freq map
        self.freqMap = {}
        self.SUM = 0
        for line in inputFile:
            line = line.strip('\n')
            pair = line.split(" ")
            if len(pair) == 2:
                self.freqMap[pair[0]] = (int)(pair[1])
                self.SUM += (int)(pair[1])
        #calculate log of probability of each gram
        for gram in self.freqMap.keys():
            self.freqMap[gram] = math.log((float) (self.freqMap[gram])  / self.SUM)
        # get N
        inputFile = open("quadgrams.txt")
        for line in inputFile:
            line = line.strip('\n')
            pair = line.split(" ")
            if len(pair) == 2:
                self.N = len(line.split(" ")[0])
                break
        # set a default probability for non-existing gram
        self.defaultLogProb = math.log(0.01 / self.SUM)


    def getScore(self, ptext):
        score = 0
        for i in xrange(0, len(ptext) - self.N + 1):
            temp = ptext[i: i + self.N]
            if temp in self.freqMap:
                score += self.freqMap[temp]
            else:
                score += self.defaultLogProb
        return score
