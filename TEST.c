/*
* A single integer (4 bytes) variable will hold all of the game data
*
* Count:        The program loop counter                    (nibble)
* Player:       Holds the current player id                 (bit)
* First board:  Holds the game state for the first player   (byte + bit)
* Second board: Holds the game state for the second player  (byte + bit)
* 
*  ┌───────┐  ┌──────────────┐
*  │ count ├┐ │ second board │
*  └───────┘│ └──────┬───────┘
*           ├──┐ ┌───┴────┐
* 00000000 00000000 00000000 00000000
*               │          └────┬───┘
*           ┌───┴────┐   ┌──────┴──────┐
*           │ player │   │ first board │
*           └────────┘   └─────────────┘
*/
