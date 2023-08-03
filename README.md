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
