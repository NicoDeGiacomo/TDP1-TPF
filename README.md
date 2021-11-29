# Quantum Chess
## Content
* [1. Build](#1-build)
  * [1.1. Install SDL2pp](#11-install-sdl2pp)
  * [1.2. Build Project](#12-build-project)
* [2. How to Play](#2-how-to-play)
  * [2.1. Connect to a Game](#21-connect-to-a-game)
  * [2.2. Play](#22-play)
  * [2.3. Chat](#23-chat)
  * [2.4. Exit](#24-exit)
* [3. Technical Documentation](#3-technical-documentation)
  * [3.1. Chess Logic](#31-chess-logic)
  * [3.2. Server-Client Logic](#32-server-client-logic)
  * [3.3. Tests](#33-tests)

## 1. Build
### 1.1. Install SDL2pp
```shell
sudo apt-get install libsdl2-2.0-0
sudo apt-get install libsdl2-image-2.0-0
sudo apt-get install libsdl2-mixer-2.0-0
sudo apt-get install libsdl2-ttf-2.0-0
sudo apt-get install libsdl-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-mixer-dev
sudo apt-get install libsdl2-ttf-dev
```
```shell
cd /TDP1-TPF/libs/libSDL2pp
cmake . && make && make install
```

### 1.2. Build Project
Download the latest release, extract it, and open a terminal on the main folder.

Use our bash script to build the project. This will also execute the tests automatically.
```shell
$ sh build.sh
$ cd build
$ ./SERVER
$ ./CLIENT localhost 7777
```

Or, if you prefer to do it yourself, you can manually do the following.
```shell
$ rm -r build
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./TESTS
$ ./SERVER
$ ./CLIENT localhost 7777
```

## 2. How to Play
### 2.1. Connect to a Game
While the server is running, launch a client application.
The first client will be assigned to the white pieces, and the second client to the black pieces. The following clients will join as spectators.

### 2.2. Play
There are three types of moves: normal, split and merge.  
To swap between move modes, you can press:
 - `n` For normal mode. Color:![normal](https://via.placeholder.com/15/00ffff/000000?text=+)
 - `s` For split mode. Color:![split](https://via.placeholder.com/15/fa0fb4/000000?text=+)
 - `m` For merge mode. Color:![merge](https://via.placeholder.com/15/008000/000000?text=+)

Normal is the default type.\
You can see which mode you are currently in, by looking at the color of the asterisk placed in the top-left corner of the screen.

#### Normal Move
Click on a piece, the piece will be selected, and then click on the destination.

#### Split Move
Press `s` and click on a piece (the piece will be selected). Then click on two empty squares.

#### Merge Move
Press `m` and click on a piece (the piece will be selected). Now click on a second piece, and finally on the destination of the merge.\
Merges can be made on a new square, or on a square currently occupied by one of the pieces being merged.

#### Entanglement
An entanglement is made with a [normal move](#normal-move). 
Select a classic piece and a destination square, so that the move 'passes through' a piece in a quantum state.

### 2.3. Chat
Click on the side of the board, write a message, and press enter.

### 2.4. Exit
Close the window, press ESC, or with the board selected (click anywhere on the board, to avoid writing in the chat) press `q`.

## 3. Technical Documentation
### 3.1. Chess Logic
![](assets/readme/chess.svg)

### 3.2. Server-Client Logic
![](assets/readme/server-client.svg)

### 3.3. Tests
