## Quantum Chess

Quantum Chess is a variant of the chess game, which uses properties of quantum physics. It uses all of the same pieces, in the same starting positions, as classical chess.\
Quantum Chess allows (almost) all pieces to exist in superposition, where they can occupy more than one square at a time. This is shown by a bar indicating the probability that the piece will be found in a given square by a measurement.

### Content

* [1. Installation guide](#1-installation-guide)
* [2. How to Play](#2-how-to-play)
  * [2.1. Connect to a Game](#21-connect-to-a-game)
  * [2.2. Play](#22-play)
  * [2.3. Notation](#23-notation)
* [3. Settings](#3-settings)

### 1. Installation Guide
Download the [latest release](https://github.com/NicoDeGiacomo/TDP1-TPF/releases/latest), extract it, and open a terminal on the main folder.\
Run the installer.
```shell
$ sh install.sh
$ cd build
$ ./CLIENT [SERVER_IP] 7777
```

### 2. How to Play
#### 2.1. Connect to a Game
The first thing you will see upon opening the game is a screen asking for your username.

![Screenshot from 2021-12-13 02-01-55](https://user-images.githubusercontent.com/11294851/145755249-16cacc16-deec-40d2-8c8c-ae54d50c0a3b.png)

The next thing you want to do is to connect to a room, and you can do that by typing the ID of the room in the login screen and selecting how you want to join.\
You can choose between using the white pieces, the black pieces, or being a spectator. If there are no rooms with the typed ID, one will be created for you.

![Screenshot from 2021-12-13 02-02-59](https://user-images.githubusercontent.com/11294851/145755278-3169a71c-f54e-48f8-be4d-fca5501c3419.png)

#### 2.2. Play
There are three types of moves: normal, split and merge.  
To swap between move modes, you can press:
 - `n` For normal mode (color: ![normal](https://via.placeholder.com/15/00ffff/000000?text=+)).
 - `s` For split mode (color: ![split](https://via.placeholder.com/15/fa0fb4/000000?text=+)).
 - `m` For merge mode (color ![merge](https://via.placeholder.com/15/008000/000000?text=+)).

Normal is the default type.\
You can see which mode you are currently in, by looking at the color of the asterisk placed in the top-right corner of the screen.

##### Normal Move
The Normal Move is a classic move of a piece, just like in a normal chess game.\
The pieces follow all of the same movement patterns as those in standard chess, including moves like castling and en passant. However, there is no concept of check, so the king can move into, or castle through, what would be considered check in classical chess.

_Click on a piece, the piece will be selected, and then click on the destination._

![Screenshot from 2021-12-13 02-00-07](https://user-images.githubusercontent.com/11294851/145755023-b90e8673-df0d-4b26-ace4-9778fd9388ea.png)

##### Split Move
All non-pawns can perform a split move. This move allows the piece to split and occupy two different target squares that it can reach.\
Only squares that are unoccupied are considered legal targets.

_Press `s` and click on a piece (the piece will be selected). Then click on two empty squares._

![Screenshot from 2021-12-13 02-00-33](https://user-images.githubusercontent.com/11294851/145755051-8d61c87e-0bcd-4a75-803d-6a997ac67fc5.png)

##### Merge Move
All non-pawns can perform a merge move. This move is designed to undo a split move, therefore two splits of the same piece merge together in a valid square that both splits can reach.\
Only squares that are unoccupied, or are occupied by one of the splits being merged are considered legal targets.

_Press `m` and click on a piece (the piece will be selected). Now click on a second piece, and finally on the destination of the merge._

![Screenshot from 2021-12-13 02-01-03](https://user-images.githubusercontent.com/11294851/145755131-5020a76b-50f7-4197-b7ca-7895c33c7a69.png)

##### Entanglements
When a classic piece 'passes through' a split of another piece which has no entanglements, a new entanglement is created.
A split of the moving piece will be performed. One part of the split will go to the target square, and the other part will stay in the parting square.
Only one entanglement per piece is permitted. When the fate of a piece is decided, so does the fate of its entanglements.

![Screenshot from 2021-12-13 01-53-12](https://user-images.githubusercontent.com/11294851/145754477-887ad41a-b933-4f22-885a-b76e8c35f456.png)

![Screenshot from 2021-12-13 01-53-30](https://user-images.githubusercontent.com/11294851/145754499-66c9eb47-0cc3-4edc-9506-fcb2a21ac45c.png)

##### Measurements
Any time a move targets a square that is occupied by another piece, the game will perform a measurement. This means it will look at certain squares on the board to determine if they are occupied or empty; and this will decide the final destination of every of the measured pieces and its entanglements.
Measurements are designed to answer a specific yes or no question. If the answer is yes, the move is then performed. If the answer is no, no further action is taken, and play passes to the next player.

_In the following images, you can see an example where black tries to eat a white bishop, but the result of measurement is that the bishop is not located in that square.\
As a consequence of that measurement, the white queen is also repositioned, as it was entangled with the white bishop._

![Screenshot from 2021-12-13 01-54-05](https://user-images.githubusercontent.com/11294851/145754551-ddd337de-addf-49fe-a737-5d93b004ac8b.png)

![Screenshot from 2021-12-13 01-54-21](https://user-images.githubusercontent.com/11294851/145754571-7c605c21-8105-4b6b-b15a-fdf1870caafa.png)

##### Winning
The game is won by capturing your opponent’s king. This means your opponent has no king left anywhere on the board. It is possible for any piece, king included, to exist in a superposition of being captured and not captured. The game will continue until you can say, with certainty, that one player has no king.

##### Exit
You can exit the game at any time by pressing 'Q' or ESC.

#### 2.3. Notation
The notation of each individual move consists of four parts.

The first part consists of a character to indicate the type of move:
- 'N' for Normal Move.
- 'S' for Split Move.
- 'M' for Merge Move.

The second part indicates the parting and destination squares of the move.
- Normal moves will have one parting and one destination square.
- Split moves will have one parting and two destination squares.
- Merge moves will have two parting and one destination squares.

Finally, if one or more measurements were performed during the move, the results will be indicated in order at the **beginning** of the notation.
- '\*' if the measurement was confirmed.
- '#' if the measurement was denied.

### 3. Settings
At any time, you can click on the gear in the top-right corner to change the screen settings.\
Then click on the desired resolution.

![Screenshot from 2021-12-13 02-09-02](https://user-images.githubusercontent.com/11294851/145755830-25386caf-a313-4311-9e80-975f3b56cf5d.png)
