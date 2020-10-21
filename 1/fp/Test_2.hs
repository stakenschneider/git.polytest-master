module Test_2 where

import Data.Map (fromListWith)

-- список функций и число и весь список применяется к числу
foo :: [t -> t] -> t -> t
foo (h:t) v = foo t $ h v
foo [] v = v

-- Удалить все повторяющиеся элементы в списке
compress [] = []
compress (h : t) | contain h t = compress t
                 | otherwise = h : (compress t )

contain _ [] = False
contain e (h : t) | e == h = True
                  | e /= h = contain e t


-- Поместить все последовательные повторяющиеся элементы списка в подсписки
pack :: Eq a => [a] -> [[a]]
pack lst = unfoldr fun lst
unfoldr f = maybe [] (\ (a, b) -> a : unfoldr f b) . f

fun :: Eq a => [a] -> Maybe ([a], [a])
fun [] = Nothing
fun (h : t) = Just (makeSublist h t [h], remove h t [])

makeSublist :: Eq a => a -> [a] -> [a] -> [a]
makeSublist _ [] lst = lst
makeSublist x (h : t) lst | h == x = makeSublist x t (x : lst)
                          | h /= x = lst

remove :: Eq a => a -> [a] -> [a] -> [a]
remove _ [] lst = lst
remove h (h' : t') lst | h == h' =  remove h t' lst
                       | h /= h' =  remove h t' (h' : lst)


-- Разбить список на 2. Размер первого списка задан параметром
mySplit :: [a] -> Int -> ([a], [a])
mySplit list i = ((take i list), (drop i list))
-- or
--mySplit lst n = splitAt n lst


-- Список от и до - только из составных чисел.
compList :: Integer -> Integer -> [Integer]
compList from to | isPrime from  = from : compList (from + 1) to
                 | from == to = []
                 | otherwise = compList (from + 1) to

isPrime :: Integer -> Bool
isPrime n | n < 0  = error("Less zero")
          | n == 1 = False
          | n == 2 = True
          | (length [x | x <- [2 .. n-1], mod n x == 0]) > 0 = False
          | otherwise = True


-- Найти из списка все натуральные
natural :: [Integer] -> [Integer]
natural (h:t) | t == [] = []
              | isPrime h = h : natural t
              | otherwise  = natural t


-- Удалить каждый n-ый элемент из списка
dropEvery :: [a] -> Int -> [a]
dropEvery l 1 = []
dropEvery l n = let dropEvery' :: [a] -> Int -> Int -> [a]
                    dropEvery' [] n k = []
                    dropEvery' (h:t) n k = if (k == n) then dropEvery' t n 1 else h : dropEvery' t n (k+1)
                in dropEvery' l n 1


-- Постройте всех спискок простых чисел в диапазоне
primeList :: Integer -> Integer -> [Integer]
primeList from to = let primeList' :: Integer -> Integer -> [Integer] -> [Integer]
                        primeList' from to lst | from == to = lst
                                               | otherwise  = primeList' (from + 1) to foo
                                               where foo = if isPrime from then lst ++ [from] else lst
                     in primeList' from to []


-- Найти сумму всех натуральных чисел от 1 до n
sumBetween :: Integer -> Integer
sumBetween n | n > 0 = foldl (+) 0 [1..n]
             | otherwise = foldl (+) 0 [n..1]


-- Функция, кот сдвигает все элементы по кругу
rotate :: [a] -> Int -> [a]
rotate l y = let (a,b) = if y > 0 then splitAt (length l - f (length l) y) l else splitAt (f (length l) (abs y)) l
                  where f len num = if (num > len) then f len (num - len) else num
             in  b ++ a


-- Найти на бесконечном списке два числа дающих в сумме заданное число
sumOfTwo :: (Eq a, Num a) => a -> [a] -> (a, a)
sumOfTwo y (h:t) = sumOfTwo' y t [h]

sumOfTwo' :: (Eq a, Num a) => a -> [a] -> [a] -> (a, a)
sumOfTwo' _ [] _ = error "Такой суммы нет"
sumOfTwo' y (h : t) r =  let hasSum y x [] = False
                             hasSum y x (h:t) | x + h == y = True
                                              | otherwise = hasSum y x t

                             takeSum y x (h:t) | x + h == y = (x, h)
                                               | otherwise = takeSum y x t
                         in if (hasSum y h r) then takeSum y h r else sumOfTwo' y t (h : r)


-- Дан список и два числа: m и n. Необходимо заменить все элементы списка, кратные индексам m на n.
changeEls :: Integral a1 => [a2] -> a1 -> a2 -> [a2]
changeEls lst m n = let changeEls' [] _ _ _ = []
                        changeEls' (h:t) m n i | mod i m == 0  = n : changeEls' t m n (i + 1)
                                               | otherwise     = h : changeEls' t m n (i + 1)
                    in changeEls' lst m n 1


-- Рассчитайте расстояние между двумя точками на плоскости.
distance :: Floating a => a -> a -> a -> a -> a
distance x y x1 y1 = sqrt $ (x - x1)^2 + (y - y1)^2


-- Даны два списка. Оставить в первом только те элементы, которые есть во втором.
intersect :: Eq a => [a] -> [a] -> [a]
intersect [] _ = []
intersect (h:t) l | contain h l = h : (intersect t l)
                  | otherwise = intersect t l


-- Удалить все элементы из первого списка (может быть бесконечным), содержащиеся во втором.
removeAll :: Eq a => [a] -> [a] -> [a]
removeAll [] _ = []
removeAll (h:t) lst  | contain h lst = removeAll t lst
                     | otherwise = h : removeAll t lst


-- Является ли число палиндромом?
isPalindrome :: Eq a => [a] -> Bool
isPalindrome list = reverse list == list


-- Реализуйте функцию grokBy, которая принимает на вход список Lst и функцию F и каждому возможному
-- значению результата применения F к элементам Lst ставит в соответствие список элементов Lst,
-- приводящих к этому результату. Результат следует представить в виде списка пар.
--grokBy :: (a -> k) -> [a] -> [(k, [a])]
grokBy f l =  fromListWith (++) [(k, [v]) | (k, v) <- map ( \x -> (,) (f x) x) l]
-- or
--import Data.Function (on)
--import Data.List (sortBy, groupBy)
--import Data.Ord (comparing)
--group :: (Eq a, Ord a) => [(a, b)] -> [(a, [b])]
--group = map ((\l -> (fst . head $ l, map snd l)) . groupBy ((==) `on` fst) . sortBy (comparing fst))


--Даны три натуральных числа, x, y и z. Необходимо найти такие два натуральных числа
-- x1 : x1 <= x
-- y1 : y1 <= y, что их произведение равно z.
r x y z  | x >= z = (z , 0)
         | y >= z = (0 , z)
         | x > y = if z - x <= y then (,) x (z - x) else c
         | x < y = if z - y <= x then (,) (z - y) y else c
         where c = undefined


--Дана пара отсортированных списков чисел xs и ys. Необходимо вернуть отсортированный список, образованный
-- объединением xs и ys. Функцию sort использовать нельзя.
g :: Ord a => [a] -> [a] -> [a]
g l [] = l
g [] l = l
g (x:xs) (y:ys) | x < y = x : g xs (y:ys)
                | otherwise = y : g (x:xs) ys


--Написать функцию, которая принимает на вход функцию f и число n и возвращает список чисел [f(n), f(n + 1), ...]
k :: Num t => (t -> a) -> t -> [a]
k f n = f n : k f ( n + 1 )


--Дан список чисел. Необходимо посчитать число чётных и нечётных чисел в этом списке.
fo :: (Foldable t, Integral a1, Num a2, Num a3) => t a1 -> (a2, a3)
fo = foldr (\x ((,) a b) -> if odd x then (a + 1, b) else (a , b + 1)) (0 , 0)


--Дан список чисел, число n и функция f :: Int -> Int -> Int. Необходимо найти любую такую пару чисел (a,b)
-- в списке, что f a b равно n.
ff (h:t) f n = case ff' h t f n of
                    Nothing -> ff t f n
                    Just x -> x
ff' _ [] _ _ = Nothing
ff' h1 (h:t) f n  = if (f h1 h == n || f h h1 == n) then Just (h1, h) else ff' h1 t f n


-- Функция для определения первой позиции вхождения заданного элемента в список.
task :: [Int] -> Int -> Int
task (x:xs) e
    | x == e    = 0
    | xs == [] = error("Not exist")
    | otherwise = 1 + task xs e


-- Определить, является ли указанное число элементом списка.
task1 :: [Int] -> Int -> Bool
task1 (x:xs) e
    | x == e    = True
    | xs == []  = False
    | otherwise     = False || task1 xs e
-- or
-- task1 x = elem x