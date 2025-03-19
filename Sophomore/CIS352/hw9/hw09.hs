--Homework 9
--Author: Davon Grant
import Data.List (unlines,replicate)

getInt = do item <- getLine
            return (read item :: Int)

showHisto :: IO()
showHisto = makeList []

makeList :: [Int] -> IO ()
makeList ns = do n <- getInt
                 if (n < 0)
                    then printList ns
                    else makeList (n:ns)
   

printList :: [Int] -> IO ()
printList [] = return ()
printList (n:ns) = do printList ns
                      putStrLn (concat (replicate n "*"))
                     

ask :: String -> IO Char
ask s = do putStr s
           putChar '\t'
           x <- getLine
           if null x 
              then return 'n'
              else return (head x)

game :: IO ()
game = do putStrLn "Think of a number between 1 and 100"
          m <- gameSearch 0 100
          putStr "Your number must be "
          print m

gameSearch l h = do n <- ask ("Is your number <= " ++ (show mid))
                    if (l == mid)||(h == mid)
                       then return mid
                       else do if n == 'n' 
                                  then gameSearch (mid+1) h
                                  else if n == 'y'
                                          then gameSearch l mid
                                          else return mid
                 where mid = (div (h + l) 2)