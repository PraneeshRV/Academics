isPalindromeStr :: String -> Bool
isPalindromeStr s = s == reverse s
main :: IO ()
main = do
  putStrLn "enter"
  line <- getLine
  putStrLn $ "the string is a palindrome: " ++ show (isPalindromeStr line)