thirdHeadTail :: [a] -> a
thirdHeadTail xs = head (tail (tail xs))

thirdIndex :: [a] -> a
thirdIndex xs = xs !! 2

thirdPattern :: [a] -> a
thirdPattern (_:_:x:_) = x

third :: [a] -> a
third = thirdPattern

main :: IO ()
main = do
  putStrLn "thirdHeadTail [1,2,3,4] =>"
  print (thirdHeadTail [1,2,3,4])
  putStrLn "thirdIndex [\"a\",\"b\",\"c\",\"d\"] =>"
  print (thirdIndex ["a","b","c","d"])
  putStrLn "thirdPattern \"abcde\" =>"
  print (thirdPattern "abcde")
  putStrLn "third [10,20,30,40] =>"
  print (third [10,20,30,40])