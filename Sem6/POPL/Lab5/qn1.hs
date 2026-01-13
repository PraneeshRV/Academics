newtype ST s a = S (s -> (a, s))

app :: ST s a -> s -> (a, s)
app (S f) = f

instance Functor (ST s) where
    fmap g st = do
        x <- st
        return (g x)

instance Applicative (ST s) where
    pure x = S (\s -> (x, s))
    stf <*> stx = do
        f <- stf
        x <- stx
        return (f x)

instance Monad (ST s) where
    return = pure
    st >>= f = S (\s ->
        let (x, s') = app st s
        in app (f x) s')