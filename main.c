/*
    Simple udp client version pédagoqique
    bogt(2018)
*/
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<unistd.h>

#include<arpa/inet.h>
#include<sys/socket.h>

#define SERVER "127.0.0.1"
#define BUFLEN 512  //Max length of buffer
#define PORT 8888  //The port on which to send data


int main(void)
{
    struct sockaddr_in si_other;
    int my_socket;
    int slen=sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];

    printf("Client UDP \n");

    if ( (my_socket=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        printf("err: Socket\n");
    }

    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);

    if (inet_aton(SERVER , &si_other.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(EXIT_FAILURE);
    }


    printf("Entrer message texte : ");
    message[0]='\0';
    /*        gets(message);  deprecated */
    fgets(message,BUFLEN,stdin);

    //send the message


    if (sendto(my_socket, message, strlen(message) , 0 , (struct sockaddr *) &si_other,(socklen_t)slen)==-1)
    {
        printf("Err: sendto \n");
    }

    //receive a reply and print it
    //clear the buffer by filling null, it might have previously received data
    memset(buf,'\0', BUFLEN);
    //try to receive some data, this is a blocking call
    if (recvfrom(my_socket, buf, BUFLEN, 0, (struct sockaddr *) &si_other, (socklen_t *)&slen) == -1)
    {
        printf("err: recvfrom");
    }
    printf("chaine renvoyée au client =>");
    puts(buf);

    close(my_socket);

    return EXIT_SUCCESS;
}
