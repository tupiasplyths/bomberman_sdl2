# Bomberman on SDL2
Only one stage, classic bomberman.
Defeat all enemies to win.
The portal is hidden among the bricks, destroy them to find it.

[Demo Video](https://youtu.be/xZEPqshVdbc)
## Control:
- W, A, S, D: Move
- Space: Place bomb
- Esc: Exit

## Program structure:
- game.cpp: main function
- app.cpp: Handle main game logic and loop, scenes, initialize SDL2 engine
- Animation.cpp: Handle animation
- scenes.cpp Class for scenes, manage and update objects 
- GameScene.cpp: Class for game scene, handle game input, timers, update objects, create level.
- Object.cpp: Base class for all objects
- Sprite.cpp: Storing animations and objects' position, textures
- MovingEntities.cpp: Base class for moving objects, basic movement functions
- Player.cpp: Player class, handle player input, animations
- Enemy.cpp: Enemy class, handle enemy movement, animations

## How to build:
- Open terminal in project folder
- run `cmake .` then `cmake --build . --config Debug --target bomberman`