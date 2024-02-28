/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:59:44 by jaeshin           #+#    #+#             */
/*   Updated: 2024/02/28 19:27:58 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

Server::Server() {
	_serverFd = createServer(4242);

	if (!_serverFd) {
		cerr << "Error: creating a server." << endl;
		exit(1);
	}
	_listening = 42;
	start();
};

Server::~Server() {};

//vector<Client> Server::getClients() const {
//	return _clients;
//};

vector<Channel> Server::getChannels() const {
	return _channels;
};

//void Server::addClient(string name) {
//	Client newClient = Client(name);
//	_clients.push_back(newClient);
//};

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

void Server::start(void) {
	pollfd server = {_serverFd, POLLIN, 0};
	_pfds.push_back(server);

	cout << "Server is listening..." << endl;

	while(_listening) {
		if (poll(_pfds.begin().base(), _pfds.size(), -1) < 0)
			throw runtime_error("Error: while polling from fd.");

		for (pfd_iterator it = _pfds.begin(); it != _pfds.end(); it++) {
			if (it->revents == 0)
				continue;

			if ((it->revents & POLLHUP) == POLLHUP) {
				// disconnect
				cout << "Disconnected." << endl;
				disconnectClient(it->fd);
				break;
			}

			if ((it->revents & POLLIN) == POLLIN) {
				if (it->fd == _serverFd) {
					// connected
					cout << "Connected." << endl;
					connectClient();
					break;
				}
				// message
				message(it->fd);
			}
		}
	}
};

void Server::disconnectClient(int fd) {
	Client *client = _clients.at(fd);
	_clients.erase(fd);

	for (pfd_iterator it = _pfds.begin(); it != _pfds.end(); it++) {
		if (it->fd == fd) {
			_pfds.erase(it);
			close(fd);
			break;
		}
	}
	cout << client->getName() << " has disconnected." << endl;
	delete client;
};

void Server::connectClient(void) {
	sockaddr_in clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);
	int clientSocket = accept(_serverFd, (struct sockaddr *)&clientAddr, &clientAddrLen);
	if (clientSocket == -1)
		throw runtime_error("Error: accepting a clint.");

	pollfd pfd = {clientSocket, POLLIN, 0};
	_pfds.push_back(pfd);

	Client *client = new Client("jaejun");
	_clients.insert(make_pair(clientSocket, client));

	cout << "Client " << clientSocket << " " << client->getName() << " has been accepted." << endl;
}

void Server::message(int fd) {
	//Client *client = _clients.at(fd);
	string message;

	char buffer[1024];
	bzero(buffer, 1024);

	while (!strstr(buffer, "\n")) {
		bzero(buffer, 1024);

		if (((recv(fd, buffer, 1024, 0) < 0) && (errno != EWOULDBLOCK)))
			throw runtime_error("Error: reading buffer from a client.");

		message.append(buffer);
	}

	cout << message;
};
