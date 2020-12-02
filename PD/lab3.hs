collatz :: Integer -> [Integer]
collatz n =
  let
    next x = if (even x)
              then (div x 2)
              else (3 * x + 1)
  in
    if (n == 1)
      then [1]
      else n:(collatz (next n))

-- next :: Integer -> Integer
-- next x =
--   if (even x)
--     then div x 2
--     else 3 * x + 1

maxLengthFn :: [[Char]] -> Int
maxLengthFn l = foldr max 0 $ map length $ filter (\x -> head x == 'c') l

factori :: Int -> [Int]
factori n = [x | x <-[1..n], n `rem` x == 0]

prim :: Int -> Bool
prim n
  | length (factori n) == 2 = True
  | otherwise = False

numerePrime :: Int -> [Int]
numerePrime n = [x | x <- [2..n], prim (x)]

myzip3 :: [Int] -> [Int] -> [Int] -> [(Int, Int, Int)]
myzip3 [] _ _ = []
myzip3 _ [] _ = []
myzip3 _ _ [] = []
myzip3 (ha:ta) (hb:tb) (hc:tc) = (ha, hb, hc) : myzip3 ta tb tc

betterMyZip3 :: [Int] -> [Int] -> [Int] -> [(Int, Int, Int)]
betterMyZip3 l1 l2 l3 = zipaux (zip l1 l2) l3
                    where
                      zipaux :: [(Int, Int)] -> [Int] -> [(Int, Int, Int)]
                      zipaux [] _ = []
                      zipaux _ [] = []
                      zipaux ((x,y):xs) (z:zs) = (x,y,z) : zipaux xs zs

aplica2 :: (a -> a) -> a -> a
aplica2 f x = f (f x)

firstEl :: [(a, b)] -> [a]
firstEl l = map (\x -> fst(x)) l

firstEl2 :: [(a, b)] -> [a]
firstEl2 [] = []
firstEl2 (h:t) = fst(h) : firstEl2 t

sumList :: [[Integer]] -> [Integer]
sumList l = map sum l

pre12 :: [Integer] -> [Integer]
pre12 l = map (\x -> if even(x) then x `div` 2 else x*2) l

cautaInCuvinte :: Char -> [[Char]] -> [[Char]]
cautaInCuvinte c l = filter (elem c) l

patrateNumereImpare :: [Integer] -> [Integer]
patrateNumereImpare l = map (^2) (filter odd l)

patratePozitiiImpare :: [Int] -> [Int]
patratePozitiiImpare l = map (\(x,y) -> y^2) (filter (\(x,y) -> x `rem` 2 == 1) (zip [0..length(l)] l))

patratePozitiiImpare2 :: [Int] -> [Int]
patratePozitiiImpare2 l = map ((^2).snd) $ filter (odd.fst) $ zip [0..length(l)] l

numaiVocale :: [String] -> [String]
numaiVocale l = map (\x -> filter (`elem` "aeiouAEIOU") x) l

mymap :: (a -> b) -> [a] -> [b]
mymap f [] = []
mymap f (h:t) = f(h) : mymap f t

myfilter :: (a -> Bool) -> [a] -> [a]
myfilter f l = [x | x<-l, f(x)]

numerePrimeCiur :: Int -> [Int]
numerePrimeCiur x = nrPrimeSel [2..x]
  where
    nrPrimeSel [] = []
    nrPrimeSel (h:t) = h : nrPrimeSel t'
      where
        l2 = [h, 2*h..x]
        t' = filter (\x -> (x `elem` l2) == False) t

ordonataNat :: [Int] -> Bool
ordonataNat [] = True
ordonataNat [x] = True
ordonataNat (x:xs) = and [a < b | (a, b) <- zip (x:xs) xs]

ordonataNat1 :: [Int] -> Bool
ordonataNat1 [] = True
ordonataNat1 [x] = True
ordonataNat1 (x:xs)
  | x < y = True && ordonataNat1 xs
  | otherwise = False
    where
      y = head(xs)

ordonata :: [a] -> (a -> a -> Bool) -> Bool
ordonata [] f = True
ordonata [_] f = True
ordonata (x:xs) f = and [f a b | (a, b) <- zip (x:xs) xs]

(*<*) :: (Integer, Integer) -> (Integer, Integer) -> Bool
(*<*) (x, y) (a, b) = if (x < a && y < b) then True else False

compuneList :: (b -> c) -> [(a -> b)] -> [(a -> c)]
compuneList f [] = []
compuneList f (g:gs) = (f.g) : compuneList f gs

aplicaList :: a -> [(a -> b)] -> [b]
aplicaList a [] = []
aplicaList a (f:fs) = f a : aplicaList a fs

myzip33 :: [a] -> [b] -> [c] -> [(a, b, c)]
myzip33 a b c = map (\((x, y), z) -> (x, y, z)) (zip (zip a b) c)
