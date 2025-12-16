removeDup :: (Eq a) => [a] -> [a]
removeDup xs = reverse $ foldl (\acc x -> if x `elem` acc then acc else x : acc) [] xs