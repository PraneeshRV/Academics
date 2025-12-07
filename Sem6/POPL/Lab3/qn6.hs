
maxrec :: Ord a => [a] -> a
maxrec [x] = x
maxrec (x:xs) = max x (maxrec xs)
maxrec [] = error "empty list"

