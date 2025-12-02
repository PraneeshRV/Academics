main :: IO ()
main = do
  putStrLn "enter list:"
  xs <- readLn :: IO [Int]
  print (null xs)