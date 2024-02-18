This log contains some of the notes/prompts.

18-02-2024
Here's what I told ChatGPT so that it better understand what I'm doing.

Scope: I am developing a Makruk (Chess variant) game project.
Target Audience: this is a toy project, so there's no explicit target audience.
Technology Stack: C++
User Interface: Command-line interface. Future plans: Graphic UI
System Architecture: Only one main program consisting of a Chessboard class, a ZoC class, a logic system and Pieces objects
Data Storage: The Chessboard class and ZoC class will be stored in a 2-D vector, and Pieces will be stored as objects. All in heap memory. Consider adding S/L features and saving the game as txt files.
Development Milestones: (1) Setup "Chessboard" and "ZoC", (2) Finish basic rules, (3) Adding counting rules, (4) Adding S/L features, (5) Adding GUI.
Testing and Debugging: For each step in the development milestone
Documentation: Inline comments for major functions and a help command when running the game.

At first, I considered using 2-D arrays of chars to represent the chessboard, each char corresponding to an Object of the chess piece. But then I thought, why not use pointers as I am writing in C++? 
So, I started thinking about memory allocation problems and pointers. What if I only initialize one Rook object and use two pointers on a chess board, both pointing at the Rook object, to represent two distinct rooks? If one got captured, just replace the pointer at that location of the chess board with `nullptr`! That would save memory! 

Well, maybe that's not a good idea. GPT says pieces should have easy access to their own position, and my "One object, two pointers." could be chaotic when being captured.

But I'll try to implement my good idea, for the time being :)

In this game, I use the ZoC(Zone of Control) to represent squares on the board that their pieces could directly reach within one move, namely, controlled by the pieces. This could be useful in many ways. Kings could not move to the opponent's ZoC. 

If the King is in the opponent's ZoC, we call it a check. 

Moreover, if the checker is not in the ZoC of the defender, and the defender's King has no ZoC, this is a mate. 

This is a draw if the defender's King is not in the attacker's ZoC, and the defender has no ZoC.

ZoC is a 2-D vector of enum, with three values: {SideA, SideB, None}. 

However, this basic logic of ZoC does not handle pins and forks well. But if we update the ZoC after the basic ZoC is calculated, it might be better.

In Makruk, only Rooks causes pins. So pin detection is quite simple: detect if rooks are one piece away on the lines where the King sits. The squares between the Rook and the King are defined as pin_area.

Pinned pieces have reduced ZoCs: either they could directly capture the pinning Rook (meaning, the attacking Rook is in the ZoC of the pinned piece), or their movement does not expose the King under attack. (The new step is still in the pin_area)
To sum up, the process of one step is:

User Input -> Pre-move Validation -> Execute -> Update Chessboard -> Reset ZoC -> Post-move Updates (Check for checks, pins) -> Update ZoC

Coding in C++ is more difficult than I thought, really. In a way, I'm not that familiar with OOP, and I'm only a first-year DS student. This project might be a small step for me, but it's a huge leap for me. I don't know what I'm talking about. OK, back to work.

The Enum data type is really interesting. I've never seen such a thing before. Honestly, it's useful. But remember, don't try to print this thing directly. I should first build a function that maps Enum values to strings.

Some syntactic sugar:
`for (const auto &item : vector)`
This is like `for i in some_list:` in Python.

`return (piecestate == Affiliation::Player1) ? 'P' : 'p'`
This means if the condition is met, return 'P'; otherwise, return 'p'