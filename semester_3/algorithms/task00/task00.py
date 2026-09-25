base = set()

with open("input.txt") as inp:
    for line in inp:
        base.add(int(line))

s = 0
for k in base:
    s += k

with open("output.txt", 'w') as outp:
    outp.write(str(s))
