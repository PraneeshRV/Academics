
average :: [Int] -> Float
average [] = 0
average xs = fromIntegral (sum xs) / fromIntegral (length xs)