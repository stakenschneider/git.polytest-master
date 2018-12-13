module Main where

data BinaryTree = EmptyTree
                  | Leaf Integer
                  | Node Integer BinaryTree BinaryTree deriving(Show)

infixl 9 `insertValue`
insertValue :: BinaryTree -> Integer -> BinaryTree
insertValue EmptyTree value = Leaf value
insertValue (Leaf integer) value
                  | value < integer = Node integer (Leaf value) EmptyTree
                  | otherwise = Node integer EmptyTree (Leaf value)
insertValue (Node integer left right) value
                  | value == integer = Node integer EmptyTree (Node integer left right)
                  | value < integer = Node integer (insertValue left value) right
                  | otherwise = Node integer left (insertValue right value)

-- В общем случае работает неверно, insertNode должна использоваться только для соседних Node одного дерева.
insertNode :: BinaryTree -> BinaryTree -> BinaryTree
insertNode tree EmptyTree = tree
insertNode EmptyTree node = node
insertNode tree (Leaf integer) = insertValue tree integer
insertNode (Leaf linteger) (Node vinteger vleft vright)
                  | vinteger < linteger = Node linteger (Node vinteger vleft vright) EmptyTree
                  | otherwise = Node linteger EmptyTree (Node vinteger vleft vright)
insertNode (Node tinteger tleft tright) (Node vinteger vleft vright)
                  | vinteger < tinteger = Node tinteger (insertNode tleft (Node vinteger vleft vright)) tright
                  | otherwise = Node tinteger tleft (insertNode tright (Node vinteger vleft vright))

infixl 9 `removeValue`
removeValue :: BinaryTree -> Integer -> BinaryTree
removeValue EmptyTree _ = EmptyTree
removeValue (Leaf integer) value
                  | value == integer = EmptyTree
                  | otherwise = Leaf integer
removeValue (Node integer left right) value
                  | value == integer = removeValue (insertNode right left) value
                  | value < integer = Node integer (removeValue left value) right
                  | otherwise = Node integer left (removeValue right value)

emptyTree :: BinaryTree
emptyTree = EmptyTree

containsElement :: BinaryTree -> Integer -> Bool
containsElement EmptyTree _ = False
containsElement (Leaf integer) value = value == integer
containsElement (Node integer left right) value
                  | value == integer = True
                  | value < integer = containsElement left value
                  | otherwise = containsElement right value

-- В случае если ни один больший элемент не найден, то возвращает чило на 1 меньше заданного.
nearestGreater :: BinaryTree -> Integer -> Integer
nearestGreater EmptyTree value = value - 1
nearestGreater (Leaf integer) value
                  | integer >= value = integer
                  | otherwise = value - 1
nearestGreater (Node integer left right) value
                  | integer == value = integer
                  | leftGreater == value = leftGreater
                  | rightGreater == value = rightGreater
                  | integerCondition && leftCondition && rightCondition = min integer (min leftGreater rightGreater)
                  | leftCondition && rightCondition = min leftGreater rightGreater
                  | integerCondition && rightCondition = min integer rightGreater
                  | integerCondition && leftCondition = min integer leftGreater
                  | integerCondition = integer
                  | leftCondition = leftGreater
                  | rightCondition = rightGreater
                  | otherwise = value - 1
                  where
                    leftGreater = nearestGreater left value
                    rightGreater = nearestGreater right value
                    integerCondition = integer > value
                    leftCondition = leftGreater > value
                    rightCondition = rightGreater > value

treeFromList :: [Integer] -> BinaryTree
treeFromList [] = EmptyTree
treeFromList list = foldl insertValue EmptyTree list

listFromTree :: BinaryTree -> [Integer]
listFromTree EmptyTree = []
listFromTree (Leaf integer) = [integer]
listFromTree (Node integer left right) = listFromTree left ++ [integer] ++ listFromTree right

main :: IO ()
main = print $ listFromTree $ treeFromList [4, 2, 1, 7, 5, 9, 7, 3, 5, 7 ,7897, 546, 45]
