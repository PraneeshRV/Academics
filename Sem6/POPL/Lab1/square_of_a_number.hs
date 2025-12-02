square :: Num a => a -> a
square x = x * x
main :: IO ()
main = do
    let result = square 7
    putStrLn $ "Square of 7: " ++ show result
