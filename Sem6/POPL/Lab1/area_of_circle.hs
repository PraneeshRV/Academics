main :: IO ()
main = do
  putStrLn "radius:"
  r <- readLn :: IO Double
  print (pi * r * r)