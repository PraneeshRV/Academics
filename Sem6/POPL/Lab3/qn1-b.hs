
conc :: [[a]] -> [a]
conc [] = []
conc (x:xs) = x ++ conc xs