import math

initialVal = math.exp(-1)
for i in range(1,26):
    initialVal = initialVal * i - 1
    print("Value: ", initialVal)