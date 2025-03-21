-------------------------------------------------------------------------- 
--									--
--	Matches.hs							--
--	Davon Grant								--
--	(c) Simon Thompson, 1995, 2000					--
--									--
-------------------------------------------------------------------------- 

module Matches2 where

import RegExp2
import Test.QuickCheck

matches :: Reg -> String -> Bool

matches Empty st   = False 

matches Epsilon st = (st == "")

matches (Literal ch) st = (st == [ch])

matches (Or r1 r2) st
  = matches r1 st || matches r2 st

matches (Then r1 r2) st
  = or [ matches r1 s1 && matches r2 s2 | (s1,s2) <- splits st ]

-------------------------------------------------------------------------- 
--	The definition for (Star r) requires some thought. Can think 	--
--	of (Star r) as Epsilon or (Then r (Star r)), but in the latter 	--
--	case the match with (Then r (Star r)) needs to be one in which	--
--	r matches *non-tivially* at the start of the string; otherwise	--
--	there is a possibility of a recursive call to 			--
--		matches (Star r) st					--
--	a black hole!!							--
--									--
--	matches (Star (Or Epsilon (Or (Literal 'a') (Literal 'b')))) 	--
--	is an example of exactly this.					--
-------------------------------------------------------------------------- 

matches (Star r) st
  = matches Epsilon st || 
      or [ matches r s1 && matches (Star r) s2 | (s1,s2) <- frontSplits st ]

--------------------------------------------------------------------------
-- Problem 5: Add equations for Opt and Plus

matches (Opt r) st
    = matches r st || matches Epsilon st

matches (Plus r) st
    = matches r st || matches (Star r) st

-- Try: quickCheck prop_equivA
prop_equivA :: Reg -> ABCDStr -> Bool
prop_equivA re (ABCD str) = (matches re str)==(matches (expand re) str)
    where 
      -- Treat Opt and Plus as macros
      expand (Opt r)       = Or (expand r) Epsilon
      expand (Plus r)      = let r' = expand r in Then r' (Star r')
      expand (Then r1 r2)  = Then (expand r1) (expand r2)
      expand (Or r1 r2)    = Or   (expand r1) (expand r2)
      expand (Star r)      = Star (expand r)
      expand e@(Literal _) = e
      expand Epsilon       = Epsilon


-------------------------------------------------------------------------- 
--	All the ways of splitting a list into two halves.		--
--									--
--	splits [2,3,4] 							--
--	    = [([],[2,3,4]),([2],[3,4]),([2,3],[4]),([2,3,4],[])]	--
-------------------------------------------------------------------------- 

splits :: [a] -> [ ([a],[a]) ]

splits st = [ splitAt n st | n <- [0 .. length st] ]

-------------------------------------------------------------------------- 
--	Splits as above, with the first half non-trivial.		--
-------------------------------------------------------------------------- 

frontSplits :: [a] -> [ ([a],[a]) ]

frontSplits st = [ splitAt n st | n <- [1.. length st] ]

-- STUFF FROM A PREVIOUS COURSE DELETED

-- Some sample reg. expressions
lita = Literal 'a'
litb = Literal 'b'
litc = Literal 'c'
litd = Literal 'd'

-- reg. exp. for {a,b,c,d}^*
abcdStar = Star (lita `Or` litb `Or` litc `Or` litd)
           
-- Strings over {a,b,c,d} that start with a
re1 = lita `Then` abcdStar

-- Strings over {a,b,c,d} that contain the substring ab
re2 = abcdStar `Then` lita `Then` litb `Then`  abcdStar

      
