#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

char board[3][3]={' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
int pos_x=1, pos_y=1;

void print_board(){
printf("\n\n\n+-+-+-+\n");	
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			printf("|%c", board[i][j]);	
		}
		printf("|\n+-+-+-+\n");		
	}
}

int check_status(){
	//1 - Computer wins, -1 - Player wins, 0 - draw/no winner
    for(int i=0;i<3;i++){
        if(board[i][0]==board[i][1] && board[i][2]==board[i][1] && board[i][1]=='X') return 1;
        if(board[i][0]==board[i][1] && board[i][2]==board[i][1] && board[i][1]=='O') return -1;

        if(board[0][i]==board[1][i] && board[2][i]==board[1][i] && board[1][i]=='X') return 1;
        if(board[0][i]==board[1][i] && board[2][i]==board[1][i] && board[1][i]=='O') return -1;
    }

    if(board[0][0]==board[1][1] && board[2][2]==board[1][1] && board[1][1]=='O') return -1;
    if(board[0][0]==board[1][1] && board[2][2]==board[1][1] && board[1][1]=='X') return 1;
    
    if(board[0][2]==board[1][1] && board[2][0]==board[1][1] && board[1][1]=='X') return 1;
    if(board[0][2]==board[1][1] && board[2][0]==board[1][1] && board[1][1]=='O') return -1;

	return 0;

}



int minmax(int moves){
	if(check_status()!=0 || moves>=9) return check_status();

	int maxscore = -2;
	int minscore = 2;
	int tmpscore = 0;
	int guard = 0;

	if(moves%2 == 1){ //player move
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				if(board[i][j]==' '){
					board[i][j]='O';
					guard = 1;
					tmpscore = minmax(moves+1);
					if(tmpscore < minscore){
						minscore = tmpscore;
					}
					board[i][j]=' ';
				}
			}
		}
		if(guard) return minscore;
		return 0;
	}
	else{ //computer move
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				if(board[i][j]==' '){
					board[i][j]='X';
					tmpscore = minmax(moves+1);
					if(tmpscore > maxscore){
						maxscore = tmpscore;
					}
					board[i][j]=' ';
				}
			}
		}
		if(guard) return maxscore;
		return 0;
	}


}

void computer_move(int moves){
	int maxscore = -2;
	int tmpscore = 0;

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(board[i][j]==' '){
				board[i][j]='X';
				if(check_status()==1){
					pos_x = i, pos_y = j;
					board[i][j]=' ';
					return;
				}
				tmpscore = minmax(moves+1);
				board[i][j]=' ';
				if(tmpscore > maxscore){
					maxscore = tmpscore;
					pos_x = i, pos_y = j;
				}
			}
		}
	}
	return;
}

void player_move(){
	int pl_xx, pl_yy; //player coordinates (x, y)
	printf("Your move! Insert coordinates: ");
	scanf("%d", &pl_xx);
	scanf("%d", &pl_yy);
	while(pl_xx<1 || pl_xx>3 || pl_yy<1 || pl_yy>3 || board[pl_xx-1][pl_yy-1]!=' '){
		printf("Your move! Insert VALID coordinates: ");
		scanf("%d", &pl_xx);
		scanf("%d", &pl_yy);
	}
	board[pl_xx-1][pl_yy-1]='O';
}

int check_winner(){
		int tmp1 = check_status();

		if(tmp1 == 1){
			printf("Computer has won the game!\n");
			return 1;
		}
		else if(tmp1==-1){
			print_board();
			printf("Player has won the game!\n");
			return 1;
		}
		return 0;
}

void game(){
	for(int i=0;i<9;i++){
		if(i%2==0){
			// if(i==0) board[1][1] = 'X';
			// else{
				computer_move(i);
				// printf("%d, %d", pos_x, pos_y);
				board[pos_x][pos_y]='X';
			// }
        	print_board();
		}

		else{
			player_move();
		}

		if(check_winner()) return;
		if(i==8){
			printf("Draw!\n");
			return;
		}
	}
}


int main(){
	game();
    return 0;
}
