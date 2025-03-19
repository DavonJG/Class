-- some classic ciphers
-- Version 1.2
-- 5 September 2018
module Ciphers1 where
import Data.List
import Data.Char
import Text.Printf (printf)

-- CONTENTS
--   alphabet = ['a','b', ... , 'z']
--   toNum ch = the index of ch in alphabet
--      Ex: toNum 'a' = 0, toNum 'z' = 25
--   toNums ch = [ toNum c | c <- cs]
--   toChar n = the inversion of toNum
--      Ex: toChar 0 = 'a', toNum 25 = 'z'
--   toChars ns = the inverse of toNums
--   smash cs = the result of removing all nonalphabetic characters and 
--              mapping the alphabetic characters to lower case
--      Ex: smash "Hi, how are you?" = "hihowareyou"
--   monoBy f cs = the result of translating all letters by f
--                 while leaving nonletters alone
--       Ex: monoBy (\n-> (n+1)`mod`26) "abc xyz" = "bcd yza"
--   shift k txt = a +k shift of txt
--       Ex: shift 1 "abc xyz" = "bcd yza"
--   affine (a,b) txt = the application to txt of the
--                      affine cipher with key (a,b) 
--   multy k txt = the application to txt of the multiplicative
--                 cipher with key k
--   enVig k txt = the encryption of txt by the Vigenere cipher with key k
--   deVig k txt = the decryption of txt by the Vigenere cipher with key k
--   would, tst, ... : various text texts
------------------------------------------------------------------------
------------------------------------------------------------------------

-- a list of the lower case alphabetic characters
alphabet :: [Char]
alphabet = ['a'..'z']


-- toNum c = the position of the character c in the alphabet
-- E.g., toNum 'a' = 0, toNum 'b' = 1, ..., toNum 'z' = 25
toNum :: Char -> Int
toNum c = (ord (toLower c)) - (ord 'a') 

-- toNums cs = the list of positions of the characters in the string cs
-- E.g., toNums "abcabc" = [0,1,2,0,1,2]
toNums :: String -> [Int]
toNums cs = [ toNum c | c <- cs ]


-- toChar n = the character at position n, where 0<=n<=25
-- E.g., toChar 0 = 'a', toChar 1 = 'b', ... , toChar 25 = 'z'
toChar :: Int -> Char
toChar n = chr (n + ord 'a')

-- toChars ns = the string of characters at the positions in ns
-- E.g., toChars [0,1,2,0,1,2] = "abcabc"
toChars :: [Int] -> String
toChars ns = [ toChar n | n <- ns ]

------------------------------------------------------------------------
------------------------------------------------------------------------

-- smash cs = the result of removing all nonalphabetic characters and 
--    mapping the alphabetic characters to lower case
-- E.g., smash "Hi, how are you?" = "hihowareyou"
smash :: String -> String
smash cs = [ toLower c | c <- cs, isAlpha c ]

monoBy :: (Int -> Int) -> String -> String
-- (monoBy f cs) 
monoBy f txt = map toUpper [ trans c | c <- txt]
  where trans c = if isAlpha c then toChar(f (toNum c)) else c

shift k txt = monoBy add txt
    where add x = (x+k) `mod` 26

affine (a,b) txt = monoBy aff txt
    where aff x = (a*x+b) `mod` 26

multy k txt = affine (k,0) txt

------------------------------------------------------------------------
-- Vigenere substitution ciphers
------------------------------------------------------------------------

  
-- enVig k cs = the encryption of cs using a Vigenere cipher based on k.
enVig :: String -> String -> String
enVig key cs = map toChar (zipWith plusMod ns ks)
    where ns          = toNums cs
          ks          = toNums repKey
          repKey      = key++repKey
          plusMod a b = (a+b) `mod` 26
  
-- deVig key cs = the decryption of cs using a Vigenere cipher
--    based on key.
deVig :: String -> String -> String
deVig key cs = toChars (zipWith minusMod ns ks)
    where ns = toNums cs
          ks = toNums repKey
          repKey = key++repKey
          minusMod a b = (26+a-b) `mod` 26
    
would = smash "How much wood would a woodchuck chuck if a woodchuck could chuck wood?"

------------------------------------------------------------------------
------------------------------------------------------------------------
--
-- Some texts
--
------------------------------------------------------------------------
------------------------------------------------------------------------

tst =  smash "Meet me at nine o'clock, sharp!"
  
orwell =
    "mostpeoplewhobotherwiththematteratallwouldadmit" 
    ++ "thattheenglishlanguageisinabadwaybutitisgenerally" 
    ++ "assumedthatwecannotbyconsciousactiondoanythingaboutitour" 
    ++ "civilizationisdecadentandourlanguagesotheargumentruns" 
    ++ "mustinevitablyshareinthegeneralcollapseitfollowsthatany" 
    ++ "struggleagainsttheabuseoflanguageisasentimentalarchaism" 
    ++ "likepreferringcandlestoelectriclightorhansomcabsto" 
    ++ "aeroplanesunderneaththisliesthehalfconsciousbeliefthat" 
    ++ "languageisanaturalgrowthandnotaninstrumentwhichweshape" 
    ++ "forourownpurposes"


orwellCrypt = 
    "BNLEGFNGIFJKNANEKFSJDEKEKFBHEEFSHEHIIJNXIMHMBDEEKHEEK"
     ++ "FFURIDLKIHURXHRFDLDUHAHMJHVAXEDEDLRFUFSHIIVHLLXBFM"
     ++ "EKHEJFTHUUNEAVTNULTDNXLHTEDNUMNHUVEKDURHANXEDENXST"
     ++ "DQDIDOHEDNUDLMFTHMFUEHUMNXSIHURXHRFLNEKFHSRXBFUESX"
     ++ "ULBXLEDUFQDEHAIVLKHSFDUEKFRFUFSHITNIIHGLFDEYNIINJL"
     ++ "EKHEHUVLESXRRIFHRHDULEEKFHAXLFNYIHURXHRFDLHLFUEDBF" 
     ++ "UEHIHSTKHDLBIDPFGSFYFSSDURTHUMIFLENFIFTESDTIDRKENS" 
     ++ "KHULNBTHALENHFSNGIHUFLXUMFSUFHEKEKDLIDFLEKFKHIYTNU"
     ++ "LTDNXLAFIDFYEKHEIHURXHRFDLHUHEXSHIRSNJEKHUMUNEHUDU"
     ++ "LESXBFUEJKDTKJFLKHGFYNSNXSNJUGXSGNLFL"


vo = map toUpper (enVig "xy" orwell)

provence = 
    "thealmondtreewasintentativeblossomthedayswere"
    ++ "longeroftenendingwithmagnificienteveningsof"
    ++ "corrugatedpinkskysthehuntingseasonwasoverwith"
    ++ "houndsandgunsputawayforsixmonthsthevineyards"
    ++ "werebusyagainasthewellorganizedfarmerstreated"
    ++ "theirvinesandthemorelackadaiscialneighborshurriedto"
    ++ "dothepruningtheyshouldhavedoneinnovember"
  
vp = enVig "janet" provence

caroll = "YZCCVEZTFJAEPGVWTTNMAXBJIYZCPKMLVUEIOIPHYZCTLATZJESMMESMPDGV" ++
           "YHPKXELVFCEEGQYIYKGWSLVVPYDBCRDZVASUCPGEDOWASUEPKRKLBASUCIII" ++
           "IEQUVIRPVMNXGASUEPHETSMTAIWTKEMCMRPIPLVSHTAUSNTNGERPLKXMTOJX" ++
           "IYRWVEEPGFRLQPFUEVQATSIVMMAMTJENBNCSFZGMHLDGROYMYLYTLQMTLOCM" ++
           "NLVFEGLQP"


toomany 
    = "Did I ever tell you that Mrs. McCave" ++
      "Had twenty-three sons, and she named them all Dave?" ++
      "Well, she did. And that wasn't a smart thing to do." ++
      "You see, when she wants one, and calls out Yoo-Hoo!" ++
      "Come into the house, Dave! she doesn't get one." ++
      "All twenty-three Daves of hers come on the run!" ++
      "This makes things quite difficult at the McCaves'" ++
      "As you can imagine, with so many Daves." ++
      "And often she wishes that, when they were born," ++
      "She had named one of them Bodkin Van Horn." ++
      "And one of them Hoos-Foos. And one of them Snimm." ++
      "And one of them Hot-Shot. And one Sunny Jim." ++
      "Another one Putt-Putt. Another one Moon Face." ++
      "Another one Marvin O'Gravel Balloon Face." ++
      "And one of them Zanzibar Buck-Buck McFate..." ++
      "But she didn't do it. And now it's too late. " 

hw2x1 = "XLCJSLOLWTEEWPVPJDSPVPAETETYPDNCZHLYOPGPCJESTYRESLEXLCJDLTOESPQPODHPCPDFCPEZVYZH"                 

hw2x2 = "FPFKRNEHAFLJHZHKRPHYEVURHHDVSFMHAFLJYRVYMR"

