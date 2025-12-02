cInit :: [a] -> [a]
cInit [_] = []
cInit (x:xs) = x : cInit xs
cInit2 :: [a] -> [a]
cInit2 xs = reverse (tail (reverse xs))
main :: IO ()
main = do
    putStrLn"enter"
    inp <- getLine
    let cLast0 = read inp :: [Int]
    putStrLn $ "answer: " ++ show (cInit cLast0)