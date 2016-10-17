---------------------------------------------------------------
--Lab 9  (Spring 2016)
---------------------------------------------------------------


import Data.Char   -- load Data.Char module to get definition of isUpper

data Shape = Circle Float
           | Rect Double Double
             deriving (Show,Eq)

data Gadget = Gizmo Int
            | Widget Char Float
             deriving (Show,Eq)

smallEven :: Int -> Bool
smallEven x = even x && x < 10

contrived :: Int -> Char -> Bool
contrived x c = isUpper c && odd x



--Removed examples
---------------------------------------------------------------
-- Your problems

--COMPLETED: one, two, three, four, five, six, eight, ten, eleven, twelve
---------------------------------------------------------------

replaceMe = error "replace with your own code"

-- :t one should give       Gadget
one = Gizmo 9        

-- :t two should give       (Char -> Bool, String)
two = checkChar        
	where
	     checkChar x y
		|(x=='a')&&(y==True) = "Correct!"
		|otherwise = "Incorrect"

-- :t three should give     Int -> Bool
three = smallEven

-- :t four should give      [Float -> Gadget]
four = [createGadget]
	where
	    createGadget x = Widget 'a' x

-- :t five should give      [Char] -> [Bool]
five = map (contrived 5) 

-- :t six should give       (String,Bool,Int) -> Char
six = sample        -- replace with your answer
	where
	    sample (a,b,c)
		|(a=="String")&&(b==True)&&(c==4) = 'y'
		|otherwise = 'n'

-- :t seven should give     ((Char -> String) -> Char) -> String
seven = replaceMe       -- replace with your answer

-- :t eight should give     [[Int] -> [Gadget]]
eight = [map Gizmo]

-- :t nine should give      a -> [b]
nine = replaceMe	-- replace with your answer

-- :t ten should give       a -> b -> a
ten = curry fst

-- :t eleven should give    ([a],String) -> [(a,Char)]
eleven = sample     -- replace with your answer
	where
	    sample (a,b)
		|((length a ==5)&&(b=="Ok")) = [(a!!1, chr 99)]
		|otherwise = [(a!!0,chr 88)]

-- :t twelve should give    [a -> b -> c] -> [(a,b) -> c]
twelve = map uncurry

-- :t thirteen should give  (String -> String -> Bool) -> String -> Bool
thirteen = replaceMe    -- replace with your answer

-- :t fourteen should give  (a -> b -> c) -> (a -> b) -> a -> c
--fourteen = replaceMe    -- replace with your answer

