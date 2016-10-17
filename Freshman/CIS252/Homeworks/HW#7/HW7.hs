data MyList a = Empty 
		| List a (MyList a)
		deriving (Show)

list0:: MyList a
list1:: MyList Integer
list2:: MyList Int
list3:: MyList Double

list0 = Empty
list1 = Empty
list2 = List 7 Empty
list3 = List 8.5 (List 1.3 (List 20.7 (List 12.4 Empty)))

haskellListToMyList:: [a] -> MyList a
haskellListToMyList [] = Empty
haskellListToMyList xs = List (foldr(\x y-> x) (last xs) xs) (haskellListToMyList (tail xs))

myFoldr:: (a->b->b)->b->MyList a -> b
myFoldr _ b Empty = b
myFoldr a b (List x xs) = a x (myFoldr a b xs)

myListToHaskellList:: MyList a->[a]
myListToHaskellList = myFoldr (:) ([])
