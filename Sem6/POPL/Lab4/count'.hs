count' :: (a -> Bool) -> [a] -> Int
count' p = foldl (\acc x -> if p x then acc + 1 else acc) 0