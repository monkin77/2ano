import math

def f1(x,y):
    return 2 * (x**2) + x*y -5*x +1 

def f2(x,y): 
    return x + 3*math.log(x) - (y**2)

def f1x(x,y):
    return y + 4*x -5

def f1y(x,y):
    return x

def f2x(x,y):
    return 3/x + 1

def f2y(x,y):
    return -2*y

x = y = 4

while(True):
    prevX = x
    prevY = y
    
    x = prevX - ( ( f1(prevX,prevY) * f2y(prevX, prevY) - f2(prevX, prevY) * f1y(prevX, prevY)  ) / ( f1x(prevX, prevY)*f2y(prevX, prevY) - f2x(prevX, prevY) * f1y(prevX, prevY)  )  )
    y = prevY - ( (f2(prevX,prevY) * f1x(prevX, prevY) - f1(prevX, prevY) * f2x(prevX, prevY)  ) / ( f1x(prevX, prevY) * f2y(prevX, prevY) - f2x(prevX, prevY) * f1y(prevX, prevY)  )  )
    
    if(abs(x - prevX) < 0.1 or abs(y - prevY) < 0.1):
        break

print(x,y)