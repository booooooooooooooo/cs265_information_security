import NGram

ctext = 'CTMYRDOIBSRESRRRIJYREBYLDIYMLCCYQXSRRMLQFSDXFOWFKTCYJRRIQZSMX'
grader = NGram.NGram('quadgrams.txt')
bestScore = -99e9
bestPText = ""

#try every combination and score the decrypted text
for x in xrange(0, 26):
    for y in xrange(0, 26):
        for z in xrange(0, 26):
            key = [x, y, z]
            ptext = ""
            for i in xrange(0, len(ctext)):
                a = chr(((ord(ctext[i])  + key[i%3]) - ord('A')) %26 + ord('A'))
                ptext += a
            score = grader.getScore(ptext)
            if score > bestScore:
                bestScore = score
                bestPText = ptext

print bestPText
