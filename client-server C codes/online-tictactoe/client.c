#include <stdio.h>
#include <math.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
 

int main(){

    int status, sock;
    struct sockaddr_in ser;
    char buf[10000];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock==-1) {
        printf("error socket\n"); return 0;
    }
    ser.sin_family = AF_INET;
    ser.sin_port=htons(2137); //port
    ser.sin_addr.s_addr=inet_addr("192.168.0.110"); //IP

    status = connect(sock, (struct sockaddr*)&ser, sizeof ser);
    if(status<0){
        printf("error connection\n"); return 0;
    }
    printf("Connection established!.\n");

    while(1){
        for(int i=0;i<2;i++){
            status=recv(sock, buf, (sizeof buf)-1, 0);
            buf[status]='\0';
            printf("%s", buf);
            if(buf[0] == 'Y' || buf[status-2]=='!'|| buf[status-2]==':') break;
        }
        if(buf[status-2]=='!') break;
        fgets(buf, sizeof buf, stdin);    
        status=send(sock, buf, strlen(buf), 0);

    }
        close(sock);
    return 0;
}