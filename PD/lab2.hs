import Data.List
import Data.Char

double :: Integer -> Integer
double x = x+x

fibCaz :: Integer -> Integer
fibCaz x =
  if (x < 2)
    then x
    else fibCaz(x - 1) + fibCaz(x - 2)

fibCaz2 :: Integer -> Integer
fibCaz2 x
  | x < 2 = x
  | otherwise = fibCaz2(x - 1) + fibCaz2(x - 2)

fibEc :: Integer -> Integer
fibEc 0 = 0
fibEc 1 = 1
fibEc x = fibEc (x-1) + fibEc (x-2)

fibPereche :: Integer -> (Integer, Integer)
fibPereche x
  | x == 1 = (0, 1)
  | otherwise =
    let
      (first, second) = fibPereche(x - 1)
    in
      (second, first + second)

fibLiniar :: Integer -> Integer
fibLiniar x
  | x == 0 = 0
  | otherwise = snd(fibPereche(x))


fibLin :: Integer -> Integer
fibLin x
  | x == 0 = 0
  | otherwise = snd(fibPer(x)) where
    fibPer :: Integer -> (Integer, Integer)
    fibPer x
      | x == 1 = (0, 1)
      | otherwise =
        let
          (first, second) = fibPer(x - 1)
        in
          (second, first + second)

fibLin2 :: Integer -> Integer
fibLin2 0 = 0
fibLin2 x = snd(fibPer2(x))
  where
    fibPer2 :: Integer -> (Integer, Integer)
    fibPer2 1 = (0, 1)
    fibPer2 x = (f2, f1 + f2)
      where
        (f1, f2) = fibPer2(x - 1)

add :: Integer -> Integer -> Integer
add x y = x + y

(+++) :: Integer -> Integer -> Integer
(+++) x y = x + y

semiPare :: [Integer] -> [Integer]
semiPare l
  | null l = l
  | even h = h `div` 2 : t'
  | otherwise = t'
  where
    h = head l
    t = tail l
    t' = semiPare t

semiPare2 :: [Int] -> [Int]
semiPare2 [] = []
semiPare2 (h:t)
  | even h = h `div` 2 : t'
  | otherwise = t'
  where
    t' = semiPare2 t

semiPare3 :: [Int] -> [Int]
semiPare3 l = [x `div` 2 | x <- l, even x]

inIntervalRecSabloane :: Int -> Int -> [Int] -> [Int]
inIntervalRecSabloane _ _ [] = []
inIntervalRecSabloane x y (h:t)
  | x <= h && h <= y = h : inIntervalRecSabloane x y t
  | otherwise = inIntervalRecSabloane x y t

inIntervalRec :: Int -> Int -> [Int] -> [Int]
inIntervalRec x y l
  | null l = l
  | x <= h && h <= y = h : t'
  | otherwise = t'
  where
    h = head l
    t = tail l
    t' = inIntervalRec x y t

inIntervalComp :: Int -> Int -> [Int] -> [Int]
inIntervalComp x y l = [n | n <- l, x <= n, n <= y]

pozitiveRec :: [Int] -> Int
pozitiveRec [] = 0
pozitiveRec (h:t)
  | h > 0 = 1 + t' -- + pozitiveRec t
  | otherwise = t' -- + pozitiveRec t
  where            -- fara asta
    t' = pozitiveRec t -- fara asta

pozitiveComp :: [Int] -> Int
pozitiveComp l = length [x | x <- l, x > 0]


pozitiiImpareAj :: [Int] -> Int -> [Int]
pozitiiImpareAj [] _ = []
pozitiiImpareAj (h:t) x
  | mod h 2 /= 0 = x : pozitiiImpareAj t (x+1)
  | otherwise = pozitiiImpareAj t (x+1)

pozitiiImpare :: [Int] -> [Int]
pozitiiImpare l = pozitiiImpareAj l 0

pozitiiImpareComp :: [Int] -> [Int]
pozitiiImpareComp l = [poz | (poz, x) <- zip [0..length(l)] l, mod x 2 /= 0]

multDigits :: [Char] -> Int
multDigits [] = 1
multDigits (h:t)
  | isDigit(h) == True = digitToInt(h) * multDigits t
  | otherwise = multDigits t

multDigitsComp :: [Char] -> Int
multDigitsComp l = product[digitToInt(x) | x <- l, isDigit(x) == True]

discountRec :: [Float] -> [Float]
discountRec [] = []
discountRec (h:t)
  | (h - 1/4 * h) < 200 = (h - 1/4 * h): discountRec t
  | otherwise = discountRec t


discountComp :: [Float] -> [Float]
discountComp l = [x - 1/4 * x | x <- l, x - 1/4 * x < 200]
