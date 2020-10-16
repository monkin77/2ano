import math

def f1(x,y):
    return 2*(x^2) + x*y - 5*x +1

def f2(x,y):
    return x + 3* math.log(x) - y^2

def g1(x,y):
    return ( (x*y + 5*x-1 ) /2 ) ** 0.5

def g2(x,y):
    return (x+3*math.log(x))**0.5

def dg1dx(x,y):
    return 0.3536 * (y+5) / ( (x*y + 5*x -1)**0.5 )

def dg1dy(x,y):
    return 0.3536 * (x) / ( (x*y + 5*x -1)**0.5 )

def dg2dx(x,y):
    return (0.5*(3/x+1)) / (3*math.log(x) + x)**0.5

def dg2dy(x,y):
    return 0

x = y = 4

print( abs(dg1dx(x,y)) + abs(dg2dx(x,y)) )
print( abs(dg1dy(x,y)) + abs(dg2dy(x,y)) )

while(True):
    prevX = x
    prevY = y
    x = g1(prevX, prevY)
    y = g2(prevX, prevY)

    if(abs(x-prevX) < 0.001 or abs(y-prevY)< 0.001):
        break

print(x,y)