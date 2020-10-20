module Test where

-- Создать структуру из "true" "false" "unknown" и реализовать "и", "или" и "не равно"
data MyBool = MyTrue | MyFalse | MyUnknown

(||) :: MyBool -> MyBool -> MyBool
(||) l r = case (l,r) of
    (MyTrue, _) -> MyTrue
    (_, MyTrue) -> MyTrue
    (MyFalse, MyFalse) -> MyFalse
    otherwise -> MyUnknown

(&) :: MyBool -> MyBool -> MyBool
(&) l r = case (l,r) of
    (MyTrue, MyTrue) -> MyTrue
    (MyFalse, _) -> MyFalse
    (_, MyFalse) -> MyFalse
    otherwise -> MyUnknown

(/=) :: MyBool -> MyBool -> MyBool
(/=) l r = case (l,r) of
    (MyTrue, MyTrue) -> MyFalse
    (MyFalse, MyFalse) -> MyFalse
    (MyTrue, MyFalse) -> MyTrue
    (MyFalse, MyTrue) -> MyTrue
    otherwise -> MyUnknown


-- Создать список вида Plus x, Minus x, Equal входной последовательности
data PlusMinusEq = Plus Integer | Minus Integer | Equal deriving (Show)
fun :: [Integer] -> [PlusMinusEq]
fun (h:[]) = []
fun (h:t) | a > 0 = Plus a : fun t
          | a < 0 = Minus (-a) : fun t
          | a == 0 = Equal : fun t
          where a = head t - h


-- Два списка (одинаковой длинны), написать функцию разницы.
data Difference = Same | Different Int Int deriving (Show)

diff :: [Int] -> [Int] -> [Difference]
diff (h:t) (h1:t1) | h == h1   = Same : diff t t1
                   | otherwise = Different h h1 : diff t t1
diff [] _ = []
diff _ [] = []


-- Реализуйте тип данных, позволяющий задавать команды управления лентой вида "Влево на определённое число шагов",
-- "Вправо на определённое число шагов", "Запись". Реализуйте функцию, которая принимает на вход список
-- команд и начальную позицию и возвращает список позиций, на которых происходила запись.
data Conveyor = MLeft Int | MRight Int | MWrite;

foo :: [Conveyor] -> Int -> [Int]
foo [] x = []
foo (h:t) x = case h of
                  MLeft y -> foo t (x-y)
                  MRight y -> foo t (x+y)
                  MWrite -> x : (foo t x)


-- Создать список вида Multiple a x, Single a входной последовательности
data SingleOrMultiple = Multiple Char Integer | Single Char deriving (Show)

function :: [Char] -> [SingleOrMultiple]
function (h:t) = f h t 1
f x [] acc = if acc == 1 then Single x : [] else Multiple x acc : []
f x (h:t) acc | h == x = f h t (acc + 1)
              | acc == 1 = Single x : f h t 1
              | acc > 1 = (Multiple x acc) : f h t 1

