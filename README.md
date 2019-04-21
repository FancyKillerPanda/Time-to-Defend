# Time to Defend
Welcome to *Time to Defend*! This is a small tower-defence type game made using C++ and SDL2.
### Features
- Multiple levels of challenging gameplay
- The ability to adjust gameplay settings
- The ability to load and play custom levels
### Current Limits
- Instantiating the editor from the in-game menu is only available on Windows
### Building
To build projects, use MSBuild/Visual Studio to build the VS-solution file. You can also build directly from the source code using a compiler from the command-line. Once built, the DLLs for SDL2 (including SDL_ttf and SDL_image) need to be placed in the output directory.
The `res/` directory should also be in the output directory. This folder contains resources such as maps, textures, fonts, and settings.

### Time to Edit
*Time to Edit* is a level editor built to create maps for *Time to Defend*. 
##### Features
- The ability to place and remove track tiles on the map
- The ability to easily place towers on the map
