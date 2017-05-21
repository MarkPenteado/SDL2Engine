# SDL2Engine
SDL2Engine in C

# Graphic engine written in C and SDL2, is not yet finished, but contains the following functions:

# Create Window:
- It is possible to change the window background color in RGB, size, position
- It is possible to change title
- It is possible to change icone
- It is possible to use full screen, window mode

# Control FPS:
- It is possible to control the fps rate
- It is possible to use VSYNC

# Load Fonts:
- Load ttf fonts
- change color, position, size

# Control Input:
- control mouse and keyboard input
- control key pressed and released
- control mouse click
- control mouse pressed and released
- show or hide cursor

# Control Sound:
- It is possible to load .mp3 and .wav
- Music is played by .mp3 files, effects by .wav
- It is possible to upload music files
- Perform music and effects
- Pause, Resume and stop Music
- Put Music and effects in loop
- check if the music is playing or stopped
- control volume of songs and effects, increase and decrease volume

# Draw Primitives:
- It is possible to draw points, lines, rectangles, triangles and circles
- It is possible to draw the completed primitives or not
- It is possible to color primitives in RGB

# Control Sprites:
- It is possible to load sprites in PNG format
- Sprites are loaded by files
- PNG with transparency is compatible
- It is possible to draw the complete Sprite
- It is possible to draw parts of a Sprite
- It is possible to resize a Sprite
- It is possible to rotate the Sprite horizontally and / or vertically
- It is possible to rotate the Sprite in angles
- It is possible to draw a rectangle around the Sprite
- It is possible to color the Sprite's RGB rectangle

# Control Timer:
- Timer is used to calculate the frame of the animations
- It is also possible to count the time with the timer in seconds, milliseconds, etc.

# Animate Sprites:
- It is possible to create animations through an existing sprite
- It is possible to add frames in specific coordinates of the Sprite to the animation
- It is possible to execute each frame of the animation
- It is possible to execute all the frames of the animation
- It is possible to use a Timer to control animations
- It is possible to control the animation time

# Control Camera:
- It is possible to use a camera or not
- It is possible to change the global position of the objects of the game according to the camera

# System of collision between Primitives:
- It is possible to check rectangular or circular collisions
- A collision uses primitives

# Map Control System:
- The system works through tiled maps with sprites
- It is possible to upload a map through files
- Empty values ​​must be filled with a ignored value greater than or equal to 0
- It is possible to show all the tiles or just one tile of the map
- The tiles can be resized

# FadeIn / FadeOut System:
- It is possible to execute FadeIn effect in a Sprite or in a set of Sprites
- It is possible to perform FadeOut effect on a Sprite or a set of Sprites
- The eh effect based on the fps rate of the screen
- It is possible to choose a speed for the effect of 0 to 255

# MarkPenteado, 2016~2017, if you use it, keep the credits :D