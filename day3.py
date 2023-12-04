import re

fd= open("data","r")
file=[]
symbols = "$+*/#-&=%@"

for x in fd:
    file.append(x.strip())

def contains(string):
    for x in symbols:
        if x in string:
            return True
    return False

tabLen = len(file)
counter = 0
for x in range(tabLen):
    line = file[x]
    up = x-1 if x-1>=0 else 0
    down = x+1 if x+1<tabLen-1 else tabLen-1
    xd = re.search(r'\d+', line)
    diff=0
    #print(line)
    while xd!=None:
        start = diff+xd.start()-1 if diff+xd.start()-1>=0 else 0
        end = diff+xd.end()+1 if diff+xd.end()+1<140 else 139
        if contains(file[up][start:end]) or contains(file[x][start:end]) or contains(file[down][start:end]):
            counter+=int(xd.group())
        line =line[xd.end():]
        diff+=xd.end()
        xd = re.search(r'\d+',line)
print(counter)
#588958
#673538