fsmap :: a -> [a -> a] -> a
fsmap x fs = foldl (\acc f -> f acc) x fs

