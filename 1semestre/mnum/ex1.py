import math

def f(x):
    return x- 2* math.log(x) -5 

def flinha(x):
    return 1 - 2/x

epsilon = 10**(-4)

#bissection

def bissection(a,b):
    while( abs( (b-a) / b ) >= epsilon):
        med = (a+b)/2
        medVal = f(med)
        if(medVal * f(a) < 0 ):
            b = med
        else:
            a = med
    print("zero at x= ", med)

#corda

def corda(a,b):
    while( abs( (b-a) / b ) >= epsilon):
        med = ( f(b) *a - f(a) * b ) / (f(b) - f(a))
        medVal = f(med)
        if(medVal * f(a) < 0 ):
            b = med
        else:
            a = med
    print("Zero using corda ", med)

def newton(guess):
    prev = 0
    while( abs((guess - prev) / guess ) >= epsilon ):
        prev = guess
        if(flinha(guess) == 0):
            break
        guess = guess - f(guess) / flinha(guess)
    print("Value using newton method: ", guess)

def picard(guess):
    def g1(x):
        return math.e**((x-5)/2)
    def g2(x):
        return math.log(x) * 2 +5
    prev = 0
    while(abs( (guess - prev) / guess ) >= epsilon):
        prev = guess
        guess = g2(guess)
    print("Value using picard method: ", guess)

bissection(0.01, 2)
bissection(8, 10)

corda(0.01, 2)
corda(8, 10)

newton(0.03)
newton(9.5)

picard(0.5)         #CANT GO LOWER THAN 1
picard(9.5)