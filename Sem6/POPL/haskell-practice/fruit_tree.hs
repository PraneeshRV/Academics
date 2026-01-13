-- STEP 1: DEFINE THE TREE (You are missing this line!)
data Tree a = Leaf a | Node (Tree a) (Tree a)

-- STEP 2: DEFINE THE FUNCTION
sumTree :: Tree Int -> Int
sumTree (Leaf x) = x
sumTree (Node left right) = sumTree left + sumTree right
