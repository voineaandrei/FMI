import Data.List
import Data.Char

myLast :: [a] -> a
myLast (h:[]) = h
myLast (h:t) = myLast t

myButLast :: [a] -> a
myButLast (h:[x]) = h
myButLast (h:t) = myButLast t

myButLast2 :: [a] -> a
myButLast2 l = head t
  where
    (h:t) = reverse l

myButLast3 :: [a] -> a
myButLast3 = last . init

elementAt :: [a] -> Int -> a
elementAt (h:t) 1 = h
elementAt (h:t) k = elementAt t (k-1)

myLength :: [a] -> Int
myLength [] = 0
myLength (h:t) = 1 + myLength t

myReverse :: [a] -> [a]
myReverse (h:[x]) = [x,h]
myReverse (h:t) = myReverse t ++ [h]

isPalindrom :: Eq a => [a] -> Bool
isPalindrom [_] = True
isPalindrom (h:t) = h == last t && isPalindrom (init t)

isPalindrom2 :: Eq a => [a] -> Bool
isPalindrom2 [_] = True
isPalindrom2 l = isPal l laux
  where
    isPal [_] [_] = True
    isPal (h1:t1) (h2:t2) = h1 == h2 && isPal t1 t2
    laux = reverse l

data NestedList a = Elem a | List [NestedList a] deriving Show
flatten :: NestedList a -> [a]
flatten (Elem x) = [x]
flatten (List (x:xs)) = flatten x ++ flatten (List xs)
flatten (List []) = []

compress :: Eq a => [a] -> [a]
compress [] = []
compress (h:t) = h : (compress.sterge) t
  where
    sterge l = [ x | x <- l, x /= h]

compress2 :: Eq a => [a] -> [a]
compress2 = map head . group
