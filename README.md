# Simon-Says-

This project aims to design an Arduino-based two-player memory and reaction 
game that supports both single-player and 2-player modes. Games that challenge 
memory and response time are engaging and educational. They improve focus, 
cognitive flexibility, and decision-making skills through repeated mental stimulation 
and pattern recognition. Arduino is well-suited for building such interactive systems. It 
offers simple hardware-software integration, real-time input handling, and flexible 
control logic. In this game, Arduino generates random LED sequences, reads player 
inputs through buttons, and provides instant feedback using LEDs, sound, and an LCD 
screen. It tracks scores, manages turns, and increases difficulty as players advance 
through six levels. This project highlights how embedded systems like Arduino can be 
used beyond traditional applications to build interactive learning tools. The game 
features six levels and supports both single-player and two-player modes. Each mode 
challenges the user with LED-based sequences that test memory, speed, and 
coordination. Players interact through four color-coded buttons and receive real-time 
feedback on an LCD screen. Scoring systems vary by mode, rewarding accuracy, speed, 
and progression through increasingly difficult patterns. 
 
                                                         Proposed Game Modes 
The game includes 6 levels. It supports both single-player and 2-player modes. The 
hardware includes: 
• 4 color-coded LEDs to display light sequences 
• 4 color-coded buttons for each player 
• LCD screen for user feedback 

                                                        Single-Player Mode 
Normal Point Scoring System:  
Scoring system for all game modes (single-player). If the user answers correctly 
(depending on the game mode criteria), he/she will receive 1 point. If they answer 
incorrectly, he/she will receive 0 points. Depends on points won, the player receives 
one of 3 medals: gold, silver or bronze. 

1. Fastest Reaction 
• (5) LEDs light up randomly during the (6) rounds 
• The user must answer correctly and within the time limit to proceed 
• As you go up in levels, the time gets tighter, but the same number of lights 
show up each round 
Scoring System 
• Player earns 5 points for entering the full sequence correctly 
• Player gets -1 point for each incorrect input 
• Player continues to the next round regardless of errors 
• If the player enters the full sequence correctly and faster than the 50%-time 
limit, he/she will receive 1 bonus point.

3. Coordination test 
• LEDs flash in sequence (2, 3, 4, 5, 6, 7)  
• The player is required to replicate the full sequence for all 6 rounds. Each 
round/level comes with a completely new sequence of LEDs that will light up 
simultaneously 
Scoring System  
• Each round, there is a timer; if the player does not answer fast enough, he/she 
will get 0 points but proceed. 
• This mode will follow the normal point-scoring system 
• Time for each round increase (as there is a higher number of LEDs) 
• If the player responds faster than the time limit, he/she will receive 1 bonus 
point. 
                                        2-Player Mode 
1. Fastest Reaction 
• Both players respond to the same LED sequence 
• (5) LEDs light up randomly during the (6) rounds 
• The users must answer correctly and within the time limit to proceed 
• As you go up in levels, the time gets tighter, but the same number of lights 
show up each round 
Scoring System 
• To receive 5 points, the player must answer the full sequence correctly 
• Player gets -1 point for each incorrect input 
• The first full correct response gets a 1-point bonus  
•  Players continue to the next round regardless of errors 
Example: Red, Green, Blue, Yellow, Red  
1) Red, Green, Blue, Yellow, Red (1.5 sec) → Points received: 6 pts 
2) Red, Green, Blue, Yellow, Red (2 sec) → Points received: 5 pts 
3) Red, Green, Blue, Blue, Blue (1.5 sec) → Points received: 3 pts 

2. Coordination test 
• LEDs flash in sequence (2, 3, 4, 5, 6, 7)  
• The players are required to replicate the full sequence for all 6 rounds. Each 
round/level comes with a completely new sequence of LEDs that will light up 
simultaneously 
• Time for each round increases (as there is a higher number of LEDs) 
• Time slots for each round will not be the main challenge of the mode (even at 
the highest difficulty)  
Scoring System:  
• 1 point if the full sequence is correct. 
• 0 points for even one mistake 
• 1 bonus point for whoever answers correctly first  
• Each round there is a timer. If both players don’t answer fast enough, they 
both get zero points and both proceed.  
• If one player doesn’t answer fast enough, he/she will receive zero points for 
that round and then both players will also proceed
