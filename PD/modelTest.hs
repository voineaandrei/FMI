import Data.Char
import Data.List

sfChr :: Char -> Bool
sfChr c =
  if (c == '.' || c == '?' || c == '!' || c == ':')
    then True
    else False

propozitii :: [Char] -> Integer
propozitii [] = 0
propozitii (h:t)
  | (sfChr h == True) = 1 + propozitii t
  | otherwise = propozitii t

prop :: [Char] -> Int
prop l = length [ x | x <- l, elem x "?!.:"]


liniiN :: [[Int]] -> Int -> Bool
liniiN matrix n =
  if (minimum (map minimum (filter (\x -> length x == n) matrix))) > 0
    then True
    else False

liniiN2 :: [[Int]] -> Int -> Bool
liniiN2 matr n = minimum (map(minimum) (filter ((==n).length) matr)) > 0

data Punct = Pt [Int]
            deriving Show

data Arb = Vid
          | F Int
          | N Arb Arb
          deriving Show

class ToFromArb a where
  toArb :: a -> Arb
  fromArb :: Arb -> a

toArbPunct :: Punct -> Arb
toArbPunct (Pt []) = Vid
toArbPunct (Pt (h:t)) = N (F h) (toArbPunct (Pt t))

fromArbPunct :: Arb -> Punct
fromArbPunct (Vid) = (Pt [])
fromArbPunct (F x) = (Pt [x])
fromArbPunct (N arb1 arb2) = compPt (fromArbPunct arb1) (fromArbPunct arb2)
  where
    compPt (Pt x) (Pt y) = Pt (x ++ y)

instance ToFromArb Punct where
  toArb = toArbPunct
  fromArb = fromArbPunct
