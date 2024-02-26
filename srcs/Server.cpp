/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:59:44 by jaeshin           #+#    #+#             */
/*   Updated: 2024/02/26 19:48:35 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

Server::Server() {
};

Server::~Server() {};

vector<Client> Server::getClients() const {
	return _clients;
};

vector<Channel> Server::getChannels() const {
	return _channels;
};

void Server::addClient(string name) {
	Client newClient = Client(name);
	_clients.push_back(newClient);
};

//void Server::rmClient(Client name) {

//};

void Server::addChannel(string name) {
	Channel newChannel = Channel(name);
	_channels.push_back(newChannel);
};

//void Server::rmChannel(Channel channel) {

//};

int Server::createServer(int port) {
	// Create a socket, on failure returns -1.
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0) {
		cerr << "Error: creating a socket." << endl;
		return 0;
	} else {
		cout << "socket() is OK." << endl;
	}

	// Bind the socket
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	// serverAddr.sin_addr.s_addr = INADDR_ANY;
	// Connect through local network
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
		cerr << "Error: binding socket." << endl;
		close(serverSocket);
		return 0;
	} else {
		cout << "bind() is OK." << endl;
	}

	// Listen for connections
	if (listen(serverSocket, 5) == -1) {
		cerr << "Error: listening on socket." << endl;
		close(serverSocket);
		return 0;
	} else {
		cout << "listen() is OK, Now I am waiting for connections." << endl;
	}

	return serverSocket;
};
