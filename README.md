TicTacToe with a single variable
--------------------------------

```c
int _=303<<19;int main(){_+=1<<19;_|=1
<<(-getchar()-7+9*(_>>18&1));printf(//
"%c\e[1;1H\e[2J",getchar());for(;_>>24
>0;_-=1<<24)printf("%c%c",95-(7*(_>>(_
>>24)-1&1)+16*(_>>(_>>24)-1+9&1)),!(((
_>>24)-1)%3)*10);for(;_>>24<3;_+=1<<24
)if((_>>3*(_>>24)+9*(_>>18&1)&7)==7|(_
>>(_>>24)+9*(_>>18&1)&73)==73)return 0
;if((_>>9*(_>>18&1)&273)==273|(_>>9*(_
>>18&1)&84)==84)return 0;_+=6<<24;_^=1
<<18;return _>>22&1?0:main();}/*seal*/
```

I think I started this project out with goals in mind. I can't remember, though. Anyway its a tictactoe game using only a single variable.

## Understanding the code
I did my best to explain the inner workings of the program in the comments.c file

## Playing the game
Players take turns placing an X or O on the board through the use of the 1-9 keys. They correspond to the spaces on the board like so:
```
123
456
789
```
To play, simply type your input number and press enter.

**⚠️ WARNING: THIS PROGRAM EXPECTS PERFECT INPUT.** If you tell it to place your piece at "UNICORN" or where someone has already gone, and it breaks, then it's on you.

## Installing and running the game
Requirements:
- GCC
- git (if you dont want to copy and paste code)
- python (if you're on windows)

If you don't have access to GCC, you can go to [onlinegdb](https://www.onlinegdb.com/) to run the code.
Simply copy and paste the code in, and set the language to C. When you run it, you will get compiler warnings, however you can simply ignore them.

Download the repo
```bash
git clone https://github.com/chomp105/shorttt
cd shorttt
```
⚠️ Skip this step if you aren't on windows
```batch
python3 win.py && del win.py
```
Compile the code
```bash
gcc shorttt.c -ow shorttt
```
Run the code

*nix: `./shorttt`

windows: `shorttt`
