
reverseStr :: String -> String
reverseStr [] = []
reverseStr (x:xs) = reverseStr xs ++ [x]
main :: IO ()
main = do
  putStrLn "enter"
  line <- getLine
  putStrLn $ "the reverse is: " ++ show (reverse line)