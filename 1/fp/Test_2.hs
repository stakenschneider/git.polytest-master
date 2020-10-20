module Test_2 where

-- список функций и число и весь список применяется к числу
foo :: [t -> t] -> t -> t
foo (h:t) v = (foo t ( h v))
foo [] v = v

-- Объединить повторяющиеся элементы в списке
compress (h : t) = compress' t (h:[])

compress' (h : t) lst = if (contain h lst == 1) then compress' t lst else compress' t (h : lst)
compress' [] lst = lst

contain e (h : t) | e == h = 1
                  | e /= h = contain e t
contain _ [] = 0


-- Поместить все последовательные повторяющиеся элементы списка в подсписки
pack lst = unfoldr fun lst

unfoldr f = maybe [] (\ (a, b) -> a : unfoldr f b) . f

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


-- Найти из списка все натуральные
natural lst = natural' lst []
natural' (h:t) lst
    | t == [] = lst
    | otherwise  = natural' t foo where
    foo = if isPrime h == False then lst else lst ++ [h]


-- Удалить каждый n-ый элемент из списка
dropEvery :: [a] -> Int -> [a]
dropEvery lst n = dropEvery' lst n (length  lst `div` n)

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
changeEls lst m n = changeEls' (reverse lst) m n 0 []

changeEls' lst m n i  res | i == length lst =  res
                          | mod (i+1) m == 0  = changeEls' lst m n (i + 1)  res ++  [n]
                          | otherwise     = changeEls' lst m n (i + 1)  res ++  [lst!!i]


-- Дано число. Заменить в нем все нули на 5.
convertFive a = convertFive' (show a) (length (show a)) 0 []

convertFive' lst len i newlst = if i < len then
    if (lst !! i) /= '0'
    then convertFive' lst len i ('5' : newlst)
    else convertFive' lst len i ((lst !! i) : newlst)
    else read newlst


-- Расчитайте расстояние между двумя точками на плоскости.
distance x y x1 y1 = sqrt((x-x1)**2+(y-y1)**2)


-- Дан список чисел. Вывести самую часто встречающуюся цифру (если таких несколько - сумму).
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


-- Удалить все элементы из первого (мб бесконечным) списка, содержащиеся во втором
removeAll (h:t) lst = removeAll' (h:t) lst []

removeAll' [] _ res = res
removeAll' (h:t) lst res | contains h lst = removeAll' t lst res
                         | otherwise = removeAll' t lst (h:res)


-- Являеться ли число палиндромом?
isPalindrome :: Eq a => [a] -> Bool
isPalindrome list = reverse list == list






