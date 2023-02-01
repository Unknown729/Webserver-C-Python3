#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          
#include <sys/socket.h>         //
#include <netinet/in.h>         //
#include <unistd.h>             // close()
#include <arpa/inet.h>          // inet_addr()
#include <string.h>             // strcat()

void error (char *msg)
{
    perror(msg);
    exit(1);
}

int main (int argc, char *argv[])
{
    char *HOST = argv[1];
    int port_number = strtol(argv[2], NULL, 10);
    char *filename = argv[3];

    //Create Socket
    int network_Socket;
    network_Socket = socket(AF_INET, SOCK_STREAM, 0);
    if (network_Socket < 0) error("ERROR opening socket");  //IF Socket failed to create

    // Specify address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port_number);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);

    // Connect 
    int connection_status = connect(network_Socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if (connection_status == -1) error("An error making a connection to the remote socket");
    

    int insert_pos = 5;

    char *message = "GET / HTTP1.1\r\n\r\n";
    int request_length = strlen(message) + strlen(filename)+1;
    char * request = (char*)malloc(request_length);
    strncpy(request, message, insert_pos);
    request[insert_pos]='\0';
    strcat(request, filename);
    char *b = strcat(request, message+insert_pos);

    //printf("%s\n", b);   

    send(network_Socket, b, strlen(b), 0);
    //receive data from the server
    
    char buffer[4096];

    int byte_count = recv(network_Socket, &buffer, sizeof(buffer)-1, 0);
    
    buffer[byte_count] = 0;
    printf("\n%.*s\n", byte_count, buffer);

    free(request);
    close(network_Socket);
}