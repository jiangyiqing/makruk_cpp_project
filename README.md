# makruk_cpp_project
My C++ project of building a command-line-based Makruk (Thai Chess) game with the help of ChatGPT


Scope: I am developing a Makruk (Chess variant) game project.
Target Audience: this is a toy project, so there's no explicit target audience.
Technology Stack: C++
User Interface: Command-line interface. Future plans: Graphic UI
System Architecture: Only one main program consisting of a Chessboard class, a ZoC class, a logic system and Pieces objects
Data Storage: The Chessboard class and ZoC class will be stored in a 2-D vector, and Pieces will be stored as objects. All in heap memory. Consider adding S/L features and saving the game as txt files.
Development Milestones: (1) Setup "Chessboard" and "ZoC", (2) Finish basic rules, (3) Adding counting rules, (4) Adding S/L features, (5) Adding GUI.
Testing and Debugging: For each step in the development milestone
Documentation: Inline comments for major functions and a help command when running the game.

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