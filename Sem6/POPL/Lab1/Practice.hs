
module Main where

-- This function is used by Qn5
square :: Num a => a -> a
square x = x * x

-- Qn3. Length of a List (Recursive implementation)
listLength :: [a] -> Int
listLength [] = 0         
listLength (_:xs) = 1 + listLength xs 

-- Qn4. Check if List is Empty
isListEmpty :: [a] -> Bool
isListEmpty [] = True      
isListEmpty _  = False     

-- Qn5. Calculate Area of Circle (Uses 'square' from Qn2)
circleArea :: Floating a => a -> a
circleArea r = pi * (square r)

-- Qn6. Factorial using Accumulator (Tail Recursive)
factorial :: Integer -> Integer
factorial n = factHelper n 1
  where
    -- 'acc' is the accumulator
    factHelper 0 acc = acc          
    factHelper n acc = factHelper (n-1) (n * acc) 

-- Qn7. Check if String is Palindrome
isStringPalindrome :: String -> Bool
isStringPalindrome str = str == reverse str

-- Qn8. Reverse a String (using an accumulator)
reverseString :: String -> String
reverseString str = revHelper str ""
  where
    revHelper [] acc = acc
    revHelper (x:xs) acc = revHelper xs (x:acc) 

-- Qn9. 'last' function definition (Way 1: Recursive)
myLast1 :: [a] -> a
myLast1 [] = error "myLast1: empty list" 
myLast1 [x] = x                          
myLast1 (_:xs) = myLast1 xs              

-- Qn9. 'last' function definition (Way 2: Using library functions)
myLast2 :: [a] -> a
myLast2 = head . reverse

-- Qn10. 'init' function definition (Way 1: Recursive)
myInit1 :: [a] -> [a]
myInit1 [] = error "myInit1: empty list" 
myInit1 [_] = []                         
myInit1 (x:xs) = x : myInit1 xs          

-- Qn10. 'init' function definition (Way 2: Using library functions)
myInit2 :: [a] -> [a]
myInit2 [] = error "myInit2: empty list"
myInit2 xs = take (length xs - 1) xs

-- Qn11. Find the second largest element (no sorting)

secondLargest :: Ord a => [a] -> a
secondLargest xs
  | length xs < 2 = error "secondLargest: List must have at least two elements"
  | otherwise     = findSecond (tail xs) (head xs) (head xs)
  where
    findSecond [] m1 m2
      | m1 == m2  = error "secondLargest: No second largest element (all elements are equal)"
      | otherwise = m2
    findSecond (x:xs') m1 m2
      | x > m1    = findSecond xs' x m1     
      | x > m2 && x < m1 = findSecond xs' m1 x 
      | m2 == m1  = findSecond xs' m1 x     
      | otherwise = findSecond xs' m1 m2    

-- Qn12. Check whether a list is a palindrome (generic)
isPalindrome :: Eq a => [a] -> Bool
isPalindrome xs = xs == reverse xs

-- Qn13. This 'main' function practices all the user-defined functions
main :: IO ()
main = do
  putStrLn "--- Haskell Practice Solutions ---"
  
  -- Qn2. Square of a Number
  putStrLn $ "Qn2.  Square of 5: " ++ show (square 5)
  
  -- Qn3. Length of a List
  putStrLn $ "Qn3.  Length of [1,2,3,4]: " ++ show (listLength [1,2,3,4])
  
  -- Qn4. Check if List is Empty
  putStrLn $ "Qn4.  Is [] empty? " ++ show (isListEmpty [])
  putStrLn $ "Qn4.  Is [1] empty? " ++ show (isListEmpty [1])
  
  -- Qn5. Calculate Area of Circle
  putStrLn $ "Qn5.  Area of circle (radius 3.0): " ++ show (circleArea 3.0)
  
  -- Qn6. Factorial using Accumulator
  putStrLn $ "Qn6.  Factorial of 6: " ++ show (factorial 6)
  
  -- Qn7. Check if String is Palindrome
  putStrLn $ "Qn7.  Is 'racecar' a palindrome? " ++ show (isStringPalindrome "racecar")
  putStrLn $ "Qn7.  Is 'hello' a palindrome? " ++ show (isStringPalindrome "hello")
  
  -- Qn8. Reverse a String
  putStrLn $ "Qn8.  Reverse of 'Haskell': " ++ show (reverseString "Haskell")
  
  -- Qn9. 'last' function
  let list9 = [1,2,3,4,5]
  putStrLn $ "Qn9.  myLast1 of [1..5]: " ++ show (myLast1 list9)
  putStrLn $ "Qn9.  myLast2 of [1..5]: " ++ show (myLast2 list9)
  
  -- Qn10. 'init' function
  let list10 = [1,2,3,4,5]
  putStrLn $ "Qn10. myInit1 of [1..5]: " ++ show (myInit1 list10)
  putStrLn $ "Qn10. myInit2 of [1..5]: " ++ show (myInit2 list10)

  -- Qn11. Second Largest Element
  let list11 = [10, 2, 8, 15, 12]
  putStrLn $ "Qn11. Second largest of [10, 2, 8, 15, 12]: " ++ show (secondLargest list11)
  let list11_dups = [5, 8, 2, 8, 3]
  putStrLn $ "Qn11. Second largest of [5, 8, 2, 8, 3]: " ++ show (secondLargest list11_dups)
  
  -- Qn12. Check if List is Palindrome
  let list12a = [1,2,3,2,1]
  let list12b = [1,2,3,4,5]
  putStrLn $ "Qn12. Is [1,2,3,2,1] a palindrome? " ++ show (isPalindrome list12a)
  putStrLn $ "Qn12. Is [1,2,3,4,5] a palindrome? " ++ show (isPalindrome list12b)
