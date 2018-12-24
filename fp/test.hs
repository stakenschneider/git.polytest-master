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

-- head, tail, minimum, maximum


-- Задания
-- объединить повторяющиеся элементы в списке
compress (h : t) = compress' t (h:[])
compress' (h : t) lst = if (contain h lst == 1) then compress' t lst else compress' t (h : lst)
compress' [] lst = lst

contain e (h : t) | e == h = 1
                  | e /= h = contain e t
contain _ [] = 0

-- 1. Вар 2
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


-- 2. Вар 2
-- Разбить список на 2. Размер первого списка задан параметром
mySplit :: [a] -> Int -> ([a], [a])
mySplit list i = ((take i list), (drop i list))


mySplit' :: [a] -> Int -> ([a], [a])
mySplit' lst n = splitAt n lst


-- список от до - только из составных чисел
compList :: Integer -> Integer -> [Integer]
compList from to = compList' from to []

compList' :: Integer -> Integer -> [Integer] -> [Integer]
compList' from to lst 
    | from == to = lst
    | otherwise  = compList' (from +1) to foo where
    foo = if isPrime from then lst else lst ++ [from]


-- проверка на простоту
isPrime :: Integer -> Bool
isPrime n = isPrime' n 2

isPrime' :: Integer -> Integer -> Bool
isPrime' x divider
    | x < 0              = error "error: less zero"
    | x == 0 || x == 1   = True
    | x == divider       = True
    | mod x divider == 0 = False
    | otherwise          = isPrime' x (divider + 1)



-- 2. Вар 1
-- Удалить каждый n-ый элемент из списка
dropEvery :: [a] -> Int -> [a]
dropEvery lst n = dropEvery' lst n (length div lst  n)

dropEvery' :: [a] -> Int -> Int -> [a]
dropEvery' lst n m = if m < 0 then lst
    else (take (n-1) lst) ++ dropEvery' (drop n lst) n (m - 1)



-- 3. Вар 1
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
