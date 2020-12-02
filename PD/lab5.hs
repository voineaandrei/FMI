import Data.Char

rotate :: Int -> [Char] -> [Char]
rotate _ [] = []
rotate 0 s = s
rotate n (h:t)
  | n < 0 = error "N negativ."
  | n > (length t) + 1 = error "N prea mare."
  | otherwise = rotate (n-1) (t ++ [h])

makeKey :: Int -> [(Char, Char)]
makeKey x = zip ['A'..] (rotate x ['A'..'Z'])

lookUp :: Char -> [(Char, Char)] -> Char
lookUp c [] = c
lookUp c (x:xs)
  | c == fst x = snd x
  | otherwise = lookUp c xs

encipher :: Int -> Char -> Char
encipher x c = chr ((ord c) + x)

encipher2 :: Int -> Char -> Char
encipher2 x c = lookUp c (makeKey x)

normalize :: String -> String
normalize [] = []
normalize (h:t)
  | ord h >= ord 'A' && ord h <= ord 'Z' || ord h > ord '0' && ord h < ord '9' = h : normalize t
  | ord h >= ord 'a' && ord h <= ord 'z' = chr ((ord h) - (ord 'a' - ord 'A')) : normalize t
  | otherwise = normalize t

normalizeEZ :: String -> String
normalizeEZ [] = []
normalizeEZ (h:t)
  | isDigit(h) = h : normalizeEZ t
  | isLetter(h) = toUpper(h) : normalizeEZ t
  | otherwise = normalizeEZ t

encipherStr :: Int -> String -> String
encipherStr x s = map (\y -> encipher2 x y) (normalizeEZ s)

reverseKey :: [(Char, Char)] -> [(Char, Char)]
reverseKey [] = []
reverseKey l = [(snd h, fst h) | h <- l]

decipher :: Int -> Char -> Char
decipher n c = lookUp c $ reverseKey $ makeKey n

decipherStr :: Int -> String -> String
decipherStr n s = [decipher n c | c <- s, isDigit(c) || isUpper(c)]
