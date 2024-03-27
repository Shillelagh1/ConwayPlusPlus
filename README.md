# Building
The program can be built with the included build file. This build file is intended for linux. The program is untested on other systems. After succesfully building the executable will be stored at a.out. SDL2 must be available to build the program.

# Execution
The executable only accepts one argument. This is the name of the binary playspace file to load on startup. Example:
> ./a.out Flyer.bin
# Controls
## Editing
To edit the play area, click on the window with the mouse cursor. The state of the cell at the mouse cursor will be toggled.
## Start/Stop
Press SPACE to start and stop the simulation.
## Saving
Press TAB to save the playspace configuration to a file. Pressing TAB will begin a prompt in the parent console requesting a filename. This is the relative filename the playspace configuration will be saved to.
## Time Scale
Press UP and DOWN arrows to adjust the simulation timescale.
