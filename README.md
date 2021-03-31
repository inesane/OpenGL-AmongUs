## OpenGL installation

```
sudo apt - get update
sudo apt - get install libglu1 - mesa - dev freeglut3 - dev mesa - common - dev
```

# To Run

```
mkdir build
cd build
cmake ..
make
./Hello-World
```

# Game
This is a version of AmongUs created using OpenGL. You are a green coloured character. There is a red coloured character who is the imposter. The imposter uses a shortest path algorithm (Bellman Ford) and moves towards you. There is a button of the same colour as the imposter. If you touch the button, the imposter dies but if the imposter touches you before you touch the button, you lose the game. There is also another button that spawns 2 coins and 2 bombs upon touching the button. If you collect a coin, your score increases by 10. If you touch a bomb, your score decreases by 10. After touching the 2 buttons, one part of the maze breaks open, and you can exit the maze from there and upon exiting the maze you win. There is also a timer, if you have not completed the game before the timer runs out, you lose the game.

# Controls
w - move character up
a - move character left
s - move character down
d - move character right
q - quit the game