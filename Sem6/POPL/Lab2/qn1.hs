halve :: [a] -> ([a],[a])
halve b = splitAt (length b `div` 2) b
main :: IO ()
main = do
  print (halve [1..10])
