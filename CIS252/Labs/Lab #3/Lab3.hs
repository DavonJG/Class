import Pictures

twoPicColumn :: Int->Picture->Picture->Picture
twoPicColumn n pic1 pic2
             | n<1 = error "twoPicColumn requires an input above 1"
             | n==1 = above pic1 pic2
             | n>1 = above pic1 (twoPicColumn (n-1) (pic2) (pic1))

descend:: Int -> Picture -> Picture
descend n pic
        | n==1 = pic
        | n<1 = error "descend requires an input above 1"
        | n>1 = above (row(n) pic)(descend(n-1)(invertColour(pic))