main :: IO ()
main = do
  let factorial n = product [1..n]
  print (factorial 7)