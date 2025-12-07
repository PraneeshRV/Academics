
andrec :: [Bool] -> Bool
andrec []      = True
andrec (x:xs) = x && and xs

