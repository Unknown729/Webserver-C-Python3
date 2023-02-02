# Import socket module
from socket import * 
import sys # In order to terminate the program

ClientSocket = socket(AF_INET, SOCK_STREAM)

# Prepare a connection to socket
HOST = sys.argv[1]				# localhost or 127.0.0.1 (Server address)
PORT = int(sys.argv[2]) 		# Server Port Number
Filename = sys.argv[3]			# File request

# establish connection and send GET Request
ClientSocket.connect((HOST,PORT))
message = "GET /%s HTTP/1.1\r\n\r\n" %sys.argv[3]
ClientSocket.send(message.encode())
	
# retrieve data from Server and display	
while True:
    datafromServer = ClientSocket.recv(1024).decode()
    if not datafromServer:
        break
    print(datafromServer)

ClientSocket.close()  
sys.exit()#Terminate the program after sending the corresponding data
