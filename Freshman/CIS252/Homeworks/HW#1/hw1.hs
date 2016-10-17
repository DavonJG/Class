{-
Davon Grant
CIS252-M007
Homework #1
-}

--1. a function named myOr that acts exactly as the built-in function (||).
myOr:: Bool -> Bool -> Bool
myOr first second
	|first==True = True
	|second==True = True
	|otherwise = False

--2. a function named myEven of type Integer -> Bool that acts exactly as the built-in function even.
myEven:: Integer ->Bool 
myEven input
	|(mod input 2)==0 = True
	|(mod input 2)>0 = False
	
--3. a function named myIsDigit that acts exactly as the built-in function isDigit. 
myIsDigit:: Char -> Bool
myIsDigit enteredChar
	|enteredChar=='0'||enteredChar=='1'||enteredChar=='2'||enteredChar=='3'||enteredChar=='4'||enteredChar=='5'||enteredChar=='6'||enteredChar=='7'||enteredChar=='8'||enteredChar=='9' = True
	|otherwise = False

--4. a function named sumOfSquares that take two Double-valued expressions as inputs and outputs the sum of the squares of the two inputs.
sumOfSquares:: Double->Double->Double 
sumOfSquares x y = ((x*x)+(y*y))

--5. a function named between that takes three Integer-valued expressions as inputs and outputs True if and only if the value of the second input is at least as large as the first input, but smaller than the third input. 
between::Integer->Integer->Integer->Bool 
between x y z
	|(y>=x)&&(y<z) = True
	|otherwise = False

--6. an individual value named p with initial value True and an individual value named q with initial value False. 
p:: Bool
p = True
q:: Bool
q = False

--7. an individual value named x with initial value 2 of type Double and an individual value named y with initial value 3 of type Double. 
x::Double
x=2
y::Double
y=3

--8. an individual value named k with initial value 2525 of type Integer, an individual value named m with initial value 140 of type Integer and an individual value named n with initial value 500 of type Integer. 
k::Integer
k=2525
m::Integer
m=140
n::Integer
n=500

--9. an individual value named c of type Char with initial value 'a' and an individual value named d with initial value 'Z' of type Char. 
c::Char
c='a'
d::Char
d='Z'

