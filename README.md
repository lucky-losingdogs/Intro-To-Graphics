# OpenGL Application

This is a program made with OpenGL and Freeglut for a module at University of Staffordshire, written in C++. The objective of the module was to create a product able to load and render models and texture files, along with continuously rotating objects, and being able to interact with the world objects during run-time.

The use of Freeglut allowed a quicker and simpler introduction to OpenGL, allowing me to produce a working system within a short time-span while learning the basics of graphics.

---

## Video

[![Preview of Graphics Program](https://img.youtube.com/vi/8oy4bac4FMY/0.jpg)](https://www.youtube.com/watch?v=8oy4bac4FMY)

---

## Features
- Supports loading and rendering 3D models (obj, txt) and texture files (raw, bmp)
- Fluid camera movement using keyboard and mouse input.
- Interaction with objects via a raycasting and collision detection system for mouse-based selection, alongside an OpenGL-integrated pop-up menu.

---

## Running The Project
To run the project follow these instructions:
1. Clone the repository and open the solution file in your preferred IDE.
2. Build the project.

Controls:
- W/S - Move backward and forward.
- A/D - Move left and right.
- Hold down RMB + move mouse - Rotate camera.
- Normal LMB on object - Interact with object.
- M - Toggle attaching/detaching LMB to pop-up menu.
- LMB after M - Opens pop-up menu to change object textures.

Importing obj models:
- Go to the directory: Graphics-Intro/Graphics-Intro/Obj.
- Drop the obj file into the folder labelled Obj.

Importing txt models/textures:
- Go to the main directory: Graphics-Intro/Graphics-Intro.
- Drop the file into this folder.

---

## Future Improvements
- Accurate FPS UI.
- A tree graph with references to every world object, replacing the currently used linked list.
- A more accessible method for users to upload models and textures. Currently these files need to be placed into appropriate folders for the program to read from, but it would be ideal to be able to upload while the program is running.
- Users spawning and moving objects while the project is running.
   
---

## Credits
Credits for assets and audio used in the preview video can be found in a separate folder named [Credits](Documents/Credits).
