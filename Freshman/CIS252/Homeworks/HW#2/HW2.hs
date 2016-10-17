--1. Define a function named taxOwed of type Double -> Bool -> Double that calculates tax owed based on income and marital status (True means married, False means single) according to the following criteria:

taxOwed:: Double->Bool->Double
taxOwed income married
	|(income<0)= error "ERROR: Negative income."
	|(income<100000)&&(married) = (income*0.10)
	|(income>=100000)&&(married) = 10000 + ((income-100000)*0.2)
	|(income<100000)&&(not married) = (income*0.15)
	|(income>=100000)&&(not married)= 15000+((income-100000)*0.25)
	
--Enumerated types
data Quadrant = UpperRight | UpperLeft | LowerLeft | LowerRight | OnAxis
	deriving (Enum,Eq,Show)
type Coords = (Double,Double)

{-}2. Now, finally, define a function named inQuadrant of type Coords -> Quadrant, so that:

if input point is in the upper-right quadrant, the value UpperRight is returned
if input point is in the upper-left quadrant, the value UpperLeft is returned
if input point is in the lower-left quadrant, the value LowerLeft is returned
if input point is in the lower-right quadrant, the value LowerRight is returned
if input point is on either axis (this includes being on both axes), the value OnAxis is returned-}

inQuadrant:: Coords->Quadrant
inQuadrant (xCoord,yCoord)
	|(xCoord>0.0)&&(yCoord>0.0) = UpperRight
	|(xCoord<0.0)&&(yCoord>0.0) = UpperLeft
	|(xCoord<0.0)&&(yCoord<0.0) = LowerLeft
	|(xCoord>0.0)&&(yCoord<0.0) = LowerRight
	|(xCoord==0.0)||(yCoord==0.0) = OnAxis
	
	
{-3. Recursively define a function named altFact of type Integer -> Integer -> Integer, which will be a generalization of the factorial function fact covered in class.   The expression altFact n r must evaluate to the product of all the numbers from n down to r, assuming n > r.   Here's the full specification, including all the "corner cases": 

if n is greater than r, altFact n r returns the value of the product n*(n-1)*(n-2)*...*r
if n equals r, altFact n r returns the value of n
if n is less than r, altFact n r returns 1

Note that altFact n 1 has the same value as fact n for all values of n for which fact is defined (i.e., altFact really does generalize fact).   However, altFact n r is defined for all Integer values of n and r. -}

altFact:: Integer->Integer->Integer
altFact n r
	|n<r= (-1)
	|n>r = n*(altFact(n-1)(r))
	|n==r = n
	
--add, mult, and expo functions taken from recursion.hs
add :: Integer -> Integer -> Integer
add m n 
    | n < 0 || m < 0 = error "add not defined for negative arguments"
    | n == 0         = m
    | n > 0          = (add m (n-1)) + 1 
	
mult :: Integer -> Integer -> Integer
mult m n 
    | n < 0 || m < 0 = error "mult not defined for negative arguments"
    | n == 0         = 0
    | n > 0          = add m (mult m (n-1))

expo :: Integer -> Integer -> Integer
expo m n 
    | n < 0 || m < 0 = error "expo not defined for negative arguments"
    | n == 0         = 1
    | n > 0          = mult m (expo m (n-1))
	
{-4.Recursively define a function named superExpo, of type Integer -> Integer -> Integer, which you might consider the function "next up" in this sequence of functions covered in class: add, mult and expo.   Just as multiplication is repeated addition and exponentiation is repeated multiplication, "super exponentiation" may be considered repeated exponentiation.   Here are the particulars of how to evaluate superExpo m n:


-if n is zero, superExpo m n returns 1.
-if n is greater than zero, superExpo m n returns m raised to this power: superExpo m (n-1)
-both arguments must be non-negative-}

superExpo:: Integer->Integer->Integer
superExpo m n
	|n<0 || m<0 = error "superExpo not defined for negative arguments"
	|n == 0 = 1
	|n > 0 = expo m (superExpo m(n-1))
	