#include <stdio.h>
void printboard(int board[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d", board[i][j]);
		}
		printf("\n");
	}
}
void move(int board[3][3], int player) {
	int x, y;
	scanf("%d", &x);
	scanf("%d", &y);
	board[y][x] = player;
}
int checkwin(int board[3][3]) {
	for (int i = 0; i < 3; i++) {
		if ((board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][2] != 0) ||
		    (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[2][i] != 0)) {
			return 1;
		}
	}
	if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[2][2] != 0) ||
	    (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[2][0] != 0)) {
		return 1;
	}
	return 0;
}
int main(void) {
	int board[3][3] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	for (int i = 0; i < 9; i++) {
		printboard(board);
		move(board, i % 2 + 1);
		if (checkwin(board)) {
			break;
		}
	}
	return 0;
}
