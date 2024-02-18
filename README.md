# makruk_cpp_project
My C++ project of building a command-line-based Makruk (Thai Chess) game with the help of ChatGPT

Day 1 Morning (18-02-2024):

Set Class:
> enum Affiliation


> Piece
>   > Pawn
>   >
>   > Rook
>   >
>   > Bishop
>   >
>   > Knight
>   >
>   > Advisor
>   >
>   > Promoted_Pawn
>   >
>   > King

> Chessboard
> * *initBoard*
> * *getPiece*
> * *printBoard*

Class Chessboard (class containing 2D vector of pointers) has methods initBoard, getPiece, printBoard
For now, I can print the basic chessboard (initialized)
```
R N S K N S N R 
. . . . . . . . 
P P P P P P P P 
. . . . . . . . 
. . . . . . . . 
p p p p p p p p 
. . . . . . . . 
r n s n k s n r 
```

Now I'm going to start writing the ZoC class, which is also vital.