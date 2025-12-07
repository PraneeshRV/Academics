
repl :: Int -> a -> [a]
repl 0 _ = []
repl n x = x : repl (n-1) x