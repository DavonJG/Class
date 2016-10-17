import Data.Char
import Pictures

--Functions from ch.3 + old hw used through hw

minThree :: Integer -> Integer -> Integer -> Integer
minThree x y z
	| x <= y && x <= z  = x
	| y <= z = y
	| otherwise = z

maxThree :: Integer -> Integer -> Integer -> Integer
maxThree x y z
	| x >= y && x >= z  = x
	| y >= z = y
	| otherwise = z
	
middleNumber :: Integer -> Integer -> Integer -> Integer
middleNumber x y z
	| between y x z = x
	| between x y z = y
	| otherwise = z

between::Integer->Integer->Integer->Bool 
between x y z
	|(y>=x)&&(y<z) = True
	|otherwise = False
	
--Exercise 5.2 
orderTriple::(Integer,Integer,Integer)->(Integer,Integer,Integer)
orderTriple (x,y,z)= (minThree x y z, middleNumber x y z , maxThree x y z)

--Exercise 5.3
straightLineCheck:: (Integer,Integer) -> (Integer,Integer) -> Integer
straightLineCheck (a,b) (c,d)
	| div (d-b) (c-a) == 0 = error "It never crosses the x axis"
	| otherwise = div (d-b) (c-a)
	
--Exercise 5.19
capitalize:: String -> String
capitalize x = [toUpper y | y<-x]

--Exercise 5.20
divisors:: Integer-> [Integer]
divisors x = [y| y<-[1,2..x], mod x y == 0]

--Exercise 6.8
rotate90::Picture->Picture
rotate90 x = flipV (flipH x)

--Exercise 7.1
firstIntPlusOne:: [Integer] -> Integer
firstIntPlusOne [] = 0
firstIntPlusOne (x:xs) = x+1

--Exercise 7.5
myProduct:: [Integer]->Integer
myProduct [] = 1
myProduct (x:xs) = x * myProduct xs

--Exercise 7.9
unique:: [Integer]->[Integer]
unique [] = []
unique (x:xs)
	|xs /= number = unique number
	|otherwise = x : unique number
	where number = [n|n<-xs,n/=x]
--Exercise 7.11
myReverse :: [x] -> [x]
myReverse [] = []
myReverse (x:xs) = concat [myReverse xs, [x]]

--Exercise 7.14 (ignore the part about writing a QuickCheck property)
{-isSorted:: [Integer]->Bool
isSorted (x:xs)
	| (x !! xs) < (x !! xs+ 1) = False
	|otherwise = True-}