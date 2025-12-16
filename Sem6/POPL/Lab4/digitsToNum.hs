digitsToNum :: [Int] -> Int
digitsToNum = foldl (\acc d -> acc * 10 + d) 0