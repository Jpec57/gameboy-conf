# gameboy-conf

This is a small project to show how does the gameboy development works to my team.

## Install 

https://www.gbdkjs.com/docs/installation/

## Presentation 

### Inspiration

Really complete blog where you can find a much more detailed explanation over key-concepts in GameBoy Programming: 
https://blog.flozz.fr/2018/10/01/developpement-gameboy-1-hello-world/

### Introduction
Some key-numbers to begin with: 

- released in 1990
- 8 ko of RAM,
- 8 ko of video memory,
- only 4 greyscales with a resolution of 160×144 pixels.

A game usually has between 32 ko and 4 Mo of ROM.

### GamePad : GBK Functions

- UINT8 waitpad(UINT8 mask): blocking execution to wait for key corresponding to the mask to be clicked.
- void waitpadup(void): blocking execusion to wait for user to release all gamepad buttons. It's particulary convenient when the user as to click 
- joypad: 

And a mask for each button: 
- J_UP,
- J_DOWN,
- J_LEFT,
- J_RIGHT,
- J_A,
- J_B,
- J_START,
- J_SELECT

Be aware that you will code on a 8-bit machine. For that reason an integer should only be 8-bit long. To do so, some recommended types are available like INT8 and UINT8. 