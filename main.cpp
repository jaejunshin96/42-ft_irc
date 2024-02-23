/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:04:11 by jaeshin           #+#    #+#             */
/*   Updated: 2024/02/22 19:34:02 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

int main() {
	// Create a socket, on failure returns -1.
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0) {
		cerr << "Error: creating a socket." << endl;
	} else {
		cout << "socket() is OK." << endl;
	}

	// Bind the socket
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
		cerr << "Error: binding socket." << endl;
		close(serverSocket);
	} else {
		cout << "bind() is OK." << endl;
	}

	// Listen for connections
	if (listen(serverSocket, 5) == -1) {
		cerr << "Error: listening on socket." << endl;
		close(serverSocket);
	} else {
		cout << "listen() is OK." << endl;
	}
}

