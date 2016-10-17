{-1. For this problem, you are to define a subtraction function (for non-negative integers) named sub, of type Integer -> Integer -> Integer, using recursion and pred — you cannot use the built-in subtraction function (-).-}
sub:: Integer -> Integer -> Integer
sub minuend subtrahend
	|(minuend<0)||(subtrahend<0) = error "Requires positive inputs"
	| minuend < subtrahend = 0
	| subtrahend > 0 = pred (sub minuend (pred subtrahend))
	| subtrahend == 0 = minuend

{-2.Define a function named quo, of type Integer -> Integer -> Integer, so that an expression of form quo dividend divisor evaluates to the integer quotient of its arguments (e.g., quo 16 5 evaluates to 3).   You must use recursion, succ and subtraction in your definition — you cannot use the built-in div, quot, floor or (/) functions. **INCOMPLETE**-}
quo:: Integer -> Integer -> Integer
quo dividend divisor
	|(dividend<0)||(divisor<0) = error "Requires positive inputs"
	|dividend < divisor = 0
	|dividend==0 = divisor
	|divisor>0 = quo (sub dividend divisor) divisor

{-3. Recursively define a function named listLen, of polymorphic type (Eq a) => [a] -> Int, whose behavior mimics that of the built-in length function covered in class.   Your definition may use any of the list functions covered here or here — except the built-in length function, of course.-}
listLen:: (Eq a) => [a] -> Int
listLen [] = 0
listLen (x:xs) = 1 + listLen xs

{-4. Define a function named isPalindrome, of polymorphic type (Eq a) => [a] -> Bool, which evaluates to True if and only if the sequence of elements in the input list is the same whether read left-to-right or right-to-left.-}
isPalindrome:: (Eq a) => [a] -> Bool
isPalindrome a = a == reverse a

palindrome:: (Eq a) => [a] -> [a]
palindrome a
	|(a==reverse a) = a
	
{-5. Recursively define a function named cc, of type [a] -> [a] -> [a], whose behavior mimics that of the built-in list concatenation (++) function covered in class.   Your definition may use any of the list functions covered here or here — except the built-in (++) function, of course. -}

cc:: [a]->[a]->[a]
cc [] ab = ab
cc(x:xs) ab = x:(cc xs ab)

{-6. Recursively define a function named sumList, of type (Num a) => [a] -> a, whose output is the sum of the elements in the input list (e.g., sumList [1,2,3,4,5] should evaluate to 15).   Your definition may use any of the list functions covered here or here. -}
sumList:: (Num a)=> [a] -> a
sumList [] = 0
sumList(x:xs)=x+ sumList xs

{- 7.Define a function named f, of type (Num a) => a -> a, such that evaluating the expression f x gives the same result as evaluating the expression 3*x+4 (e.g., f 2 should evaluate to 10.0).   Your definition must follow these rules: -}
f::(Num a)=> a -> a
f x = (3*x)+4

{-8.Define a function named g, of type (Num a) => [a] -> [a], such that, given input list [x1,x2,...,xn], yields the output list [3*x1+4,3*x2+4,...,3*xn+4]. -}
g :: (Num a) => [a] -> [a]
g a = map(+4)(map(*3)a)
