module Test_4 where

import Data.Map (fromListWith)

-- Реализуйте функцию grokBy, которая принимает на вход список Lst и функцию F и каждому возможному
-- значению результата применения F к элементам Lst ставит в соответствие список элементов Lst,
-- приводящих к этому результату. Результат следует представить в виде списка пар.

--import Data.Function (on)
--import Data.List (sortBy, groupBy)
--import Data.Ord (comparing)
--group :: (Eq a, Ord a) => [(a, b)] -> [(a, [b])]
--group = map ((\l -> (fst . head $ l, map snd l)) . groupBy ((==) `on` fst) . sortBy (comparing fst))

grokBy f l =  fromListWith (++) [(k, [v]) | (k, v) <- map ( \x -> (,) (f x) x) l]


--Даны три натуральных числа, x, y и z. Необходимо найти такие два натуральных числа
-- x1 : x1 <= x
-- y1 : y1 <= y,
-- что их произведение равно z.
r x y z  | x >= z = (z , 0)
         | y >= z = (0 , z)
         | x > y = if z - x <= y then (,) x (z - x) else c
         | x < y = if z - y <= x then (,) (z - y) y else c
          where c = undefined


--Дана пара отсортированных списков чисел xs и ys. Необходимо вернуть отсортированный список, образованный
-- объединением xs и ys. Функцию sort использовать нельзя.
g l [] = l
g [] l = l
g (x:xs) (y:ys) | x < y = x : g xs (y:ys)
                | otherwise = y : g (x:xs) (ys)


--Написать функцию, которая принимает на вход функцию f и число n и возвращает список чисел [f(n), f(n + 1),
-- f(n + 2), f(n + 3)...]
k f n = f n : k f ( n + 1 )


--Реализуйте тип данных, позволяющий задавать команды управления лентой вида "Влево на определённое число шагов",
-- "Вправо на определённое число шагов", "Запись". Реализуйте функцию, которая принимает на вход список
-- команд и начальную позицию и возвращает список позиций, на которых происходила запись.
data MyData = MLeft Int | MRight Int | MWrite;
foo [] x = []
foo (h:t) x = case h of
                  MLeft y -> foo t (x-y)
                  MRight y -> foo t (x+y)
                  MWrite -> x : (foo t x)


--Дан список чисел. Необходимо посчитать число чётных и нечётных чисел в этом списке.
fo l = foldr (\x (a,b) -> if ((mod) x 2 == 0) then (a+1, b) else (a,b+1)) (0,0) l


--Дан список чисел, число n и функция f :: Int -> Int -> Int. Необходимо найти любую такую пару чисел (a,b)
-- в списке, что f a b равно n.
ff (h:t) f n = case ff' h t f n of
                    Nothing -> ff t f n
                    Just x -> x
ff' _ [] _ _ = Nothing
ff' h1 (h:t) f n  = if (f h1 h == n || f h h1 == n) then Just (h1, h) else ff' h1 t f n

--Дан список чисел и функция f :: Int -> Int -> Int. Необходимо найти такую пару чисел (a,b) в списке, что f a b максимально.
--Даны два списка чисел, a и b. Нужно посчитать произведение всех попарных сумм элементов из a и b.
-- Дано число n и функция f :: a -> a. Необходимо вернуть функцию, которая применяет f к своему аргументу n раз.
-- Дан список функций fs :: [Int -> Int] и число n. Необходимо применить все функции из fs к n в порядке встречаемости в fs.
-- 4 массива. такое a из as, b из bs ... что (a*b)/(c*d) -> max
-- show 4 value without deriving
-- Построить уравнение прямой, проходящей через 2 точки

-- Дан список. Отсортировать по убыванию, начиная с n-ого элемента
--mySort :: [Int] -> Int -> [Int]
--mySort ls n = take n ls ++ (sortOn Down) (drop n ls)

-- функция f гарантированно возрастает по обоим аргументам, написать f::int->int->int и x и возвращает произвольные
-- натуральные числа a и b, такие что f a b = x
--invertF f x | x>=0 = invertF' f x (0,0)
--            | otherwise = error "err"
--
--invertF' f x (y1,y2) | f (fst res) (snd res) == x = res
--                     | f (y1+1) 0 > x = error "err1"
--                     | otherwise = invertF' f x (y1+1, 0)
--                     where res = invertF' f x (y1 0)
--
--invertF'' f x (y1 y2) | f y1 y2 == x = (y1 y2)
--                      | f y1 y2 < x = invertF'' f x (y1 y2+1)
--                      | otherwise = (y1 y2)


-- Вернуть длину наибольшей последовательности
longestSpan lst x = longestSpan' lst x 0

longestSpan' [] _ s = s
longestSpan' (h:t) x s | x == h = if (l>s) then longestSpan' (drop l t) x l else longestSpan' (drop l t) x s where l = countX t 1 x

countX [] i x = i
countX (h:t) i x | x == h = countX (i+1) x
                 | otherwise = i


-- проверка скобок
isCorrect [] [] = "Success"
isCorrect s  [] = show . fst . last $ s
isCorrect s (e@(i, c) : l)
  | c `elem` "([{" = isCorrect (e : s) l
  | c `elem` ")]}" = case s of
    []            -> show i
    ((_, t) : s') -> if Just t == lookup c [(')', '('), (']', '['), ('}', '{')]
                     then isCorrect s' l
                     else show i
  | otherwise      = isCorrect s l

main = isCorrect [] . zip [1 ..] <$> getLine >>= putStrLn


-- стек с поддержкой максимума
main = getContents >>= process [] . map words . tail . lines
    where process _  []                 = return ()
          process [] (["push", n] : xs) = process [read n :: Int] xs
          process st (["push", n] : xs) = process (max (head st) (read n) : st) xs
          process st (["pop"    ] : xs) = process (tail st) xs
          process st (["max"    ] : xs) = print (head st) >> process st xs


-- phonebook hashmap
-- import Data.Map.Strict
run m ("add" : k : v : ws) = run (insert k v m) ws
run m ("del" : k : ws) = run (delete k m) ws
run m (_ : k : ws) = putStrLn (findWithDefault "not found" k m) >> run m ws
run _ _ = return ()
main = getContents >>= run empty . tail . words


