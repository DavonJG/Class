{-Davon Grant-}

one = [x*10 | x <- [1..10], x<11]
two = [if mod x 2==0 then True else False | x <- [1..10], x<11]
three = [x+2| x <- [1..10], x<8 ]
four = [ [x*5]| x <- [1..10], x<7 ]
five = [ (x*100, if (x==1||x==2) then True else False) | x <- [1..10], x<6 ]
six = [((x+10),(x+11)) | x <- [1..10], odd x, x<10 ]
seven = [[11-x]| x <- [1..10], x<11 ]
eight = [ [14-(x*2)] | x <- [1..10], x<8 ]
nine = [ [2,3..3+x] | x <- [1..10], odd x, x<9 ]
ten = [ 6*(6-x) | x <- [1..10], x<7 ]
