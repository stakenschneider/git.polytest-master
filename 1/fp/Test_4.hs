module Test_4 where

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


