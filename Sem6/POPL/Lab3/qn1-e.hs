
elerec :: Eq a => a -> [a] -> Bool
elerec _ [] = False
elerec y (x:xs)
    | y == x    = True
    | otherwise = elerec y xs