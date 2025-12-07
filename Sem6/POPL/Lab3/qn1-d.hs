
import Prelude hiding ((!!))

(!!) :: [a] -> Int -> a
(x:_) !! 0 = x
(_:xs) !! n = xs !! (n-1)
[] !! _ = error "Index out of bounds"