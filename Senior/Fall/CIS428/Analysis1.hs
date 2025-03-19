-- Version 1.1
-- 6 September 2017
module Analysis1 where
import Ciphers1
import Data.List
import Data.Char
import Text.Printf (printf)
import Numeric

-- CONTENTS
--   Fpair  - a data type for strings with a frequency
--   Ftable - a data type for freq. tables
--   std    - the standard freq. table for English

--   nlists - the list of all length-n sublists of a list
--   occurrences xs x = the number of occurrences of x in xs
--   countReps ts = a list of pairs of the form (t,n) where
--      t is an item and n is the number of occurrences of t in ts.
--      PRECONDITION: ts is assumed to be sorted. 
--   freqChars text = a sorted Ftable of occurrences of characters
--                    in text
--   freqs n text = returns a sorted frequence table of 30 top occurrences
--                  of length n strings in the text
--   naiveMatch pat text = the list of positions in the text where pat occurs.
--     E.g., (naiveMatch "ab" "abxabab") returns [0,3,5]
--                             0123456
--   kasiski pat text = the size of the gaps between the occurrences
--     of pat in text.  E.g., kasiki  "ab" "abxabab" = [3,2]
--   multiGcd xs = the gcd of all the elements of xs
--   split cs n = [l0,l1,l2 ... , lnsub1] where li = the
--     list of items at positions i, i+n, i+2n, ... 
--     E.g., split 2 "nevermore" = ["nvroe","eemr"]
--     E.g., split 3 "nevermore" = ["neo","err","vme"]
--   ic text = the incidence of coincidence of the text
--   ics n cs =  [ ic txt | txt <- split n cs ]

------------------------------------------------------------------------
------------------------------------------------------------------------

------------------------------------------------------------------------
-- Fpair - frequence pairs
------------------------------------------------------------------------
newtype Fpair = Fpair (String,Double)
  deriving (Eq)
  
instance Show Fpair where
  showsPrec _ (Fpair (cs,n))
    = showString cs . showString " " . showFFloat (Just 4) n

instance Ord Fpair where
  compare (Fpair (cs,m)) (Fpair (ds,n))
          | m == n    = EQ
          | m < n     = LT
          | otherwise = GT

------------------------------------------------------------------------
-- Ftable - a list of frequence pairs
------------------------------------------------------------------------
newtype Ftable = Ftable [Fpair]

instance Show Ftable where
  show = showTable

showTable :: Ftable -> String
showTable (Ftable es)
  = unlines (map showLine es)
    ++ "  One * = " ++ (showFFloat (Just 4) scale "")
    ++ ", frequences are rounded.\n"
  where freq (Fpair (_,f)) = f
        scale              = (maximum (map freq es))/65
        histo p            = replicate (round ((freq p)/scale)) '*'
        showLine p         = show p ++ (' ':histo p)

std = sortTab (Ftable (map Fpair [("a", 0.08167),
                                  ("b", 0.01492),
                                  ("c", 0.02782),
                                  ("d", 0.04253),
                                  ("e", 0.12702),
                                  ("f", 0.02228),
                                  ("g", 0.02015),
                                  ("h", 0.06094),
                                  ("i", 0.06996),
                                  ("j", 0.00153),
                                  ("k", 0.00772),
                                  ("l", 0.04025),
                                  ("m", 0.02406),
                                  ("n", 0.06749),
                                  ("o", 0.07507),
                                  ("p", 0.01929),
                                  ("q", 0.00095),
                                  ("r", 0.05987),
                                  ("s", 0.06327),
                                  ("t", 0.09056),
                                  ("u", 0.02758),
                                  ("v", 0.00978),
                                  ("w", 0.02360),
                                  ("x", 0.00150 ),
                                  ("y", 0.01974),
                                  ("z", 0.00074 )]))

sortTab (Ftable es) = Ftable (sort es)  
------------------------------------------------------------------------
-- nlists xs n = returns a list of all length n sublists of xs
nlists :: [a] -> Int -> [[a]]
nlists xs n = if ((length xs)<n)
                then []
                else (take n xs):(nlists (tail xs) n)
  
-- occurrences xs x = the number of occurrences of x in xs
occurrences :: (Num a, Eq b) => [b] -> b -> a
occurrences xs y = sum [ eq x y | x <- xs]
  where eq x y = if (x==y) then 1 else 0
  
-- countReps ts = a list of pairs of the form (t,n) where
--    t is an item and n is the number of occurrences of t in ts.
--    PRECONDITION: ts is assumed to be sorted.
countReps :: (Eq a) => [a] -> [(a,Int)]
countReps [] = []
countReps (x:xs) = ((x,n):countReps(ys)) 
  where (n,ys)                = countFront x xs 1
        countFront c [] n     = (n,[])
        countFront c (d:ds) n = 
          if (c==d)
            then countFront c ds (n+1)
            else (n,d:ds)
  
------------------------------------------------------------------------
  
-- freqChars text = returns a sorted frequence table of 
--   occurrences of characters in the text
freqChars :: String -> Ftable
freqChars text = Ftable (sort (map count ['a'..'z']))
    where count c = Fpair ([c],(occurrences (map toLower text) c)/len)
          len     = (fromIntegral (length text))


-- freqs n text = returns a sorted frequence table of 
--   30 occurrences of length n strings in the text
freqs :: Int -> String -> Ftable
freqs n text = Ftable (drop top (sort (map freq counts)))
    where freq (s,fc) = Fpair (s,(fromIntegral fc)/(fromIntegral len))
          nstrings    = nlists text n
          len         = (length nstrings)
          counts      = countReps (sort nstrings)
          top         = (length counts) - 30

------------------------------------------------------------------------
  
-- the classic (and not very efficient) naive substring matcher
-- naiveMatch pat text = the list of positions in the text where
--   pat occurs.
-- E.g., naiveMatch "ab" "abxabab" = [0,3,5]
--                        0123456 
naiveMatch :: String -> String -> [Int]
naiveMatch pat text = nmatch text pat 0
    where nmatch [] pat n     = []
          nmatch (c:cs) pat n =
              if (headAgree (c:cs) pat)
                 then n:(nmatch cs pat (n+1))
                 else nmatch cs pat (n+1)
          headAgree _ []      = True
          headAgree [] _      = False
          headAgree (c:cs) (p:ps) =
              if (c==p) 
                 then headAgree cs ps
                 else False
  
-- kasiski pat text = the size of the gaps between the occurrences
--   of pat in text
-- E.g., kasiki  "ab" "abxabab" = [3,2]
kasiski :: String -> String -> [Int]
kasiski pat text = gaps (naiveMatch pat text)
    where gaps []       = []
          gaps [m]      = []  
          gaps (m:n:ns) = (n-m):gaps (n:ns)
  
-- multiGcd xs = the gcd of all the elements of xs
multiGcd :: (Integral a) => [a] -> a
multiGcd = foldr1 gcd 

-- split cs n = [l0,l1,l2 ... , lnsub1] where li = the
--   list of items at positions i, i+n, i+2n, ... 
-- E.g., split 2 "nevermore" = ["nvroe","eemr"]
-- E.g., split 3 "nevermore" = ["neo","err","vme"]
split :: Int -> [a] -> [[a]]
split n cs = transpose (nblocks cs n)
    where nblocks cs n 
           | (null rst)    = [fst]
           | otherwise     = fst:nblocks rst n
           where (fst,rst) = splitAt n cs
  
------------------------------------------------------------------------
  
-- ic text = the incidence of coincidence of the text
ic :: String -> Float
ic text = sum (map g freqs)
    where sum ns = foldr (+) 0 ns
          freqs   = map (occurrences (map toLower text)) ['a'..'z']
          len     = fromIntegral(length text)
          g x     = fromIntegral(x*(x-1))/(len*(len-1))
                      
  
ics :: Int -> String -> [Float]
ics n cs = [ ic txt | txt <- split n cs ]


------------------------------------------------------------------------
-- Temperary Defs
------------------------------------------------------------------------

ct = enVig "doc" (smash toomany)


