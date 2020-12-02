import Data.List
import Numeric.Natural

produsRec :: [Integer] -> Integer
produsRec [] = 1
produsRec (h:t) = h * produsRec t

produsFold :: [Integer] -> Integer
produsFold l = foldr (*) 1 l

andRec :: [Bool] -> Bool
andRec [] = True
andRec (h:t) = h && andRec t

andFold :: [Bool] -> Bool
andFold l = foldr (&&) True l

concatRec :: [[a]] -> [a]
concatRec [] = []
concatRec (h:t) = h ++ concatRec t

concatFold :: [[a]] -> [a]
concatFold [] = []
concatFold l = foldr (++) [] l

rmChar :: Char -> String -> String
rmChar c [] = []
rmChar c (s:sx) =
  if (c /= s)
    then s : rmChar c sx
    else rmChar c sx

rmChar2 :: Char -> String -> String
rmChar2 c l = [ x | x <- l, x /= c]

rmCharsRec :: String -> String -> String
rmCharsRec [] l2 = l2
rmCharsRec l1 [] = []
rmCharsRec (h:t) l2 =
  let
    l3 = rmChar h l2
  in
    rmCharsRec t l3

rmCharsRec2 :: String -> String -> String
rmCharsRec2 (h:l1) l2 = rmCharsRec l1 (rmChar h l2)

test_rmchars :: Bool
test_rmchars = rmCharsRec ['a'..'l'] "fotbal" == "ot"

rmCharsFold :: String -> String -> String
rmCharsFold l1 l2 = foldr (rmChar) l2 l1

logistic :: Num a => a -> a -> Natural -> a
logistic rate start = f
  where
    f 0 = start
    f n = rate * f (n - 1) * (1 - f (n - 1))

logistic0 :: Fractional a => Natural -> a
logistic0 = logistic 3.741 0.00079

ex1 :: Natural
ex1 = undefined

ex20 :: Fractional a => [a]
ex20 = [1, logistic0 ex1, 3]

ex21 :: Fractional a => a
ex21 = head ex20

ex22 :: Fractional a => a
ex22 = ex20 !! 2

ex23 :: Fractional a => [a]
ex23 = drop 2 ex20

ex24 :: Fractional a => [a]
ex24 = tail ex20
