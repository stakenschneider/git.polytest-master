module Test where

import Prelude hiding (foldl,foldr, unfoldr)

-- foldl (/) 64 [4,2,4]
-- 2.0
foldl :: (b -> a -> b) -> b -> [a] -> b
foldl f x []     = x
foldl f x (y:ys) = foldl f (f x y) ys


-- foldr (+) 5 [1,2,3,4]
-- 15
foldr :: (a -> b -> b) -> b -> [a] -> b
foldr f x []     = x
foldr f x (y:ys) = f y (foldr f x ys)


-- unfoldr (\b -> if b == 0 then Nothing else Just (b, b-1)) 10
-- [10,9,8,7,6,5,4,3,2,1]
unfoldr :: (b -> Maybe (a, b)) -> b -> [a]
unfoldr f b0 = build (\c n ->
  let go b = case f b of
               Just (a, new_b) -> a `c` go new_b
               Nothing         -> n
  in go b0)

build g = g (:) []


-- splitAt 3 [1..5]
-- ([1,2,3],[4,5])
splitAt                :: Int -> [a] -> ([a],[a])
splitAt n xs           =  (take n xs, drop n xs)

-- map reverse ["abc","cda","1234"]
-- ["cba","adc","4321"]
-- map :: (a -> b) -> [a] -> [b]

-- drop 2 [1..5]
-- [3,4,5]
-- drop :: Int -> [a] -> [a]


-- take 2 [1..5]
-- [1,2]
-- take :: Int -> [a] -> [a]

-- [0..10] !! 5
-- 5
-- (!!) :: [a] -> Int -> a

-- filter (\x -> x>3) [1..5]
-- [4,5]
-- filter :: (a -> Bool) -> [a] -> [a]

-- elem 58 [1..100]
-- True
-- elem :: (Foldable t, Eq a) => a -> t a -> Bool

-- 1 : [2,3,4]
-- [1,2,3,4]
-- (:) :: a -> [a] -> [a]

-- [1..2] ++ [3,4]
-- [1,2,3,4]
-- (++) :: [a] -> [a] -> [a]

-- length [0..9]
-- 10
-- length :: Foldable t => t a -> Int

-- reverse [1..3]
-- [3,2,1]
--reverse :: [a] -> [a]

