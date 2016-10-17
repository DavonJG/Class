import GHC.Float
type X = Double
type Y = Double
type Z = Double
type Rho = Double
type Azimuth = Double
type Polar = Double
type Radius = Double

data Animal = Snake | Tiger | Mongoose | Wasp | Fish
              deriving (Eq, Ord, Enum, Show)

data Attribute = Brawn | Speed | Wits | GoodLuck
              deriving (Eq, Ord, Show)

data Creature = Cr String Animal Attribute
                deriving (Eq, Show)

fred, rex, bella :: Creature
fred             = Cr "Fred" Fish Brawn
rex              = Cr "Rex" Mongoose GoodLuck
bella            = Cr "Isabel" Tiger Speed

qSort'            :: [a] -> (a->a->Bool) -> [a]
qSort' [] cmp     = []
qSort' (x:xs) cmp = qSort' [y | y<-xs, cmp y x] cmp ++ [x] ++ qSort' [y | y<-xs, not (cmp y x)] cmp

--Problem 1
data Coords3D = Rectangular X Y Z
		| Cylindrical Rho Azimuth Z
		| Spherical Radius Azimuth Polar 
	deriving (Show,Eq) 

toRectangular :: Coords3D -> Coords3D
toRectangular (Rectangular 0 _ _) = (Rectangular 0 0 0)
toRectangular (Rectangular _ 0 _) = (Rectangular 0 0 0)
toRectangular (Rectangular _ _ 0) = (Rectangular 0 0 0)
toRectangular (Rectangular a b c) = (Rectangular a b c)
toRectangular (Cylindrical a b c) = (Rectangular (a*cos(b)) (a*sin(b)) c)
toRectangular (Spherical a b c) = (Rectangular (a*sin(c)*cos(b)) (a*sin(b)*sin(c)) (a*cos(c)))

toCylindrical :: Coords3D -> Coords3D
toCylindrical (Cylindrical 0 _ _) = (Cylindrical 0 0 0)
toCylindrical (Cylindrical _ 0 _) = (Cylindrical 0 0 0)
toCylindrical (Cylindrical _ _ 0) = (Cylindrical 0 0 0)
toCylindrical (Cylindrical a b c) = (Cylindrical a b c)
toCylindrical (Rectangular a b c) = (Cylindrical (sqrt((a*a)+(b*b))) (atan(b/a)) c)
toCylindrical (Spherical a b c) = (Cylindrical (a*sin(c)) b (a*cos(c)))

toSpherical :: Coords3D -> Coords3D
toSpherical (Spherical 0 _ _) = (Spherical 0 0 0)
toSpherical (Spherical _ 0 _) = (Spherical 0 0 0)
toSpherical (Spherical _ _ 0) = (Spherical 0 0 0)
toSpherical (Spherical a b c) = (Spherical a b c)
toSpherical (Cylindrical a b c) = (Spherical (sqrt((a*a)+(c*c))) (atan(a/c)) c)
toSpherical (Rectangular a b c) = (Spherical (sqrt((a*a)+(b*b)+(c*c))) (atan(b/a)) (atan((sqrt((a*a)+(b*b)))/c)))


--Problem 2
mapFuncs :: [a->b] -> a -> [b]
mapFuncs [] _ = []
mapFuncs (f:fs) x = f x : (mapFuncs fs x)

mapFuncsListComp :: [a->b] -> a -> [b]
mapFuncsListComp x y = [f y | f <- x]

--Problem 3
mapFuncsList :: [a->b] -> [a] -> [b]
mapFuncsList a b = zipWith ($) a b 

mapFuncsListListComp :: [a->b] -> [a] -> [b]
mapFuncsListListComp a b = zipWith ($) [x | x <-a] [y | y <-b]

--Problem 4
--qSort' [fred,rex,bella] (\ Cr x Cr y->  (if x>y = True) | (otherwise = False) )
--qSort' [fred,rex,bella] (\Cr x Cr y->

--Problem 5 
pointwiseGreater:: Ord b => (a->b) -> (a->b) -> a -> Bool
pointwiseGreater a b c = (a c) > (b c)

