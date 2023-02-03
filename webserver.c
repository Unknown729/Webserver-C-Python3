#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

// Print message error
void error (char *msg)
{
    perror(msg);
    exit(1);
}

int main (void)
{
    int port_number = 65016;

    // Create Socket
    int server_Socket;
    server_Socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_Socket < 0) error("ERROR opening socket");  //IF Socket failed to create

    // Specify address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port_number);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to host and port and start listening
    bind(server_Socket, (struct sockaddr*) &server_address, sizeof(server_address));
    listen(server_Socket, 1);

    while (1)
    {
        printf("Server is ready to receive\n");
        int client_connection;

        //Accept incoming connection
        int len = sizeof(server_address); //without this we have errors as long unsigned int
        client_connection = accept(server_Socket, (struct sockaddr*) &server_address, &len);

        //receiving incoming Messages
        char buffer[1024];
        int content;
        if((content = recv(client_connection, &buffer, sizeof(buffer)-1, 0)) > 0)
        {
            buffer[content] = 0;
        } 
        
        // Parse request to get file requested
        char delim[] = " ";
        char * a = strcat(buffer, " ");
        char * ptr = strtok(a, delim);
        char *pathfile_request = strtok(NULL, delim);
        char *file_requested = pathfile_request+1;

        // Parse file if exist
        if (access(file_requested, F_OK) == 0)
        {
            // send one line header HTTP
            char * header_line = "HTTP/1.1 200 OK \r\n\r\n";
            send(client_connection, header_line, strlen(header_line), 0);

            //Open File, read and compile into one and send to the connection Socket
            FILE* file_access;
            file_access = fopen(file_requested, "r");
            char *data;
            char * line = NULL;
            size_t len = 0;
            ssize_t read;
            while ( (read = getline(&line, &len, file_access)) != -1)
            {
                strncat(data, line, strlen(line));
            }
            send(client_connection, data, strlen(data), 0);

            //Clear data request and close file
            data[0] = '\0'; 
            fclose(file_access);
            if (line) 
            {
                free(line);
            }
        }
        else
        {
            printf("\n404: File does not exist\n");
        }
        buffer[0] = '\0';
        //Close Client Connection
        close(client_connection);
    }
    return 0;
}
