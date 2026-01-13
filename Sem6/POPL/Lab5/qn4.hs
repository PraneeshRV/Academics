sqroot :: Double -> Double
sqroot n = snd . head . dropWhile condition $ zip approxs (tail approxs)
  where
    approxs = iterate (\a -> (a + n/a) / 2) 1.0
    condition (x, y) = abs (x - y) >= 0.00001