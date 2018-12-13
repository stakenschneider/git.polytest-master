module Main where

data UnaryOperator = UnaryPlus | UnaryMinus deriving (Show, Eq)

data BinaryOperator = BinaryPlus | BinaryMinus | BinaryMult deriving (Show, Eq)

data Term = IntConstant { _constant :: Int }
            | Variable { _variable :: String }
            | UnaryTerm { _central :: Term, _uoperator :: UnaryOperator }
            | BinaryTerm { _left :: Term, _right :: Term, _boperator :: BinaryOperator } deriving (Show, Eq)

infixl 6 @+
(@+) :: Term -> Term -> Term
IntConstant first @+ IntConstant second = IntConstant (first + second)
first @+ second = BinaryTerm first second BinaryPlus

infixl 6 @-
(@-) :: Term -> Term -> Term
IntConstant first @- IntConstant second = IntConstant (first - second)
first @- second = BinaryTerm first second BinaryMinus

infixl 7 @*
(@*) :: Term -> Term -> Term
IntConstant first @* IntConstant second = IntConstant (first * second)
first @* second = BinaryTerm first second BinaryMult

(@++) :: Term -> Term
(@++) (IntConstant argument) = IntConstant argument
(@++) argument = UnaryTerm argument UnaryPlus

(@--) :: Term -> Term
(@--) (IntConstant argument) = IntConstant (-argument)
(@--) argument = UnaryTerm argument UnaryMinus

replaceVariable :: Term -> String -> Term -> Term
replaceVariable (IntConstant constant) _ _ = IntConstant constant
replaceVariable (Variable variable) rvariable rterm = if variable == rvariable then rterm else Variable variable
replaceVariable (UnaryTerm central uoperator) rvariable rterm = UnaryTerm (replaceVariable central rvariable rterm) uoperator
replaceVariable (BinaryTerm left right boperator) rvariable rterm = BinaryTerm (replaceVariable left rvariable rterm) (replaceVariable right rvariable rterm) boperator

main :: IO ()
main = print $ IntConstant 2 @* IntConstant 3 @+ (@--) (IntConstant 9)
