#**********************************************************
#*	Name: Rayleigh Thai
#*	StarID: it5651eg
#*
#* 	Course: ICS 460
#*	Assignment: Project 1 - Web Server
#**********************************************************

# Import socket module
from socket import * 
import sys # In order to terminate the program

ClientSocket = socket(AF_INET, SOCK_STREAM)

# Prepare a connection to socket
HOST = sys.argv[1]				# localhost or 127.0.0.1
PORT = int(sys.argv[2]) 		# Rayleigh Thai Student Port Number
Filename = sys.argv[3]			# request file

# establish connection and send GET Request
ClientSocket.connect((HOST,PORT))
message = "GET /%s HTTP/1.1\r\n\r\n" %sys.argv[3]
ClientSocket.send(message.encode())
	
# retrieve data from Server and display	
#AllData = []
while True:
    datafromServer = ClientSocket.recv(1024).decode()
    if not datafromServer:
        break
    print(datafromServer)

#print(AllData)



#datafromServer = ClientSocket.recv(1024).decode()
#print(datafromServer)
		
ClientSocket.close()  
sys.exit()#Terminate the program after sending the corresponding data
