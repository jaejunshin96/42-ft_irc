/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:04:11 by jaeshin           #+#    #+#             */
/*   Updated: 2024/02/26 19:34:24 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // For inet_addr()
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {
	// Create a socket, on failure returns -1.
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0) {
		cerr << "Error: creating a socket." << endl;
		return 1;
	} else {
		cout << "socket() is OK." << endl;
	}

	// Bind the socket
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	// serverAddr.sin_addr.s_addr = INADDR_ANY;
	// Connect through local network
	serverAddr.sin_port = htons(4242);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
		cerr << "Error: binding socket." << endl;
		close(serverSocket);
		return 1;
	} else {
		cout << "bind() is OK." << endl;
	}

	// Listen for connections
	if (listen(serverSocket, 5) == -1) {
		cerr << "Error: listening on socket." << endl;
		close(serverSocket);
		return 1;
	} else {
		cout << "listen() is OK, Now I am waiting for connections." << endl;
	}

	// Accept incoming connection
	while (true) {
		struct sockaddr_in clientAddr;
		socklen_t clientAddrLen = sizeof(clientAddr);
		int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
		if (clientSocket == -1) {
			cerr << "Error: accpeting connection." << endl;
			continue;
		} else {
			cout << "Client " << clientSocket << " has been accpeted." << endl;
			while (true) {
				// // Get user input
				// cout << "Enter a message to the client: ";
				// string message;
				// getline(cin, message);

				// // Send a message
				// if (send(clientSocket, message.c_str(), message.length(), 0) == -1) {
				// 	cerr << "Error: sending data to client." << endl;
				// 	close(clientSocket);
				// 	return 1;
				// }

				// Receive a message from clients
				char buffer[1024];
				int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
				if (bytesReceived == -1) {
					cerr << "Error: receving data from client" << endl;
					close(clientSocket);
				}
				buffer[bytesReceived] = '\0';
				string exitStr = "exit";
				if (strcmp(buffer, exitStr.c_str()) == 0) {
					cout << "exit" << endl;
					break;
				}
				cout << "Message from client: " << buffer << endl;
			}
		}
		close(clientSocket);
	}

	// Close the socket when it is done.
	close(serverSocket);

	return 0;
}

