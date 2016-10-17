import Data.Char

--Problem 1
sqRoots :: [Float]->[Float]
sqRoots first = map sqrt first

--Problem 2
getLengths :: [String] -> [(String, Int)]
getLengths strs = map (\a->(a,(length a))) strs

--Problem 3
grabOdds:: [Integer]->[Integer]
grabOdds nums = filter odd nums

--Problem 4
vowels:: [(Char,Int)]->[(Char,Int)]
vowels pairs = filter (\(x,y)->((isVowel x==True))) pairs
	where
		isVowel c = elem (toLower c) "aeiou"

--Problem 5
mystery :: Int -> [Int] -> [Int]
mystery q ms = [ m-10 | m <- ms, m > 2*q]

mystery2 :: Int -> [Int] -> [Int]
mystery2 q ms = map (\x-> x-10) (filter (>(2*q)) ms)