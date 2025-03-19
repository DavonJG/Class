-- Written by: Davon Grant

import Test.QuickCheck
import System.Process(system)
import System.IO( hPutStrLn, withFile, IOMode(WriteMode) )
import Control.Monad( liftM, liftM2, liftM3)
import Data.List hiding (insert, delete)
import Data.Char

------------------------------------------------------------------------
-- Binary trees
data BTree = Empty | Branch Char BTree BTree
            deriving (Show,Eq)

-- Multiway trees
data MTree = Node Char [MTree]
        deriving (Eq, Show)

------------------------------------------------------------------------
-- Examples 

t1 = Branch 'x' 
       (Branch 't' 
         (Branch 'a' Empty Empty) 
         Empty) 
       (Branch 'w' 
         (Branch 'm' Empty Empty) 
         (Branch 'q' Empty Empty))

t2 = Node 'u' 
       [Node 'c' [],
        Node 'q' [],
        Node 'n' 
          [Node 'm' [],
           Node 'g' [],
           Node 'j' []],
        Node 'y' 
          [Node 'z' []]]


-- Counting BTree Branch nodes
bcount :: BTree -> Int
bcount Empty = 0
bcount (Branch _ tl tr) = 1 + bcount tl + bcount tr

-- Counting MTree Nodes
mcount :: MTree -> Int
mcount (Node _ ts) = 1 + sum (map mcount ts)

--  preorder traversal for BTrees
preorder Empty = ""
preorder (Branch c tl tr) = c:(preorder tl ++ preorder tr)

-- inorder traversal for BTrees
inorder Empty = ""
inorder (Branch c tl tr) = inorder tl ++ [c] ++ inorder tr
------------------------------------------------------------------------
------------------------------------------------------------------------
fix = error "Please fix me!"

------------------------------------------------------------------------
------------------------------------------------------------------------
-- Part I: Binary and Multiway Trees

------------------------------------------------------------------------
-- Problem 1: BTree depth 
bmaxDepth :: BTree -> Int
bmaxDepth Empty = -1
bmaxDepth (Branch c Empty Empty) = 0
bmaxDepth (Branch c tl Empty) = 1 + bcount(tl)
bmaxDepth(Branch c Empty tr) = 1 + bcount(tr)
bmaxDepth (Branch c tl tr) = if (bmaxDepth tl >= bmaxDepth tr) then 1 + bmaxDepth(tl) else 1 + bmaxDepth(tr)

------------------------------------------------------------------------
-- Problem 2: 
mmaxDepth :: MTree -> Int
mmaxDepth (Node _ []) = 0
mmaxDepth (Node _ ts) = 1 + maximum (map mmaxDepth ts)

------------------------------------------------------------------------
-- Problem 3: Collecting BTree leaves
bleaves :: BTree -> String
bleaves Empty = ""
bleaves (Branch x Empty Empty) = x : ""
bleaves (Branch x tl tr) = (bleaves tl) ++ (bleaves tr)
------------------------------------------------------------------------
-- Problem 4: Collecting MTree leaves
mleaves :: MTree -> String
mleaves (Node x []) = x : ""
mleaves (Node x ts) = concat (map mleaves ts)

------------------------------------------------------------------------
-- Problem 5: BTree levels 
blevel :: Int -> BTree -> String
blevel 0 _ = ""
blevel 1 (Branch x _ _) = x : ""
blevel x (Branch _ Empty tr) = blevel (x-1) tr
blevel x (Branch _ tl Empty) = blevel (x-1) tl
blevel x (Branch _ tl tr) = blevel (x-1) tl ++ blevel (x-1) tr

------------------------------------------------------------------------
-- Problem 6: MTree levels 
mlevel :: Int -> MTree -> String
mlevel 0 _ = ""
mlevel 1 (Node x _) = x : ""
mlevel x (Node _ ts) = concat [mlevel (x-1) t | t <- ts]


------------------------------------------------------------------------
------------------------------------------------------------------------
-- Part II: Rope

data Rope = Leaf String | Fork Rope Rope Int
            deriving (Show,Eq)

-- Example from https://en.wikipedia.org/wiki/Rope_(data_structure)
wiki = concatenate
         (concatenate (Leaf "Hello_") (Leaf "my_"))
         (concatenate (concatenate (Leaf "na") (Leaf "me_i"))
                      (concatenate (Leaf "s")  (Leaf "_Simon")))
(wa,wb) = split wiki 10              


-- size r = the size of a Rope
size (Leaf s)     = length s
size (Fork _ _ n) = n

-- flatten r = the String that Rope r represents
flatten (Leaf s)       = s
flatten (Fork rl rr _) = flatten rl ++ flatten rr

------------------------------------------------------------------------
-- Problem 7: concatenate

concatenate :: Rope -> Rope -> Rope
concatenate (Leaf "") r2 = r2
concatenate r1 (Leaf "") = r1
concatenate r1 r2 = Fork r1 r2 (size r1 + size r2)                           


------------------------------------------------------------------------
-- Problem 8: index

index :: Rope -> Int -> Char
index r i = (flatten r) !! i

------------------------------------------------------------------------
-- Problem 9: split

split :: Rope -> Int -> (Rope,Rope)
split (Leaf str) i = (Leaf (take (i + 1) str), Leaf(drop(i + 1)str))
split (Fork r1 r2 _) i
    | i >= (size r1) = (concatenate r1 (fst (split r2 (i - size r1))), snd (split r2 (i - size r1)))
    | otherwise = (fst (split r1 i), concatenate (snd (split r1 i)) r2)

------------------------------------------------------------------------
-- Problem 10: insert

insert :: Rope -> String -> Int -> Rope
insert r "" _          = r
insert (Leaf "") str _ = Leaf str           
insert r str i = concatenate(concatenate(fst (split r i ))(Leaf str))(snd (split r i))

------------------------------------------------------------------------
-- Problem 11: delete

delete :: Rope -> Int -> Int -> Rope
delete r i j
    | i <= 0 || j <= 0 || (i + j) >= (size r) = r
    | otherwise = concatenate (fst(split r(i - 1)))(snd(split r((i + j)-1)))



------------------------------------------------------------------------
-- Drawing
------------------------------------------------------------------------
-- The following assumes Mac OS X with graphviz installed.
-- (See the download section of: http://www.graphviz.org.)
-- There are probably easy patches to make this work on 
-- other OS's since dump is the only system dependent function.

-- dump str 
--   writes the temp file /tmp/graph.gv with contents str
--   then opens it

dump str = do withFile "/tmp/graph.gv" WriteMode (`hPutStrLn` str)
              system "open /tmp/graph.gv"
                     
-- (drawBTree t) creates a gv description of t and displays it
drawBTree t = dump $ start  ++ nodes ++ edges ++ end
    where
      start = "digraph g {\n    "
      (nodes,edges) = draw t 1
      end   = "}\n"

-- draw tree root_address = (node_decls, edge_decls)
draw :: BTree -> Integer -> (String,String)
draw Empty m = (inode m,"")
    where inode m = (show m) ++ " [style=invis];\n    "
draw (Branch c tl tr) m 
    = ((node c m)++nl++nr,(edge m ml tl)++(edge m mr tr)++el++er)
    where ml      = 2*m
          mr      = 2*m+1
          (nl,el) = draw tl ml
          (nr,er) = draw tr mr
          node c m      = (show m) ++ " [label=" ++ (show [c]) ++ "];\n    "
          edge m n Empty = (show m) ++ "->" ++ (show n) 
                          ++" [style=invis];\n    "
          edge m n _    = (show m) ++ "->" ++ (show n) ++ ";\n    "


-- (drawMTree t) creates a gv description of t and displays it
drawMTree t = dump $ start  ++ nodes ++ edges ++ end
    where
      start = "digraph g {\n    "
      (nodes,edges) = mdrawAux (t,"X")
      end   = "}\n"


-- draw tree root_address = (node_decls, edge_decls)
mdraw :: MTree -> (String,String)
mdraw mt = mdrawAux (mt,"X")

mdrawAux :: (MTree,String) -> (String,String)
mdrawAux (Node c ts,tag) = (nodes,edges)
    where 
      taggedts = zip ts (map (\k->tag++'x':show k) [0..])
      subs = map mdrawAux taggedts
      edge (Node _ _,tag') = tag ++ " -> " ++ tag' ++            ";\n    "
      nodes = (tag ++ " [label=" ++ (show [c]) ++ "];\n    ")
              ++ concatMap fst subs
      edges = (concatMap edge taggedts) ++ concatMap snd subs


-- draw a Rope
drawR r = dump ("digraph g {\n   rankdir=TB\n" ++ gvbuild r 1 ++ "}\n")

xshow i = 'x':show i
          
gvbuild :: Rope -> Int -> String
gvbuild (Leaf s) i
    = concat["   ", xshow i, " [label=\"", quote s,  "\"];\n"]
      where  quote s = "\\\""++s++"\\\""
gvbuild (Fork rl rr n) i
     = concat ["   ", xshow i, " [label=", show n,   "];\n",
               "   ", xshow i, " -> ", xshow (2*i),   ";\n",
               "   ", xshow i, " -> ", xshow (2*i+1), ";\n",
               gvbuild rl (2*i),  gvbuild rr (2*i+1)]
          

------------------------------------------------------------------------
-- Testing
------------------------------------------------------------------------

t10 = Branch 'm' 
     (Branch 'h' 
      (Branch 'c' 
       (Branch 'a' Empty Empty) 
       (Branch 'e' Empty (Branch 'f' Empty Empty)))
      Empty)
     (Branch 'u' 
      (Branch 's' (Branch 'p' Empty Empty) Empty)
      (Branch 'z' Empty Empty))
     
-- QuickCheck BTree generator
instance Arbitrary BTree where
    arbitrary = sized tree
        where
          tree 0 = return Empty
          tree n = do c <- elements (['a'..'z']++['A'..'Z'])
                      m1 <- elements [0..(2*n `div` 3)]
                      m2 <- elements [0..(2*n `div` 3)]
                      liftM2 (Branch c) (variant 1 (tree m1))
                                        (variant 2 (tree m2))

-- QuickCheck MTree generator
instance Arbitrary MTree where
    arbitrary = sized tree
        where
          tree n = do c <- elements (['a'..'z']++['A'..'Z'])
                      m <- elements [0..n]
                      liftM (Node c) (liftM (take m)
                                           (listOf (tree (2*(n-m)`div` 3))))


-- QuickCheck Rope generator

-- (rvalid r) tests if r is a valid Rope
rvalid (Fork t1 t2 n) = rvalid t1 && rvalid t2 && (n==(size t1 + size t2))
rvalid (Leaf _)       = True

refString = ['a'..'z']++['0'..'9']++['A'..'Z']

instance Arbitrary Rope where
    arbitrary = sized tree
        where
          tree n = let m = n `mod` 62
                   in frequency [(1, return (Leaf "")),
                                 (20,rtree (take m refString) m)]
          rtree str m
              = if k < 5
                then return (Leaf str)
                else do j <- choose (1,k-1)
                        let (a,b) = splitAt j str
                        liftM3 Fork (variant 1 (rtree a j))
                                   (variant 2 (rtree b (k-j)))
                                   (return k)
                    where k = length str


------------------------------------------------------------------------
-- Testing for bleaves

bleaves_prop t = and $ zipWith (==) (bleaves (bleafRel t)) ['a'..maxBound]

bleafRel :: BTree -> BTree
bleafRel t = fst $ relab (t,['a'..maxBound])
    where 
      relab (Empty,cs) = (Empty,cs)
      relab (Branch _ Empty Empty,c:cs)=(Branch c Empty Empty,cs)
      relab (Branch c tl tr,cs) = (Branch c tl' tr',cs'')
          where (tl',cs') = relab (tl,cs)
                (tr',cs'') = relab (tr,cs')


------------------------------------------------------------------------
-- Testing for mleaves

mleaves_prop t = and $ zipWith (==) (mleaves (mleafRel t)) ['a'..maxBound]

mleafRel :: MTree -> MTree
mleafRel t = fst $ relab (t,['a'..maxBound])
    where 
      relab (Node _ [],c:cs)=(Node c [],cs)
      relab (Node c ts,cs)  = foo (ts,[],cs)
          where foo ([],ts',cs) = (Node c (reverse ts'),cs)
                foo (t:ts,ts',cs) = let (t',cs') = relab (t,cs)
                                    in foo (ts,t':ts',cs')

------------------------------------------------------------------------

-- Testing for concatenate

concat_prop r1 r2 = rvalid r && flatten r == (flatten r1)++(flatten r2)
    where r = concatenate r1 r2
------------------------------------------------------------------------
-- Testing for index

index_prop (Leaf "") = True
index_prop r = [index r i | i <- [0..(size r)-1]] == flatten r

------------------------------------------------------------------------
-- Testing for split

split_prop (Leaf "") _ = True
split_prop r i = size r1 == 1+j && flatten r1 ++ flatten r2 == flatten r
    where
      j = (i `mod` size r)
      (r1,r2) = split r j 

------------------------------------------------------------------------
-- Testing for insert

insert_prop r "" i = flatten (insert r "" i) == flatten r
insert_prop (Leaf "") str i = flatten (insert (Leaf "") str i)==str
insert_prop r str n = flatten r' == s1 ++ str ++ s2
    where m       = n `mod` (length str)
          (s1,s2) = splitAt (1+m) (flatten r)
          r'      = insert r str m

------------------------------------------------------------------------
-- Testing for delete

delete_prop r m n
    | (size r) <= 2 = flatten r == flatten (delete r m n)
    | otherwise     = flatten r' == s1 ++ s3
    where len     = size r
          i       = 1+(m `mod` (len-2))
          j       = 1+(n `mod` (len-i-1))
          r'      = delete r i j                     
          (s1,s2) = splitAt i (flatten r)
          s3      = drop j s2
          


