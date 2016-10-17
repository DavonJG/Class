data Animal = Snake | Tiger | Mongoose | Wasp | Fish
	deriving ( Eq, Ord, Enum, Show )

--Problem 1.
data Attribute = Brawn|Speed|Wits|GoodLuck
	deriving ( Eq, Ord, Show )
	
mammal :: Animal -> Bool
mammal Tiger = True
mammal Mongoose = True
mammal _ = False

data Creature = Cr String Animal Attribute
	deriving (Eq, Show)

fred,rex,bella:: Creature
fred = Cr "Fred" Fish Brawn
rex = Cr "Rex" Mongoose GoodLuck
bella = Cr "Isabel" Tiger Speed

battle:: Creature -> Creature -> String
battle (Cr name1 sp1 att1) (Cr name2 sp2 att2)
	|att1>att2 = name1 ++ " wins!"
	|att2>att1 = name2 ++ " wins!"
	|otherwise = "It's a draw!"
	
--Problem 2
upgrade:: Creature -> Attribute -> Creature
upgrade (Cr name animalType initialAtt) (new)
	|new>initialAtt = (Cr name animalType new)
	|otherwise = (Cr name animalType initialAtt)
	
--Problem 3
upgradeAll::Attribute-> [Creature]->[Creature]
upgradeAll new crList = [upgrade n new|n<-crList]
	