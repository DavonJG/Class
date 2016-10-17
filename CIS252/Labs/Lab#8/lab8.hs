--addThree is used for testing
addThree::(Int,Int,Int)->Int
addThree (x,y,z) = (x+y+z)

simple :: Int -> Int -> Int
simple a b = a + 3*b

uncurriedSimple :: (Int,Int) -> Int
uncurriedSimple (a,b) = a + 3*b

--Problem 1:
curry3:: ((a,b,c)->d) -> (a->b->c->d)
curry3 f x y z = (f(x,y,z))

--Problem 2:
diagFun:: ((a,a)->b) -> (a->b)
diagFun f x = f (x,x)

--Problem 3:
cross::((a->b),(c->d)) -> ((a,c)->(b,d))
cross (f,g) = (\ (x,y)->(f x, g y))
