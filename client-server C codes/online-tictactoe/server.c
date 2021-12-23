#include <stdio.h>
#include <math.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

char board[3][3]={' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
int pos_x=1, pos_y=1, sock2;
char buf[10000];

void print_board(){
	int status;
		sprintf(buf, "+-+-+-+\n|%c|%c|%c|\n+-+-+-+\n|%c|%c|%c|\n+-+-+-+\n|%c|%c|%c|\n+-+-+-+\n",
		board[0][0],  board[0][1],  board[0][2],
		board[1][0],  board[1][1],  board[1][2],
		board[2][0],  board[2][1],  board[2][2]);
		status = send(sock2, buf, strlen(buf), 0);

	return;
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
	int pl_xx, pl_yy, status; //player coordinates (x, y)
			sprintf(buf, "Your move! Insert coordinates:\n");	
			status = send(sock2, buf, strlen(buf), 0);
			status = recv(sock2, buf, sizeof buf, 0);
			buf[status]='\0';
			pl_xx= (int)buf[0]-'0';
			pl_yy= (int)buf[2]-'0';
			printf("Player positions: %d %d\n", pl_xx, pl_yy);
			while(pl_xx<1 || pl_xx>3 || pl_yy<1 || pl_yy>3 || board[pl_xx-1][pl_yy-1]!=' '){
				sprintf(buf, "Your move! Insert VALID coordinates:\n");
				status = send(sock2, buf, strlen(buf), 0);

				status = recv(sock2, buf, sizeof buf, 0);
				buf[status]='\0';	
				pl_xx= (int)buf[0]-'0';
				pl_yy= (int)buf[2]-'0';
			}
			board[pl_xx-1][pl_yy-1]='O';
}

int check_winner(){
		int tmp1 = check_status();

		if(tmp1 == 1){
			sprintf(buf, "Result: Computer has won the game!\n");
			send(sock2, buf, strlen(buf), 0);
			return 1;
		}
		else if(tmp1==-1){
			print_board();
			sprintf(buf, "Result: Player has won the game!\n");
			send(sock2, buf, strlen(buf), 0);
			return 1;
		}
		return 0;
}


int main(){
   int status, sock;

    struct sockaddr_in ser;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock==-1) {
        printf("error socket\n"); return 0;
    }

    ser.sin_family = AF_INET;
    ser.sin_port=htons(2137); //port
    ser.sin_addr.s_addr=inet_addr("192.168.0.110"); //IP

    status = bind(sock, (struct sockaddr *) &ser, sizeof ser);
    if(status==-1){
        printf("error bind\n");
        return 0;
    }

    status = listen(sock, 10);
    if(status != 0){
        printf("error listen\n");
        return 0;
    }


    sock2 = accept(sock, 0, 0);
    if(sock2==-1){
        printf("error accept\n"); return 0;
    }

	for(int i=0;i<9;i++){
		if(i%2==0){
			printf("Computer move!\n");
			computer_move(i);
			board[pos_x][pos_y]='X';
			print_board();
		}

		else{
			player_move();
		}

		if(check_winner()) break;
		if(i==8){
			sprintf(buf, "Result: Draw!\n");
			status = send(sock2, buf, strlen(buf), 0);
			break;
		}
	}


        close(sock2);
    close(sock);


    return 0;   
}