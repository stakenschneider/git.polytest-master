module Test where

-- Создать структуру из "true" "false" "unknown" и реализовать "и", "или" и "не равно"
data NewData = MyTrue | MyFalse | MyUnknown

(||) l r = case (l,r) of
    (MyTrue, _) -> MyTrue
    (_, MyTrue) -> MyTrue
    (MyFalse, MyFalse) -> MyFalse
    otherwise -> MyUnknown

(&) l r = case (l,r) of
    (MyTrue, MyTrue) -> MyTrue
    (MyFalse, _) -> MyFalse
    (_, MyFalse) -> MyFalse
    otherwise -> MyUnknown

(/=) l r = case (l,r) of
    (MyTrue, MyTrue) -> MyFalse
    (MyFalse, MyFalse) -> MyFalse
    (MyTrue, MyFalse) -> MyTrue
    (MyFalse, MyTrue) -> MyTrue
    otherwise -> MyUnknown


-- Создать список вида Plus x, Minus x, Equal входной последовательности
data MyData = Plus Integer | Minus Integer | Equal

myDataFun lst = myDataFun2 lst []
myDataFun (h:[])  = l
myDataFun2 (h:t) lst = myDataFun3 h (take 1 t) : lst
myDataFun3 x y
    | a > 0 = Plus a
    | a < 0 = Minus a
    | a == 0 = Equal
    where a = x - y


-- Создать список вида Multiple a x, Single a входной последовательности
data MyData2 = Multiple Char Integer | Single Char deriving(Show)

myData2Fun (h:t) = fff h t 1

fff x (h:t) acc
    | h == x = fff x t (acc + 1)
    | h /= x && acc > 1 = Multiple x acc : fff h t 1
    | h /= x && acc == 1 = Single x : fff h t 1

fff x [] acc
    | acc>0 = Multiple x acc : []
    | acc == 0 = Single x : []


-- Два списка, написать функцию разницы
data MyData3 = Same | Different Int Int deriving(Show)

diff (h:t)(h1:t1) = if (h == h1) then Same : diff t t1 else Different h h1 : diff t t1
diff [] = []


--Реализуйте тип данных, позволяющий задавать команды управления лентой вида "Влево на определённое число шагов",
-- "Вправо на определённое число шагов", "Запись". Реализуйте функцию, которая принимает на вход список
-- команд и начальную позицию и возвращает список позиций, на которых происходила запись.
data MyData = MLeft Int | MRight Int | MWrite;
foo [] x = []
foo (h:t) x = case h of
                  MLeft y -> foo t (x-y)
                  MRight y -> foo t (x+y)
                  MWrite -> x : (foo t x)