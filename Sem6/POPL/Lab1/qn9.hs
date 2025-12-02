
cLast :: [a] -> a
cLast [x] = x
cLast (_:xs) = cLast xs
cLast2 :: [a] -> a
cLast2 xs = head (reverse xs)
main :: IO ()
main = do
    putStrLn"enter"
    inp <- getLine
    let cLast0 = read inp :: [Int]
    putStrLn $ "answer: " ++ show (cLast cLast0)