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

serverSocket = socket(AF_INET, SOCK_STREAM)

# Prepare a sever socket
#Fill in start
PORT = 65016 						# Rayleigh Thai Student Port Number
serverSocket.bind(('',PORT))		# Bind and listen to port
serverSocket.listen(1)
#Fill in end

while True:
	print('The server is ready to receive')

	#Fill in start 
	connectionSocket, addr = serverSocket.accept()		# Accept incoming connection
	#Fill in end

	try:

		#Fill in start 
		message = connectionSocket.recv(1024).decode()	# Receiving incoming Message [increase more if needed]
		#Fill in end

		filename = message.split()[1]

		f = open(filename[1:])

		#Fill in start
		outputdata = f.read()		# read requested file / request
		#Fill in end

		# send one http header line in to the socket

		#Fill in start
		connectionSocket.send(b"HTTP/1.1 200 OK \r\n\r\n")		# return status
		#Fill in end
 
		# Send the content of the requested file to the connection socket
		for i in range(0, len(outputdata)):  
			connectionSocket.send(outputdata[i].encode())
		connectionSocket.send("\r\n".encode()) 
		
		connectionSocket.close()

	except IOError:
			# Send HTTP response code and message for file not found
			#Fill in start
			connectionSocket.send(b"404 File Not Found \r\n\r\n")
			#Fill in end

			# Close the client connection socket
			#Fill in start
			connectionSocket.close()
			#Fill in end

serverSocket.close()  
sys.exit()#Terminate the program after sending the corresponding data