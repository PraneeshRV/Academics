isPrime :: Int -> Bool
isPrime 0 = False -- Base Case
isPrime 1 = False -- Base Case

isPrime x = not (hasDivisor(x-1))
    where
        hasDivisor :: Int -> Bool
        hasDivisor 1 = False
        hasDivisor n = mod x n == 0 || hasDivisor(n-1)
