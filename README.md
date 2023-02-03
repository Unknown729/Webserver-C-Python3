#Webserver Project



There are 3 file within this folder excluding this README file:
 - webserver.py
 - webclient.py
 - HelloWorld.html
 
The webserver establish the socket and listening to any incoming connection coming from client. The incoming connection will be accept by the server and awaiting for client making the request. Upon rececving the request, server will parse the argument for file request if exist, will return the content of the file requested. However, if file is not exist, error "404 file not found" will return back to socket connection. In order to run the server you must run following command.
E.g., python3 webserver.py 

Upon server running, you are now able to run client asking for file. The webclient.py take 3 agrument such as ip addresss, port number and File requesting. Due to file running in locally and not in the open internet network, 127.0.0.1 and localhost are the only 2 argument that is acceptable. For port number, Rayleigh Thai student port number is 65016. The last argument will be the requesting file. The webclient.py will attempt to connect to the server. upon the connection establishment, the webclient will send requesting file to the server. Upon received all data of requesting file or appropriate response from server, connection will close. The following will be structure of agrument for running webclient.py
E.g., python3 webclient.py <server_host> <server_port> <filename> 

The HelloWorld.html is a sample file of testing the retrieval from the server.

Future note of this assignment: Attempt to create Multithreading to the server to handle more than one request at a time. This would consisting into socketBlocking() to one connection prevent another request binding to the existing request connection pair. 

