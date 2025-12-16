joinWithSpace :: [String] -> String
joinWithSpace = foldr (\s acc -> if null acc then s else s ++ " " ++ acc) ""