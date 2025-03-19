import AS1
import Parser1 (aparse)
import Debug.Trace

fixMe = error "Please fix me"

-- For a simple trace, uncomment the next line
-- eval e | trace ("entering eval with arg: "++ show e) False = undefined 
-- Davon Grant
eval (Num  n)        = n
eval (Add  a1 a2)    = (eval a1) + (eval a2)
eval (Sub  a1 a2)    = (eval a1) - (eval a2)
eval (Mult a1 a2)    = (eval a1) * (eval a2)
eval (Div  a1 a2)    = if (eval a2) == 0 then error "cannot divide by 0" else div (eval a1) (eval a2)
eval (Cond a1 a2 a3) = if (eval a1 /= 0) then (eval a2) else (eval a3)

------------------------------------------------------------------------
-- run e 
--   parses e, evaluates e, prints the answer
--   Try: (run "2+3*5")
run :: String -> IO ()
run etxt = do { let e = aparse etxt
              ; putStrLn $ "Evaluating: " ++ show e
              ; let val = eval e
              ; putStrLn $ "    Result: " ++ show val
              }

-- read-eval-print
rep :: IO ()
rep = do { etxt <- getLine;
         ; let e = aparse etxt
         ; let val = eval e
         ; putStrLn $ "Evaluates to:\t"++ show val
         }

data IntTree = Emp | Fork Int IntTree IntTree
     deriving (Show)

hasPathSum :: IntTree -> Int -> Bool
hasPathSum (Fork t Emp Emp) n = (n - t) == 0
hasPathSum (Fork t l Emp) n = hasPathSum l (n-t)
hasPathSum (Fork t Emp r) n = hasPathSum r (n - t)
hasPathSum (Fork t l r) n = (hasPathSum l (n - t) || hasPathSum r (n - t))

levels :: IntTree -> Int -> [Int]
levels Emp _ = []
levels t n = helper t n 0
       where
        helper Emp _ _ = []
        helper (Fork t l r) x w         | t == x =  w : (helper l x (w+1) ++ helper r x (w+1))
                                        | otherwise = (helper l x (w+1) ++ helper r x (w+1))
       

t1 = (Fork 3
           (Fork 1
                 (Fork 3
                       (Fork 3 Emp Emp)
                       (Fork 3 Emp Emp))
                 (Fork 2 Emp Emp))
           (Fork 3
                 (Fork 4 Emp Emp)
                 (Fork 1 Emp Emp)))