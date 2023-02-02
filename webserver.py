from socket import * 
import sys # In order to terminate the program

serverSocket = socket(AF_INET, SOCK_STREAM)

# Prepare a sever socket
PORT = 3333							# Server Port Number
serverSocket.bind(('',PORT))		# Bind and listen to port
serverSocket.listen(1)

while True:
	print('The server is ready to receive')

	# Accept incoming connection
	connectionSocket, addr = serverSocket.accept()		
	try:
		# Receiving incoming Message [increase more if needed]
		message = connectionSocket.recv(1024).decode()	
		
		# Get file request 
		filename = message.split()[1]			
		f = open(filename[1:])

		# read requested file / request
		outputdata = f.read()		

		# send one http header line in to the socket
		connectionSocket.send(b"HTTP/1.1 200 OK \r\n\r\n")
 
		# Send the content of the requested file to the connection socket
		for i in range(0, len(outputdata)):  
			connectionSocket.send(outputdata[i].encode())
		connectionSocket.send("\r\n".encode()) 
		
		connectionSocket.close()

	except IOError:
			# Send HTTP response code and message for file not found
			connectionSocket.send(b"ERROR 404: File Not Found \r\n\r\n")

			# Close the client connection socket
			connectionSocket.close()

serverSocket.close()  
sys.exit()#Terminate the program after sending the corresponding data