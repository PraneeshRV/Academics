import Data.List (elemIndex)

selectFirst :: [Int] -> [Int] -> [Int] -> [Int]
selectFirst l1 l2 l3 =
  [ x
  | x <- l1
  , let p2 = findIndexOr (maxBound :: Int) l2 x
  , let p3 = findIndexOr (maxBound :: Int) l3 x
  , p2 < p3
  ]

findIndexOr :: Int -> [Int] -> Int -> Int
findIndexOr def xs x = case elemIndex x xs of
  Just k -> k
  Nothing -> def