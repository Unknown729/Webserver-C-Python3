#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>
#include <string.h>

void error (char *msg)
{
    perror(msg);
    exit(1);
}

/*
void callingMethod(char *msg)
{
    if (msg == "GET")
    {
        return;
    }
    if (msg == "POST")
    {
        return;
    }
    else printf("No Method was accepted\n");
}*/

int main ()
{
    int port_number = 65016;
    char * header_line = "HTTP/1.1 200 OK \r\n\r\n";
    
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
    listen(server_Socket, 5);
    printf("Server ready for connections\n");

    while (1)
    {
        int client_connection;
        //Accept incoming connection
        int len = sizeof(server_address); //without this we have errors as long unsigned int
        client_connection = accept(server_Socket, (struct sockaddr*) &server_address, &len);
        printf("Connection Connected\n");

        char buffer[1024];
        int content;
        if((content = recv(client_connection, &buffer, sizeof(buffer)-1, 0)) > 0)
        {
            buffer[content] = 0;
            printf("%.*s\n", content, buffer);
        } 
        char * a = strcat(buffer, " ");
        int init_size = strlen(a);
        char delim[] = " ";
        char * ptr = strtok(a, delim);
        //printf("%s\n", ptr);
        char *pathfile_requested = strtok(NULL, delim);
        char *file_requested = pathfile_requested+1;
        //printf("File requesting is: %s\n", file_requested);
        if (access(file_requested, F_OK) == 0)
        {   // File Exist
            //printf("Files exist\n");
            //send(client_connection, header_line, sizeof(header_line), 0);
            char file_data;
            FILE* file_access;
            //char data[] = "";
            file_access = fopen(file_requested, "r");
            //printf("here\n");
            
            do
            {
                file_data = fgetc(file_access);
                //strcat(data, &file_data);
                //printf("%.s\n", data);
                send(client_connection, &file_data, sizeof(file_data), 0);
                //send(client_connection, data, strlen(data), 0);
                //printf("he2342342re\n");
                printf("%c\n", file_data);
            
            } while (file_data != EOF);
            //send(client_connection, data, strlen(data), 0);
            printf("2342424123515\n");

            

            fclose(file_access);
        }
        else{
            printf("File does not exist\n");
        }
/*



        
        //char * responses;
        //strncpy()
        // strsep(&a, delim);
        //printf("%li\n", sizeof(ptr));
        //printf("%c\n", ptr[1]);

        //printf("%s\n", responses);
        //ptr = strtok(buffer, delim);

        //printf("%s\n", ptr);

        


        
        
        //buffer[content] = 0;
        //printf("\n%.*s\n", content, buffer);


        // Seding data to the socket
        //char *data = "GET /Hello.html HTTP/1.1\r\n";
        //send(client_connection, data, strlen(data), 0);
        close(client_connection);*/
    }

    return 0;
}