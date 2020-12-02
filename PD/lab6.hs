import Data.Char
import Data.List
import Data.Maybe

data Fruct
  = Mar String Bool
  | Portocala String Int
  deriving (Show)

{-
showFruct :: Fruct -> String
showFruct (Mar s b) = "Marul " ++ s ++ (if b then " are viermi." else " nu are viermi.")
showFruct (Portocala s x) = "Portocala " ++ s ++ " are " ++ show x ++ " felii."

instance Show Fruct where
  show = showFruct
-}

-- instance Show Fruct where
--   show (Mar s b) = "Marul " ++ s ++ (if b then " are viermi." else " nu are viermi.")
--   show (Portocala s x) = "Portocala " ++ s ++ " are " ++ show x ++ " felii."

ionatanFaraVierme = Mar "Ionatan" False
goldenCuVierme = Mar "Golden Delicious" True
portocalaSicilia10 = Portocala "Sanguinello" 10
listaFructe = [Mar "Ionatan" False,
                Portocala "Sanguinello" 10,
                Portocala "Valencia" 22,
                Mar "Golden Delicious" True,
                Portocala "Sanguinello" 15,
                Portocala "Moro" 12,
                Portocala "Tarocco" 3,
                Portocala "Moro" 12,
                Portocala "Valencia" 2,
                Mar "Golden Delicious" False,
                Mar "Golden" False,
                Mar "Golden" True]

ePortocalaDeSicilia :: Fruct -> Bool
ePortocalaDeSicilia (Mar _ _) = False
ePortocalaDeSicilia (Portocala s _) = s `elem` ["Tarocco", "Moro", "Sanguinello"]

test_ePortocalaDeSicilia1 =
  ePortocalaDeSicilia (Portocala "Moro" 12) == True
test_ePortocalaDeSicilia2 =
  ePortocalaDeSicilia (Mar "Ionatan" True) == False

nrFeliiSicilia :: [Fruct] -> Int
nrFeliiSicilia [] = 0
nrFeliiSicilia (h:t)
  | ePortocalaDeSicilia h = extrageNrFelii h + nrFeliiSicilia t
  | otherwise = nrFeliiSicilia t
    where
      extrageNrFelii (Portocala _ x) = x

test_nrFeliiSicilia = nrFeliiSicilia listaFructe == 52

nrMereViermi :: [Fruct] -> Int
nrMereViermi [] = 0
nrMereViermi (h:t)
  | eMar h = areViermi h + nrMereViermi t
  | otherwise = nrMereViermi t
    where
      eMar (Mar _ _) = True
      eMar (Portocala _ _) = False
      areViermi (Mar _ b) = if (b == True) then 1 else 0

nrMereViermi2 :: [Fruct] -> Int
nrMereViermi2 [] = 0
nrMereViermi2 (h@(Mar _ b):t) = if (b == True) then (1 + nrMereViermi2 t) else (0 + nrMereViermi2 t)
nrMereViermi2 (_:t) = nrMereViermi2 t

nrMereViermi3 :: [Fruct] -> Int
nrMereViermi3 l = length [s | Mar s True <- l]

test_nrMereViermi = nrMereViermi listaFructe == 2

type NumeA = String
type Rasa = String
data Animal = Pisica NumeA
              | Caine NumeA Rasa
              deriving (Show)

-- showAnimal :: Animal -> String
-- showAnimal (Pisica s) = "Pisica cu numele " ++ s
-- showAnimal (Caine s r) = "Cainele cu numele " ++ s ++ " e de rasa " ++ r
--
-- instance Show Animal where
--   show = showAnimal

pisica1 = Pisica "berry"
caine1 = Caine "hamham" "bischon"

vorbeste :: Animal -> String
vorbeste (Pisica _) = "Meow!"
vorbeste (Caine _ _) = "Woof!"

rasa :: Animal -> Maybe String
rasa (Pisica _) = Nothing
rasa (Caine _ r) = Just (r)


type Nume = String
data Prop
  = Var Nume
  | F
  | T
  | Not Prop
  | Prop :|: Prop
  | Prop :&: Prop
  | Prop :->: Prop
  | Prop :<->: Prop
  deriving (Eq, Read)
infixr 2 :|:
infixr 3 :&:

p1 :: Prop
p1 = (Var "P" :|: Var "Q") :&: (Var "P" :&: Var "Q")

p2 :: Prop
p2 = (Var "P" :|: Var "Q") :&: (Not (Var "P") :&: Not (Var "Q"))

p3 :: Prop
p3 = (Var "P" :&: (Var "Q" :|: Var "R")) :&: ((Not (Var "P") :|: Not (Var "Q")) :&: (Not (Var "P") :|: Not (Var "R")))

instance Show Prop where
  show (Var s) = s
  show (F) = "False"
  show (T) = "True"
  show (Not p) = "(~" ++ show p ++ ")"
  show (p :|: p2) = "(" ++ show p ++ " | " ++ show p2 ++ ")"
  show (p :&: p2) = "(" ++ show p ++ " & " ++ show p2 ++ ")"
  show (p :->: p2) = show p ++ " -> " ++ show p2
  show (p :<->: p2) = show p ++ " <-> " ++ show p2

test_ShowProp :: Bool
test_ShowProp =
  show (Not (Var "P") :&: Var "Q") == "((~P) & Q)"

type Env = [(Nume, Bool)]

impureLookup :: Eq a => a -> [(a, b)] -> b
impureLookup a = fromJust . lookup a

eval :: Prop -> Env -> Bool
eval (Var s) env = impureLookup s env
eval (F) env = False
eval (T) env = True
eval (Not p) env = not(eval p env)
eval (p1 :|: p2) env = eval p1 env || eval p2 env
eval (p1 :&: p2) env = eval p1 env && eval p2 env
eval (a :->: b) e = not (eval a e) || eval b e
eval (a :<->: b) e = (not (eval a e) || eval b e) && (not (eval b e) || eval a e)

test_eval = eval (Var "P" :|: Var "Q") [("P", True), ("Q", False)] == True

variabile :: Prop -> [Nume]
variabile (Var s) = [s]
variabile (F) = []
variabile (T) = []
variabile (Not p) = variabile p
variabile (p1 :|: p2) = nub (variabile p1 ++ variabile p2)
variabile (p1 :&: p2) = nub (variabile p1 ++ variabile p2)
variabile (a :->: b) = nub (variabile a ++ variabile b)
variabile (a :<->: b) = nub (variabile a ++ variabile b)

test_variabile = variabile (Not (Var "P") :&: Var "Q") == ["P", "Q"]

envs :: [Nume] -> [Env] -- [[(Nume1, Bool1)], [(Nume2, Bool2)]]
envs [] = []
envs [x] = [[(x, False)], [(x, True)]]
envs (h:t) = [(h, False):e | e <- envs t] ++ [(h, True):e | e <- envs t]

test_envs = envs ["P", "Q"] == [[("P", False), ("Q", False)],
                                [("P", False), ("Q", True)],
                                [("P", True), ("Q", False)],
                                [("P", True), ("Q", True)]]

satisfiabila :: Prop -> Bool
satisfiabila p = or [eval p env | env <- (envs $ variabile p)]

test_satisfiabila1 = satisfiabila (Not (Var "P") :&: Var "Q") == True
test_satisfiabila2 = satisfiabila (Not (Var "P") :&: Var "P") == False

valida :: Prop -> Bool
valida p = not (satisfiabila (Not p))

test_valida1 = valida (Not (Var "P") :&: Var "Q") == False
test_valida2 = valida (Not (Var "P") :|: Var "P") == True
