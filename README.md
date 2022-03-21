# About the Project
Cosmic Capture was completed as the term project for the games programming course at University of Calgary, CPSC 585, in a team of four; to see the other contributors, trace back the fork or click on this link: https://github.com/cpsc585team2/CosmicCapture?organization=cpsc585team2&organization=cpsc585team2

The game is built using C++, OpenGL for graphics, and NVIDIA PHYSX for driving simulation. We also use a few other C/C++ libraries, including SDL2 for input and window management, OpenAL for audio, assimp for loading 3D files, and glm for math.

## Cosmic Capture Demo
Me badly playing Cosmic Capture by myself against the three AI. The below image is linked to a youtube video:
[![Watch the video](https://img.youtube.com/vi/SXtFcH4nQ_c/maxresdefault.jpg)](https://youtu.be/SXtFcH4nQ_c)

The project is setup such that with controllers four people can play locally on the same computer as well

# How to play

## Requirements:  The game runs on windows computers, and runs best if the computer has a dedicated graphics card. Note that the Microsoft Visual C++ for visual studio 2015, 2017, and 2019 is required in order to run the game, and can be obtained from here: Visual C++ Download.

## Gameplay

As in classic capture the flag, grab the flag and return it to your corner of the arena. When you aren't in posession of the flag, the compass at the top of the creen will be pointing you towards it, and if you are in possession of the flag that compass will point you to home base (so no getting lost!). While bumping into someone just slows you down if neither have the flag, when someone is in possession of the flag you can both make them drop the flag and eject them back to their home base by driving into them. If a player or AI gets the flag to homebase everyone is teleported back to their starting positions and the flag back to the arena centre. 

Power-ups:
1) Boost - a classic speed boost- quite powerful, so use wisely (something I fail to do in the above video)
2) Projectile - ejects the target back to their home base if hit
3) Spike traps- will stun any car that runs into them for a moment, preventing them from moving

Gate-switches: there are gates throughout the arena, half of which are active at any given time. The unique strategy of this particular capture the flag game is to get in rhythm with the gates so that your path can take you to and from the flag witout having to take an unaccounted for detour.

## Controls: 

We have implemented both keyboard controls (WASD) as well as controller controls (AB, Left joystick), you can accelerate forward, turn left and right, as well as brake and reverse. 

After you pick up a power-up press (SPACEBAR) on keyboard, (X) on controller to use power-up.
If you get stuck or get sent flying you can respawn your car, to respawn press (R) on keyboard, (Y) on controller.

When the game loads you will be greeted with a title screen, press (ENTER) on keyboard, press (BACK) on controller to get to the character select screen.
** Note: sometimes the game can take a while to load, so give it a bit of time

Press (SPACE) on keyboard or (X) on controller to determine which position you would like and once all the players are in, each player must confirm they are ready by pressing either (SPACE) or (X) again. Once all players have confirmed they are ready the game will start.

When the game ends, press (ENTER) on keyboard, (BACK) on controller to restart the game.
