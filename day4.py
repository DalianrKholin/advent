fd = open("data")
lines=[]
def contains(r, l,mode):
    counter =0
    for x in l:
        if x in r:
            counter+=1
    if counter==0:
        return 0
    if mode:
        return 2**(counter-1)
    else:
        return counter

def exeOne(lines):
    response = 0
    for x in lines:
        response+= contains(x.split('|')[0].split(),x.split('|')[1].split(),True )
    print(response)

def exeTwo():
    fd = open("data")
    lines = []
    for x in fd:
        lines.append([x[x.index(':')+1:].strip(), 1])
    rax=0
    for x in range(len(lines)):
        rax+=lines[x][1]
        res = contains(lines[x][0].split('|')[0].split(),lines[x][0].split('|')[1].split(),False)
        for y in range(1,res+1):
            lines[x+y][1]+=lines[x][1]
    print(rax)

for x in fd:
    lines.append(x[x.index(':')+1:].strip())
fd.close()

exeOne(lines)
exeTwo()