# OpenGL Application

This is a program made with OpenGL and Freeglut for a module at University of Staffordshire, written in C++.

The use of Freeglut allowed a quicker and simpler introduction to OpenGl, allowing me to produce a working system within a short time-span while learning the basics of graphics.

---

## Video

[![Preview of Graphics Program](https://img.youtube.com/vi/Qprxd3IJZQ4DARl5/0.jpg)](https://www.youtube.com/watch?v=Qprxd3IJZQ4DARl5)

---

## Features
- A ticket system where pre-made tickets are placed in a list, which is extended and shuffled so tickets can continually be completed through the length of a level.
- Ingredients are moved around by placing tiles on a tile map at the position of the ingredient.
- The cells/tiles of ingredients that are dragged over another ingredient are replaced by 'ghost' tiles, which indicate to the player that there are overlapping tiles at that position. If the overlapping ingredient is dropped onto another ingredient, a search algorithm is used to determine the closest empty position that the ingredient can be placed within the grid.
- A tile map made in Unity's UI canvas using images in a grid. To check if a ticket has been completed in the actual tile map that the player places ingredients on, there is a conversion between the UI tile map and the actual tile map.
- A save system that auto-saves after completing a level and determines the levels available to choose from in the level select.

---

## Future Improvements
- More play-testing is required in order to to tweak the duration of certain mechanics, for example the combo decrease speed and the ticket spawn speed.
- The prototype currently lacks sound effects and more interesting visuals.
- An options menu.

---

## Running The Project
I have a build of the project published on [itch.io](https://lucky-losingdogs.itch.io/burger-builder), which you can play in browser, or download and run from the .exe file.

For downloading the Unity project from this repository please follow these instructions:
1. Clone the repository and open it from Unity Hub with the latest Unity version.
2. Open the Start Menu scene.
3. Press play to run the project in the play view.
   
---

## Credits
Credits for assets and audio used in the preview video can be found in a separate folder named [CREDITS](Documents/Credits).

---

## Other Documentation
Some of the design plans for the prototype were created using Miro, and can be viewed in the folder named [Miro](Documents/Miro).
