getNumbers :: Int -> IO [Int]
getNumbers 0 = return []
getNumbers n = do
    putStr "Enter a number: "
    numStr <- getLine
    let num = read numStr :: Int
    rest <- getNumbers (n - 1)
    return (num : rest)

main :: IO ()
main = do
    putStr "How many numbers? "
    input <- getLine
    let n = read input :: Int
    numbers <- getNumbers n
    putStrLn $ "The sum of the numbers is " ++ show (sum numbers)