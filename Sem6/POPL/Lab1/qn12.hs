isPalindromeRev :: Eq a => [a] -> Bool
isPalindromeRev xs = xs == reverse xs

isPalindromeRec :: Eq a => [a] -> Bool
isPalindromeRec [] = True
isPalindromeRec [_] = True
isPalindromeRec (x:xs) = x == last xs && isPalindromeRec (init xs)

main :: IO ()
main = do
    print (isPalindromeRev [1,2,10])
    print (isPalindromeRev [1,2,1])
    print (isPalindromeRec [10,90,56,7])