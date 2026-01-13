data Tree a = Leaf a | Node (Tree a) (Tree a) deriving (Show, Eq)

instance Functor Tree where
    fmap g (Leaf x) = Leaf (g x)
    fmap g (Node l r) = Node (fmap g l) (fmap g r)

-- Verification Functions
checkIdentity :: (Eq (f a), Functor f) => f a -> Bool
checkIdentity x = fmap id x == x

checkComposition :: (Eq (f c), Functor f) => f a -> (b -> c) -> (a -> b) -> Bool
checkComposition x g h = fmap (g . h) x == (fmap g . fmap h) x