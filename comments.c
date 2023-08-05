/*
* A single integer (4 bytes) holds all of the game data.
*
* First board:  Holds the game state for the first player   (byte + bit)
* Second board: Holds the game state for the second player  (byte + bit)
* Player:       Holds the current player id                 (bit)
* Turn:         The program loop counter                    (nibble)
*               (Padding for the overflow of Turn)          (bit)
* Count:        The loop counter for win checking           (nibble)
* 
*   ┌──────┐  ┌──────────────┐
*   │ turn ├┐ │ second board │
*   └──────┘│ └──────┬───────┘
*           ├──┐ ┌───┴────┐
* 00000000 00000000 00000000 00000000
*     └─┬┘      │          └────┬───┘
* ┌─────┴─┐ ┌───┴────┐   ┌──────┴──────┐
* │ count │ │ player │   │ first board │
* └───────┘ └────────┘   └─────────────┘
*
* The game data ("_") is initialized to the following binary:
* ┌─────────────────────────────────────┐
* │ 00001001 01111000 00000000 00000000 │
* └─────────────────────────────────────┘
* This is equivalent to 303 (100101111) shifted 19 bits to the left.
* 
* Count is set to 9 for the print function.
* Turn is set to 15 so that it will overflow to zero at the start of the program.
*/

int _ = 303 << 19;

int main() {

    /*
    * Turn is incremented at the start of the function.
    * As noted before, instead of writing out the real decimal representation,
    * the use of the left bit shift operator has been used to move 1 over
    * enough bits that it increments Turn. This method of getting and setting data
    * in the integer will be used throughout this program.
    */

    _ += 1 << 19;

    /*
    * In order to place the user input on the board,
    * the result of getchar() is used in a hacky technique that allows one to
    * shift something a negative amount to the left. Normally, bits that
    * are shifted over fall off the end and dont loop back around. However,
    * by shifting over a negative amount, the bit travels from the far right to the far left.
    * 
    * The characters 1-9 (ascii 49-57) loop the 1 through all 32 bits and back to the left with
    * 17-25 shifts to go. When 7 is subtracted from the -getchar(), the shifts are changed to
    * 24-32 bits to go. This puts us in range for the first board. ` + 9 * (_ >> 18 & 1)` is used to
    * move back to the second board in the case that it is O's turn. The 18th bit is shifted to the 1s place
    * and then ANDed against 1 in order to remove all other bits from the result. This effectively returns
    * a 0 if it's X's turn, and a 1 if it's O's turn. If it is a 1, then 9 gets added, shifting the input
    * 9 bits to the left.
    * 
    * ┌────────────────────────────┐
    * │┌───────────────────────────┼────────────┐
    * ││┌──────────────────────────┼──────────┐ │
    * │││ 00000000 00000000 00000000 00000001 ├┐│
    * ││└─────────────────────────────────────┘││
    * │└───────────────────────────────────────┴┼── first loop around
    * └─────────────────────────────────────────┴── second loop around
    */

    _ |= 1 << (-getchar() - 7 + 9 * (_ >> 18 & 1));

    /*
    * This printf solves two problems in one line:
    * e
    * 1. The screen should be cleared every turn of the game
    * 2. The enter key in the input buffer needs to be accounted for
    * 
    * Because getchar will read our enter key the next time it is called, it needs to
    * removed from the buffer. It gets printed out right before the screen is cleared.
    * The escape code `"\e[1;1H\e[2J"` is used for the clearing.
    * I don't actually know what its doing and I'm too lazy to research.
    */

    printf("%c\e[1;1H\e[2J", getchar());

    /*
    * This is the print loop. Count was set to 9, and will go until it reaches 1.
    * Because it's still decremented on the final iteration, it will be at 0 once the loop finishes.
    * Count is obtained or changed by shifting to the 25 bit. (<< 24 or >> 24)
    */

    for (; _ >> 24 > 0; _ -= 1 << 24)

        /*
        * The print loop uses a call to printf with two characters. The first character is for the
        * X, O, or blank space. The second character is set to either 0 or '\n' (decimal 10) depending on
        * if Count - 1 is a multiple of 3. Count - 1 is used so that it will breakline at 7, 4, and 1.
        * If the second character is 0, there will be practically nothing printed to the screen. I say
        * "practically" because the character is technically there, but it is nothing visible.
        * 
        * The default value for the first character is '_' (decimal 95). To get to an X or O, one of two values
        * is subtracted from the default. These two values are multipled by checks on the boards to see which should be used.
        * One will be multipied by 0, and the other by 1. To check the first board, (`7 * (_ >> (_ >> 24) - 1 & 1)`)
        * The value 7 (95 - 7 == 'X') is multipled by the digit of the first board corresponding to Count and ANDed against 1.
        * As previously stated, the shift by 24 gets count, and then the board is shifted over by this value - 1 to have the
        * desired bit for checking in the ones place. 1 is subtracted from the value to adjust for Count starting at 9 rather than 8.
        * (For example, shifting over 9 digits would access the second board rather than the 8th bit of the first.)
        * This is ANDed against 1 to isolate it.
        * 
        * The same logic is used for the second board, except that the shift over is 9 greater
        * to reach the second board instead of the first. 16 is used for the second board as opposed to 7. (95 - 16 == 'O')
        * For the second character, the same style of branchless decision making is used. It is set to 10 multipled by the
        * Result of (Count - 1) % 3.
        */
    
        printf("%c%c", 95 - (7 * (_ >> (_ >> 24) - 1 & 1) + 16 * (_ >> (_ >> 24) - 1 + 9 & 1)), !(((_ >> 24) - 1) % 3) * 10);
    
    /*
    * This is the win checking loop. Count was left at 0 by the previous loop. It will go until
    * it reaches 2. This value is used to shift data over in order to check each section against the same number.
    * For example, this binary:
    * ┌────────────┐
    * │ 1 11000000 │ (decimal 448)
    * └────────────┘
    * can be shifted to the right by 6 bits (where Count == 2) so that it can be against 7 instead of 448, just like if it had
    * been 7 to begin with. The shift for horizantal wins is multiplied by 3, as shown previously. When checking for vertical wins,
    * The shift is just Count.
    * 
    * 000000111 >> 0 bits (Count == 0)
    * 000111000 >> 3 bits (Count == 1)
    * 111000000 >> 6 bits (Count == 2)
    * 
    * 001001001 >> 0 bits (Count == 0)
    * 010010010 >> 1 bit  (Count == 1)
    * 100100100 >> 2 bits (Count == 2)
    */

    for (; _ >> 24 < 3; _ += 1 << 24)

        /*
        * As previously explained, the win check works by shift the board over a certain amount, and then seeing if its equal to a certain number.
        * For horizontal wins, this number is 7, because the first 3 bits of a number in an on state make 7. For a
        * vertical win, the number is 73 for the same reason. (001001001 == 73)
        * `_ >> 3 * (_ >> 24) + 9 * (_ >> 18 & 1) & 7) == 7` is the code to check horizontal wins.
        * It takes 3 times the current Count and shifts the board over by that amount. If it is O's turn then 9 is added to that shift.
        * The shifted value is then ANDed against 7 to isolate it, and if that is equal to 7, there is a win.
        * The same logic is used for the vertical wins. To end the game, the statement simply returns.
        */
        
        if ((_ >> 3 * (_ >> 24) + 9 * (_ >> 18 & 1) & 7) == 7 | (_ >> (_ >> 24) + 9 * (_ >> 18 & 1) & 73) == 73) return 0;
    
    /*
    * This uses the exact same logic as in the loop above, except that its for the two diagonals
    * (100010001 and 001010100)
    */

    if ((_ >> 9 * (_ >> 18 & 1) & 273) == 273 | (_ >> 9 * (_ >> 18 & 1) & 84) == 84) return 0;
    
    /*
    * This resets the Count to 9. Since it was left at 3 by the win checking,
    * 6 is added to it.
    */

    _ += 6 << 24;

    /*
    * This is a flipflop for the player bit. If the bit is 0, it becomes 1, and vice versa.
    * It is used to keep track of who's turn it is.
    */

    _ ^= 1 << 18;
    
    /*
    * The return statement is used to run the program loop. If `_ >> 22` is 1
    * then Turn has reached 8, and the program is over. Otherwise, main is recursively called.
    */

    return _ >> 22 & 1 ? 0 : main();
}
