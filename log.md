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

19-02-2024

Let's analyse the logic of updating ZoCs.

For the sake of convenience, let's suppose (i,j) means ith row, jth column. Such a coordinate system is precisely the inverse of the Catersian we use in real life but is quite common in matrices.

Pawns: A Pawn located at (i,j) has a ZoC of (i+1,j+1) and (i+1,j-1) if the pawn belongs to white, (i-1,j+1) and (i-1,j-1) if it belongs to black.
Pawns are also unique due to their movement rules being separated from their Zone of Control. This might be troublesome. We'll probably treat Pawns separately when dealing with movements.

Advisors/Promoted Pawns: They follow a more straightforward rule. An Advisor or a Promoted Pawn located at (i,j) controls its four diagonal neighbours (i+1,j+1), (i+1,j-1), (i-1,j+1) and (i-1,j-1).
I'm treating Advisors and Promoted Pawns as different objects because I plan to introduce the "Sut Met" special movement rule.

Bishops: In Makruk, Bishops control the Advisor's ZoC plus the square in front of it. 
A Bishop located at (i,j) has a basic ZoC of its four diagonal neighbours (i+1,j+1), (i+1,j-1), (i-1,j+1) and (i-1,j-1). Additionally, white Bishops controls (i+1,j) while black controls (i-1,j)

Knights: Knights are the same as chess. A Knight located at (i,j) controls (i+1,j+2), (i+1,j-2), (i+2, j+1), (i+2, j-1), (i-1, j+2), (i-1, j-2), (i-2, j+1), (i-2, j-1)

Rooks: Rooks are pretty different from any other pieces.
A Rook at (i,j) follows such rules.
(1) (i+1,j), (i-1,j), (i,j+1), (i,j-1) are in its ZoC.
(2) Continue in four directions until the square is not empty: (i+k,j) or (i,j+k) is in its ZoC.

Kings: 
Kings control those within their eight neighbours that the opponent hasn't controlled.

21-02-2024:

Updated ZoC system.

This is quite complicated...

In the last update, I forgot to consider situation for Both sides to control the squares. Now I've updated the enum Affiliation to resolve that.

22-02-2024

Now, our ZoC system looks pretty complete. But there are two more things: pins and checks.

First, let's look at pins.

If a piece gets pinned (which, in Makruk, only Rooks can do), its ZoC is the intersection of the pinning piece and its original ZoC.

Let's have some examples.

Case 1: Black Rook on a2. White King on f2. White Pawn on e2. In this case, the Pawn could not move, nor could it control f3 or d3.

Case 2: Replace the white Pawn with a Rook. In this case, the Rook could either stay where it has been or capture the black Rook on a2.

Checks occur when the King is in the opponent's ZoC after a move by the opponent. It also changes the ZoC in a more complicated way. When being checked, the ZoC reduces to the union of these three scenarios:
(1) The King breaks out from the check.
(2) Some piece takes out the checker.
(3) Some piece blocks the check.
For case (3), we have: This piece is a pawn, or this piece is not a pawn.
In Makruk, only the Rook check could be blocked; this simplifies the case.
We'll first look at non-pawn cases.

23-02-2024

While I was carrying out these steps, I found something serious. It might have been better if I had used 2-D vectors of vectors of pointers as ZoC rather than 2-D vectors of enum Affiliation. Yet, I came up with something that might work. First, update the ZoC, then remove all squares that both a King and the opponent have controlled. Finally, update the ZoC without King.
I'll try it later.