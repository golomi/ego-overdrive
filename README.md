# Ego Overdrive
Ego Overdrive is an open source clone of the jump 'n run game Duke Nukum of '91 (aka Duke Nukem).

You will need the original data in order to play the game. All three episodes are supported or will at least be in the future. The game is, however, in an early stage, so a lot of features are currently not working. But it's alread fun to play.

You need at least the first episode, as the game takes all the graphics from there, including the title image and the graphics for the menu.

Good luck :-)


## How to play
So far only Linux is supported

### Install
To Play the game, you need the SDL2 runtime library.

Put the original episodes in <game path>/data/duke<episode no> without any further subdirectory, e.g. Episode 1 in <game path>/data/duke1. Episode 1 is mandatory. Episode 2 and 3 are optional.

Make sure the executable file and the icons for the mouse cursor cursor.png and cursor_clicked.png are in <game path>/data. The mouse does not have any effect in the game. It's only for debugging purposes.

### Operate
To play the game just run ./egooverdrive

In contrast to the original game, there are no individual executable files per episode, but the episode can be selected in the main menu.

As in the original game, the menu is selected via the first letter before the bracket of the menu entry. Apart from “s” and “q”, however, the other menu entries do not yet work.

For example, to start the first episode you have to press “s” and then “1”.

The keyboard layout for controlling Duke is exactly the same as in the original game:
* Cursor left/right to move
* CTRL to jump
* ALT to shoot
* Cursor up to insert key or raise elevator

Additional keys during the game
* Return - switch between full screen and window
* ESC - exits the game
* r - restarts the current world
* n - switches to the next world
* s - quick save
* l - quick load


## How to build
You will need the development libraries for SDL2.

Currently only Linux is supported. Just run Make.

## How to contribute
I am very pleased to get support. As the code itself is very unclean at the moment, smaller functional changes will lead to bigger code changes. So parallel working might result in bigger merging activities. That might keep me from accepting bigger pull requests. The time for cleaning up will come.

Support for Windows and other systems things are very welcome. In this context, support for cmake would probably be useful.



## Roadmap
The following things are planned, which does not necessarily mean, that it will come exaclty the way.

### 0.1
World 1 is completly playable. Other worlds might not be playbale. Even in world 1 are several details which are not yet realized perfectly similar to the original game.

### 0.1.1
Fix several known issues

### 0.2
Teleporter stations are working and maybe some other object.

### 0.3
Objects only move when they come into sight, like in the original game. For some reasons even in the original game, some objects behave differently.
