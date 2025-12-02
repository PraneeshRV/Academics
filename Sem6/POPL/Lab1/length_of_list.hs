
len :: [a] -> Int
len [] = 0
len (_:xs) = 1 + len xs

main :: IO ()
main = do
    putStrLn "enter the list([1,2,3,4]):"
    input <- getLine           
    let list = read input :: [Int]   
    putStrLn $ "len of the list is: " ++ show (len list)
