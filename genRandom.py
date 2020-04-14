import random

file = open("in.txt", "w")

for i in range(0, 1000):
    line = random.randint(1, 10)
    file.write(str(line) + "\n")

file.close()
