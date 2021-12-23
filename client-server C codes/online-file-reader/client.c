//MAX FILESIZE FOR PRESENTED ALGORITH: 1MB

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

 

int main(){

    int status, sock;
    struct sockaddr_in ser;
    char buf[1000000];


    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock==-1) {
        printf("error socket\n"); return 0;
    }
    ser.sin_family = AF_INET;
    ser.sin_port=htons(33334);
    ser.sin_addr.s_addr=inet_addr("192.168.0.110");

    status = connect(sock, (struct sockaddr*)&ser, sizeof ser);
    if(status<0){
        printf("error connection\n"); return 0;
    }
    printf("Connection established.\n");
    while(1){
        printf("Type filename: ");
        fgets(buf, sizeof buf, stdin);
        status = send(sock, buf, strlen(buf), 0);

            status = recv(sock, buf, sizeof buf, 0);
            buf[status]='\0';
            printf("S:\n%s\n", buf);
            
    }
    close(sock);


    return 0;
}