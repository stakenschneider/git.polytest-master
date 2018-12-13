module Main where

-- Косинус через ряд Тейлора.

factorial :: Integer -> Integer
factorial step = if step < 2 then 1 else step * factorial (step - 1)

tailor :: Double -> Integer -> Double -> Double
tailor number step precision = if abs result < precision
                               then result
                               else result + tailor number (step + 1) precision
                               where result = (-1) ^ step * number ^ (2 * step) / fromInteger (factorial (2 * step))

optimisation :: Double -> Double
optimisation number = if result <= 2 * pi
                      then result
                      else optimisation (result - 2 * pi)
                      where result = abs number

cosinus :: Double -> Double
cosinus number = tailor (optimisation number) 0 0.000000000001

-- Проверка на существование числа между двумя целыми числами.

toPositive :: Integer -> Integer
toPositive number = if number < 0
                    then 0
                    else number

isInteger :: Double -> Bool
isInteger value = (floor value :: Integer) == (ceiling value :: Integer)

checkSquareBetween :: Integer -> Integer -> Bool
checkSquareBetween first second
                  | minPrepared == maxPrepared = not isMinSqrtInteger && not isMaxSqrtInteger
                  | minPrepared > maxPrepared = False
                  | otherwise = not isMinSqrtInteger || not isMaxSqrtInteger || maxPrepared - minPrepared /= 1
                  where
                    minSqrt = sqrt $ fromInteger $ min (toPositive first) (toPositive second) :: Double
                    maxSqrt = sqrt $ fromInteger $ max (toPositive first) (toPositive second) :: Double
                    isMinSqrtInteger = isInteger minSqrt
                    isMaxSqrtInteger = isInteger maxSqrt
                    minPrepared = ceiling minSqrt :: Integer
                    maxPrepared = floor maxSqrt :: Integer

-- Нахождение наибольшего общего делителя двух целых чисел.

euclideanAlgorithm :: Integer -> Integer -> Integer
euclideanAlgorithm first second = if second == 0
                                  then first
                                  else euclideanAlgorithm second (mod first second)

greatestCommonDivisor :: Integer -> Integer -> Integer
greatestCommonDivisor first second
                          | first == 0 && second == 0 = error "Wrong input parameters!"
                          | first == 0 = abs second
                          | second == 0 = abs first
                          | otherwise = euclideanAlgorithm (abs first) (abs second)

main :: IO ()
main = putStrLn $ show (cosinus 65.0) ++ "\n" ++
                  show (checkSquareBetween 3 4) ++ "\n" ++
                  show (checkSquareBetween 11 17) ++ "\n" ++
                  show (checkSquareBetween 17 11) ++ "\n" ++
                  show (checkSquareBetween 11 11) ++ "\n" ++
                  show (checkSquareBetween 11 16) ++ "\n" ++
                  show (checkSquareBetween 9 16) ++ "\n" ++
                  show (checkSquareBetween 16 9) ++ "\n" ++
                  show (checkSquareBetween 9 17) ++ "\n" ++
                  show (checkSquareBetween 16 16) ++ "\n" ++
                  show (checkSquareBetween (-2) 5) ++ "\n" ++
                  show (checkSquareBetween (-5) (-5)) ++ "\n" ++
                  show (greatestCommonDivisor 43560 (-65536))
