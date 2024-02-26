/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:03:51 by jaeshin           #+#    #+#             */
/*   Updated: 2024/02/23 18:24:51 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // For inet_addr()
#include <unistd.h>

using namespace std;

int main() {
	// Create a socket, on failure returns -1.
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket < 0) {
		cerr << "Error: creating a socket." << endl;
		return 1;
	} else {
		cout << "socket() is OK." << endl;
	}
	
	// Set up the server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(4242); // Example port number
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Example server IP address (localhost)

	// Connect to the server
	if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
		cerr << "Error: connecting to server." << endl;
		close(clientSocket);
		return 1;
	} else {
		cout << "connect() is OK." << endl;
	}
	
	while (true) {
		// Get user input
		cout << "Enter a message to the server: ";
		string message;
		getline(cin, message);
		
		if (message == "exit") {
			send(clientSocket, message.c_str(), message.length(), 0);
			close(clientSocket);
			break;
		}
		
		// Send data to the server
		if (send(clientSocket, message.c_str(), message.length(), 0) == -1) {
			cerr << "Error: sending data to server." << endl;
			close(clientSocket);
			return 1;
		}
		
		// Receive data from the server
		// char buffer[1024];
		// int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
		// if (bytesReceived == -1) {
		// 	cerr << "Error: receiving data from server" << endl;
		// 	close(clientSocket);
		// 	return 1;
		// }
		// buffer[bytesReceived] = '\0';
		// cout << buffer << endl;
	}
	
	close(clientSocket);
	
	return 0;
}