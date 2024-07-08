# AmongUs Game with OpenGL

This is a version of AmongUs created using OpenGL.

## OpenGL installation

```bash
sudo apt - get update
sudo apt - get install libglu1 - mesa - dev freeglut3 - dev mesa - common - dev
```

## To Run

```
mkdir build
cd build
cmake ..
make
./Hello-World
```

## Gameplay

### Objective
- You play as the green-colored character. Avoid the red-colored imposter, reach and touch the imposter-colored button to eliminate the imposter, and navigate through the maze to exit.

### Imposter Behavior
- The imposter uses the Bellman-Ford shortest path algorithm to move towards you.

### Buttons
- **Imposter Button**: If you touch the imposter-colored button, the imposter dies. If the imposter touches you before you touch the button, you lose the game.
- **Spawn Button**: Touching this button spawns 2 coins and 2 bombs.

### Scoring
- **Collect a Coin**: +10 points
- **Touch a Bomb**: -10 points

### Maze and Timer
- After touching the two buttons, a part of the maze breaks open, providing an exit.
- **Exit the Maze**: Upon exiting, you win the game.
- **Timer**: Complete the game before the timer runs out to avoid losing.

## Controls
- **W**: Move character up
- **A**: Move character left
- **S**: Move character down
- **D**: Move character right
- **Q**: Quit the game
