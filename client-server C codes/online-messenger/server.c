#include <stdio.h>
#include <math.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>


 

int main(){

   int status, sock, sock2;
    struct sockaddr_in ser, cli;
    char buf[10000];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock==-1) {
        printf("error socket\n"); return 0;
    }


    ser.sin_family = AF_INET;
    ser.sin_port=htons(5555);
    ser.sin_addr.s_addr=inet_addr("192.168.0.110");

    status = bind(sock, (struct sockaddr *) &ser, sizeof ser);
    if(status==-1){
        printf("error bind\n");
        return 0;
    }

    status = listen(sock, 10);
    if(status == 1){
        printf("error listen\n");
        return 0;
    }

    sock2 = accept(sock, 0, 0);
    if(sock2==-1){
        printf("error accept\n"); return 0;
    }
    
    while(1){
        status = recv(sock2, buf, sizeof buf, 0);
        printf("Client: %s", buf);
        printf("Server: ");
        fgets(buf, sizeof buf, stdin);
        status = send(sock2, buf, strlen(buf), 0);
    }
        close(sock2);
    close(sock);


    return 0;   
}