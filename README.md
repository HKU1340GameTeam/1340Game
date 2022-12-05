# 1340Game
Team members: Zhang Shengce 
              Liu Jinheng 3035951959
              Fan Zimeng 3035952745

 ______   ______   ___   __    ___   _________   ______   ________   __       __          
/_____/\ /_____/\ /__/\ /__/\ /__/\ /________/\ /_____/\ /_______/\ /_/\     /_/\         
\:::_ \ \\:::_ \ \\::\_\\  \ \\::\ \\__.::.__\/ \::::_\/_\::: _  \ \\:\ \    \:\ \        
 \:\ \ \ \\:\ \ \ \\:. `-\  \ \\:_\/   \::\ \    \:\/___/\\::(_)  \ \\:\ \    \:\ \       
  \:\ \ \ \\:\ \ \ \\:. _    \ \        \::\ \    \:::._\/ \:: __  \ \\:\ \____\:\ \____  
   \:\/.:| |\:\_\ \ \\. \`-\  \ \        \::\ \    \:\ \    \:.\ \  \ \\:\/___/\\:\/___/\ 
    \____/_/ \_____\/ \__\/ \__\/         \__\/     \_\/     \__\/\__\/ \_____\/ \_____\/ 
                                                                                          
The objective of the game is simple, make it through the parkour map while dodging obstacles with limited health. Most importantly, DON'T FALL! There will be some pits that you do not want to fall in...

*When entering the game with ./main, you need to go down and enter the portal to offcially begin the parkour map. Or press 0 and load your saved game.

*TO DISPLAY/RUN THE GAME PROPERLY, PLEASE ADJUST THE CONSOLE FONT SIZE! (The initial font size of the console may be too large to display the game properly, so please zoom out).

*DISCLAIMER: If you made it to the end and see "coming soon", which means you have completed the game! [Because thats all the levels we've made so far :) ].

Controls:
l(L) for moving left, '(") for moveing right, 3 for jumping, space for dashing,
t to teleport through portal, r for conversation/interaction,
o for constant left move, [ for constant right move.
0(zero) to enter pause menu where you can 'RESUME', 'SAVE', 'LOAD', or 'EXIT', j for arrow down, k for arrow up and ENTER to select.

*You can customize your own keyboard control in Player/KeyboardInput.txt
*You can customize animation speed in Player/Animator.txt

1: Random selection of text messages when the player dies.
2: Press 0 to enter pause menu, if 'SAVE' is selected, it will store current player scene, positon and HP into an ofstream fout.
3: We utilized vector for dynamic memory management.
4: 'SAVE' will save the current game into a file inputted by the user and is stored in an ofstream fout. 'LOAD' will read a saved file inputted by the user and read from ifstream fin.
5: Each feature of the game is scripted in a different file, e.g. Player is scripted in Player.cpp, the pause menu is scripted in UI.cpp...

Compilation and execution:
Just simply type 'make', then './main' to run the game!

Thats all, enjoy!
