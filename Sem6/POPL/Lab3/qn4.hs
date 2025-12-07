
insertIn :: a -> [a] -> Int -> [a]
insertIn x ys 0 = x : ys
insertIn x [] _ = [x]
insertIn x (y:ys) n = y : insertIn x ys (n - 1)