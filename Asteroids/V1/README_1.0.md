# C-Asteroids

## Version 1.0

### Overview

An implementation of a customized version of the Atari game “Asteroids” that will run under Linux. 

The main functionality for Version 1.0 is run a single asteroid motion simulator multiple times with different test data.  

The position and velocity data along with the size of the asteroid and the number of steps the simulation will run will be read from stdin.  

The execution will sleep for 1 second as part of every simulation step when the code is doing graphical output.

All position and velocity data is to be stored in double precision floating point and the size of the asteroid and the number of steps are integers.  

Every step, the new position and velocity data may be printed to stdout, but will be printed to stderr once graphics are integrated.  

Eventually position data will be fed to the graphics library as well for better visualization.  

In the game, the world “wraps” so an asteroid that wanders off the bottom of the screen reappears at the top of the screen.  Likewise for the left and right edges. 

