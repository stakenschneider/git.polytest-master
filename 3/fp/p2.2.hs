module Main where

_foldl :: (b -> a -> b) -> b -> [a] -> b
_foldl _ parameter [] = parameter
_foldl function parameter (element : other) = _foldl function (function parameter element) other

_foldr :: (a -> b -> b) -> b -> [a] -> b
_foldr _ parameter [] = parameter
_foldr function parameter (element : other) = function element (_foldr function parameter other)

_map :: (a -> b) -> [a] -> [b]
_map _ [] = []
_map function list = _foldr (\ element concatable -> function element : concatable) [] list

_flatMap :: (a -> [b]) -> [a] -> [b]
_flatMap _ [] = []
_flatMap function list = _foldl (\ concatable element -> concatable ++ function element) [] list

_concat :: [a] -> [a] -> [a]
_concat left [] = left
_concat [] right = right
_concat left right = _foldr (:) right left

_filter :: (a -> Bool) -> [a] -> [a]
_filter _ [] = []
_filter function list = _foldr (\ element concatable -> if function element then element : concatable else concatable) [] list

_maxBy :: (a -> Integer) -> [a] -> a
_maxBy _ [] = error "Empty list!"
_maxBy function list = _foldl (\ greatest element -> if function element > function greatest then element else greatest) (head list) list

_minBy :: (a -> Integer) -> [a] -> a
_minBy _ [] = error "Empty list!"
_minBy function list = _foldl (\ least element -> if function element < function least then element else least) (head list) list

_reverse :: [a] -> [a]
_reverse [] = []
_reverse list = _foldl (\ concatable element -> element : concatable) [] list

_elementAt :: Integer -> [a] -> a
_elementAt _ [] = error "Index out of bounds!"
_elementAt at list
                  | at < 0 = error "Index out of bounds!"
                  | at == 0 = head list
                  | otherwise = _foldr (\ element hack parameter -> case parameter of
                                          0 -> element
                                          _ -> hack (parameter - 1)) (\ _ -> error "Index out of bounds!") list at

_indexOf :: Eq a => a -> [a] -> Integer
_indexOf _ [] = -1
_indexOf value list
                  | result >= 0 = result
                  | otherwise = -1
                  where
                    result = _foldl (\ index element -> if element == value && index < 0 then abs index - 1 else if index < 0 then index - 1 else index) (-1) list

main :: IO ()
main = putStrLn $ show (_foldl max (-100) [1, -3, 6, -4, -9]) ++ "\n" ++
                  show (_foldr max (-100) [1, -3, 6, -4, -9]) ++ "\n" ++
                  show (_map abs [1, -3, 6, -4, -9]) ++ "\n" ++
                  show (_flatMap (\ number -> [number, number]) [1, -3, 6, -4, -9]) ++ "\n" ++
                  show (_concat [23, 54, 66] [1, -3, 6, -4, -9]) ++ "\n" ++
                  show (_filter (\ number -> number /= 6) [1, -3, 6, -4, -9, 6, 6]) ++ "\n" ++
                  show (_maxBy abs [1, -3, 6, -4, -9, 6, 6]) ++ "\n" ++
                  show (_minBy abs [1, -3, 6, -4, -9, 6, 6]) ++ "\n" ++
                  show (_reverse [1, -3, 6, -4, -9, 6, 6]) ++ "\n" ++
                  show (_elementAt 15000000 [1..15000001]) ++ "\n" ++
                  show (_elementAt 4 [1, -3, 6, -4, -9, 6, 6]) ++ "\n" ++
                  show (_indexOf "string" ["int", "double", "string", "float", "long", "string"]) ++ "\n" ++
                  show (_indexOf 1 [2, 3, 4, 1, 9, 6]) ++ "\n" ++ ""
