
secondLargest :: Ord a => [a] -> a
secondLargest (x:y:xs) = findSecond xs (max x y) (min x y)
    where
        findSecond [] max1 max2 = max2
        findSecond (z:zs) max1 max2
            | z > max1              = findSecond zs z max1
            | z > max2 && z < max1  = findSecond zs max1 z
            | otherwise             = findSecond zs max1 max2

main :: IO ()
main = do
    print (secondLargest [75,24,66,10,10,89])