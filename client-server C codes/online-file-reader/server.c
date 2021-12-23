//MAX FILESIZE FOR PRESENTED ALGORITH: 1MB

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>


 

int main(){

   int status, sock, sock2;
    struct sockaddr_in ser;
    char buf[1000000];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock==-1) {
        printf("error socket\n"); return 0;
    }


    ser.sin_family = AF_INET;
    ser.sin_port=htons(33334);
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

        status=recv(sock2, buf, (sizeof buf)-1, 0);
        if(status){
            buf[status-1]='\0';
            if(status)printf("\n\n\n\n%s:\n", buf);
        
            FILE *wsk = fopen(buf, "r");
            if(wsk == 0){
                printf("There was an error opening the file!\n\n");
            status=send(sock2, "There was an error opening the file!", strlen("There was an error opening the file!"), 0); 
            }
            else{
                int w;
                int i=0;
                while((buf[i++]=fgetc(wsk)) != EOF && i<1000000);
                fclose(wsk);
                buf[i-1]='\0';
                printf("%s", buf);
                status=send(sock2, buf, strlen(buf), 0); 
            }
        }
    }
        close(sock2);
    close(sock);


    return 0;
}