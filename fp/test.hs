module Test where

import Prelude hiding (foldl,foldr, unfoldr)

-- Вспомогательные функции

-- (b -> a -> b) -> b -> t a -> b
foldl :: (b -> a -> b) -> b -> [a] -> b
foldl f x []     = x
foldl f x (y:ys) = foldl f (f x y) ys


-- (a -> b -> b) -> b -> t a -> b
foldr :: (a -> b -> b) -> b -> [a] -> b
foldr f x []     = x
foldr f x (y:ys) = f y (foldr f x ys)


-- (b -> Maybe (a, b)) -> b -> [a]
unfoldr :: (b -> Maybe (a, b)) -> b -> [a]
unfoldr f = maybe [] (\ (a, b) -> a : unfoldr f b) . f


-- splitAt n xs -- splitAt 3 [1..5] = ([1,2,3],[4,5])
-- new_element : xs -- 5 : [1..3] = [5,1,2,3]
-- map my_function xs -- map (+1) [1..3] = [2,3.4]
-- drop n xs -- drop 2 [1..5] = [3,4,5]
-- take n xs -- take 2 [1..5] = [1,2]
-- lst !! n -- [0..10] !! 5 = 5
-- filter foo xs -- filter (\x -> x>3) [1..5] = [4,5]
-- elem el lst -- elem 58 [1..100] = True
-- ls1 ++ ls2 -- [1..2] ++ [3,4] = [1,2,3,4]
-- length lst -- length [0..10] = 11
-- reverse lst -- reverse [1..3] = [3,2,1]


-- Объединить повторяющиеся элементы в списке
compress (h : t) = compress' t (h:[])
compress' (h : t) lst = if (contain h lst == 1) then compress' t lst else compress' t (h : lst)
compress' [] lst = lst

contain e (h : t) | e == h = 1
                  | e /= h = contain e t
contain _ [] = 0


-- Поместить все последовательные повторяющиеся элементы списка в подсписки
pack lst = unfoldr fun lst

fun [] = Nothing
fun (h : t) = Just (makeSublist h t [h], remove h t [])

makeSublist _ [] lst = lst
makeSublist x (h : t) lst | h == x = makeSublist x t (x : lst)
                          | h /= x = lst

remove h (h' : t') lst | h == h' =  remove h t' lst
                       | h /= h' =  remove h t' (h' : lst)
remove _ [] lst = lst


-- Разбить список на 2. Размер первого списка задан параметром
mySplit :: [a] -> Int -> ([a], [a])
mySplit list i = ((take i list), (drop i list))


mySplit' :: [a] -> Int -> ([a], [a])
mySplit' lst n = splitAt n lst


-- Список от до - только из составных чисел
compList :: Integer -> Integer -> [Integer]
compList from to = compList' from to []

compList' :: Integer -> Integer -> [Integer] -> [Integer]
compList' from to lst
    | from == to = lst
    | otherwise  = compList' (from +1) to foo where
    foo = if isPrime from then lst else lst ++ [from]

isPrime :: Integer -> Bool
isPrime n = isPrime' n 2

isPrime' :: Integer -> Integer -> Bool
isPrime' x divider
    | x < 0              = error "error: less zero"
    | x == 0 || x == 1   = True
    | x == divider       = True
    | mod x divider == 0 = False
    | otherwise          = isPrime' x (divider + 1)


-- Удалить каждый n-ый элемент из списка
dropEvery :: [a] -> Int -> [a]
dropEvery lst n = dropEvery' lst n (length div lst  n)

dropEvery' :: [a] -> Int -> Int -> [a]
dropEvery' lst n m = if m < 0 then lst
    else (take (n-1) lst) ++ dropEvery' (drop n lst) n (m - 1)


-- Постройте всех спискок простых чисел в диапазоне
primeList :: Integer -> Integer -> [Integer]
primeList from to = primeList' from to []

primeList' :: Integer -> Integer -> [Integer] -> [Integer]
primeList' from to lst
    | from == to = lst
    | otherwise  = primeList' (from + 1) to foo where
    foo = if isPrime from then lst ++ [from] else lst


-- Найти сумму всех натуральных чисел от 1 до n
sumBetween :: Integer -> Integer
sumBetween n = if n > 0
    then foldl (+) 0 [1..n]
    else foldl (+) 0 [n..1]


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


-- Функция, кот сдвигает все элементы по кругу
rotate3 lst y = let (a,b) = if (y > 0) then splitAt (length lst - fuck (length lst) y) lst  else splitAt (fuck (length lst) (abs y)) lst in  b ++ a
fuck len num  = if (num > len) then fuck len (num - len)  else num


-- Найти на бесконечном списке два числа дающих в сумме заданное число
myFuncNumFuck y (h:t) = myFuncNumFuck' y t [h]

myFuncNumFuck' y (h : t) r =  if (hasSum y h r) then takeSum y h r
                           else myFuncNumFuck' y t (h : r)

myFuncNumFuck' _ [] _ = error ":("

hasSum y x [] = False
hasSum y x (h:t) | x + h == y = True
                 | otherwise = hasSum y x t

takeSum y x (h:t) | x + h == y = (x, h)
                  | otherwise = takeSum y x t


-- Дан список и два числа; m, n. Необходимо заменить все элементы списка, кратные индексам m на n.
changeEls lst m n = changeEls' lst m n 0 (length lst) []

changeEls' lst m n i len res | i == len = res
                             | mod i n == 0 = changeEls' lst m n (i+1) len (n : res)
                             | otherwise = changeEls' lst m n (i+1) ((lst !! i) : res)


-- Дано число. Заменить в нем все нули на 5.
convertFive a = convertFive' (show a) (length (show a)) 0 []

convertFive' lst len i newlst = if i < len then
    if (lst !! i) /= '0'
    then convertFive' lst len i ('5' : newlst)
    else convertFive' lst len i ((lst !! i) : newlst)
    else read newlst


-- Расчитайте расстояние между двумя точками на плоскости.
distance x y x1 y1 = sqrt((x-x1)**2+(y-y1)**2)


-- Дан список чисел. Вывести самую частовстречающуюся цифру (если таких несколько - сумму).
-- -- 1 вариант
mostFreq z = map fst $ filter (\ (a,n) -> n == max) pc
         where pc = mostFreq' z
               max = maximum $ map snd pc

mostFreq' []     = []
mostFreq' (x:xs) = (x,n) : (mostFreq' xxs)
            where n   = (length xs) - (length xxs) + 1
                  xxs = filter (/= x) xs

-- -- 2 вариант
-- import Data.List
-- import Data.Ord
-- mostFreq :: Integral a => [a] -> a
-- mostFreq = head . maximumBy (comparing length) . group . sort


-- Даны два списка. Оставить в первом только те элементы, которые есть во втором.
intersect (h:t) lst2 = if (contains h lst2) then (intersect t lst2) ++ [h] else intersect t lst2

contains x [] = False
contains x (h:t) | h == x = True
                 | otherwise = contains x t


-- Дано число. Все цифры, кот не 0 заменить на m
convertN a n = convertN' (show a) n (length (show a)) 0 []

convertN' ls n len i newls = if i < len then
    if (ls !! i) /= '0'
    then convertN' ls n len i (n : newls)
    else convertN' ls n len i ((ls !! i) : newls)
    else read newls


-- Дан список. Отсортировать по убыванию, начиная с n-ого элемента
mySort :: [Int] -> Int -> [Int]
mySort ls n = take n ls ++ (sortOn Down) (drop n ls)


-- Являеться ли число сильным
task_ x y x1 y1 = let a = x*(y1-y)-y*(x1-x)
                      x = y1-y
                      y = x1-x in
                  show [y] ++ "y" ++ " + " ++ [x] ++ "x= " ++ [a]

isStrong n = getSum (digs n) == n

getFact ls = foldl (factorial) 0 lst

getSum ls = foldl (+) 0 getFact ls

factorial 0 = 1
factorial n = n*factorial (n-1)

digs 0 = []
digs x = digs (div x 10) ++ [mod x 10]


-- Построить уравнение прямой, проходящей через 2 точки