# Webserver Project

## Introduction
The Purpose of this project is to practice socket programming on TCP connection setup. The server is set up with specified port in its code and running on its serverIP. The socket opens port, binding and listening for any incoming connection while staying at localhost or 127.0.0.1. We are not pushing it toward the big IoT as we are here to only learn how the socket programing works thus running at serverIP. The project will also take GET HTTP file request and return appropriate response back to client. Only the ```GET``` request is implemented here. This project were origin in Networks and Security class where the code can either in C or Python (Python3 specific). Or you can do both to further understand socket programing in different languages. If you are a student, you might view the codes to understand how implementation works. I **DO NOT** encourage plagiarism! 

## Contents of this project
There are 6 files within this folder excluding this README:
 - webserver.c
 - webclient.c
 - webserver.py
 - webclient.py
 - HelloWorld.html
 - Concept.png

## How this works:
The webserver establish the socket and listening to any incoming connection coming from client. The incoming connection will be accept by the server and awaiting for client making the request. A simple three-way handshake established. Upon rececving the request, server will parse the argument. In this special case of project, we only getting the GET<sup>(1)</sup> request for HTTP. There is no implementation of ```POST```, ```HEAD``` or ```PUT``` method. 

Once client is connected through serverIP and its corresponding port number, file request will be needed. Thus command line will take always taking 3 arguments as ```<serverIP> <port number> <file request>```. ServerIP and port number on client side need to be exact as server side. The *file request* can be any file that the client want to get. It is the server responsibility of searching for file exist or not and return with appropriate response. For instance of HTML file request in this project that exist will return ```200 OK``` status whereas ```ERROR 404: File not found``` for nonexistent file. Client now will wait for server return a reply and printing response from Server. 

The server now will process the arguments coming from client side. The first part of the request will be GET request. The second part will be pathfile request. This is what we will be focusing on locate the file and return file data to send back to client through socket. For file request if exist, will return the content of the file requested. However, if file is not exist, error "404 file not found" will return back to socket connection. Once the data of the file request is retrieved, server will send data through the established connection. Once completion of sending data, server will close client connection. 

Client will receive response from server of file existence and its data if file exist. Completion of receiving data will close the socket connection to the server. 

<img src = "https://github.com/Unknown729/Webserver-C-Python3-/blob/main/Concept.PNG" align="center">

## Command Line: 
### C:
 - Server:
  - ```gcc webserver.c -o server```
  - ```./server```
 - Client:
  - ```gcc webclient.c -o client```
  - ```./client <serverIP> <port number> <filename>```


### Python:
 - Server:
```python3 webserver.py``` 
 -  Client:
```python3 webclient.py <server_host> <server_port> <filename> ```


## NOTE:
1. For C code, since I have to parse the argument as GET, I know to split it up at certain array to get file request. Other methods can be implement within the code. However, due to time constraint, I will not implement parsing for method calling. Perhaps this can be future project when I have more time. 
2. Multithreading this connection allowing server to take more client request was considered. Back to time constraint, I have not explored this area. 
