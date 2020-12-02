import Data.List
myInt = 5555555555555555555555555555555555555555555
double :: Integer -> Integer
double x = x+x

triple :: Integer -> Integer
triple x = x+x+x

penta :: Integer -> Integer
penta x = x+x+x+x+x

test x = (double x + triple x) == (penta x)

maxim:: Integer -> Integer -> Integer
maxim x y =
   if (x > y)
      then x
      else y

maxim3 :: Integer -> Integer -> Integer -> Integer
maxim3 x y z = maxim x (maxim y z)

maxim3v2 :: Integer -> Integer -> Integer -> Integer
maxim3v2 x y z =
  if (x > y)
    then if (x > z)
      then x
      else z
    else if (y > z)
      then y
      else z

maxim3v3 :: Integer -> Integer -> Integer -> Integer
maxim3v3 x y z =
  if (x > y && x > z)
    then x
    else if (y > x && y > z)
      then y
      else z

maxim3v4 :: Integer -> Integer -> Integer -> Integer
maxim3v4 x y z =
  let
    u = (maxim x y)
  in
    maxim u z

maxim4 :: Integer -> Integer -> Integer -> Integer -> Integer
maxim4 x y z k =
  let
    u = maxim x y
    o = maxim z k
  in
    maxim u o

verificareMaxim4 :: Integer -> Integer -> Integer -> Integer -> (Integer, Bool)
verificareMaxim4 x y z w =
  let
    maxim = maxim4 x y z w
  in
    if maxim >= x && maxim >= y && maxim >= z && maxim >= w
      then (maxim, True)
      else (maxim, False)

sumSquareNumb :: Integer -> Integer -> Integer
sumSquareNumb x y = x * x + y * y

paritate :: Integer -> [Char]
paritate x =
  if (mod x 2 == 0)
    then "Par"
    else "Impar"

factorial :: Integer -> Integer
factorial 0 = 1
factorial x = x * factorial (x-1)

describeList :: [a] -> String
describeList xs = "The list is " ++ case xs of [] -> "empty."
                                               [x] -> "a singleton list."
                                               xs -> "a longer list."

factorial2 :: Integer -> Integer
factorial2 x =
  if (x == 0)
    then 1
    else x * factorial2(x - 1)

fact :: Integer -> Integer
fact x = case x of 0 -> 1
                   otherwise -> x * fact(x-1)

verifParam :: Integer -> Integer -> Bool
verifParam x y =
  if (x > 2 * y)
    then True
    else False
