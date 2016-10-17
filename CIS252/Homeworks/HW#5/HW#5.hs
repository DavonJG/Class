--Exercise 5.5 + 5.7 + 5.8
data Shape = Circle Double|
	Rectangle Double Double|
	Triangle Double Double Double 
	deriving (Eq,Ord,Show)

area:: Shape->Double
area (Circle r) = 3.14*r*r
area (Rectangle l w) = l*w
area (Triangle base height hypotenuse) = (base*height)/2

isRound::Shape->Bool
isRound (Circle _) = True
isRound (Rectangle _ _) = False
isRound (Triangle _ _ _) = False

perimeter:: Shape->Double
perimeter (Circle r) = 2*3.14*r
perimeter (Rectangle l w) = (2*l)+(2*w)
perimeter (Triangle base height hypotenuse) = base+height+hypotenuse

isRegular:: Shape->Bool
isRegular (Circle _) = True
isRegular (Rectangle l w)
	|l==w = True
	|otherwise = False
isRegular (Triangle base height hypotenuse)
	|(base==height)&&(base==hypotenuse) = True
	|otherwise = False
	
--Exercise 5.21
matches:: Integer -> [Integer] -> [Integer]
matches x y = [n|n<-y, n==x]

eleme :: Integer -> [Integer] -> Bool
eleme x xs
    | (matches x xs) == [] = False
	| otherwise	= True

--Exercise 5.22 
onSeparateLines::[String]->String
onSeparateLines []=""
onSeparateLines x
	|length x == 1 = head x
	|otherwise = (head x)++"\n"++(onSeparateLines(tail x))

--Exercise 5.30
--Exercise 7.2
twoDigitsSum :: [Integer] -> Integer
twoDigitsSum [] = 0
twoDigitsSum (x:xs) = x + (head xs)

--Exercise 7.4
firstDigit :: String -> Char
firstDigit x = head x
--Exercise 7.20
splitAt :: Int -> [a] -> ([a], [a])
splitAt _ [] = ([], [])
splitAt b a
	| b <=0 = ([], a)
	| b >= length a = (a, [])
	| otherwise = (take b a, drop b a)
--Exercise 7.23
myZip3 :: [a] -> [b] -> [c] -> [(a, b, c)]
myZip3 [] _ _ = []
myZip3 _ [] _ = []
myZip3 _ _ [] = []
myZip3 (a:as) (b:bs) (c:cs) = (a, b, c) : myZip3 as bs cs