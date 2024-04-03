/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:59:44 by jaeshin           #+#    #+#             */
/*   Updated: 2024/04/03 14:05:54 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

int Server::_listening = 42;

Server::Server(const string &port, const string &password): _password(password) {
	_port = stoi(port);
	if (!(0 <= _port && _port <= 65535))
		throw runtime_error("Error: Invalid port number.");

	_serverFd = createServer(_port);
	if (!_serverFd)
		throw runtime_error("Error: creating a server.");

	_parser = new Parser(this);

	start();
};

Server::~Server() {
	delete _parser;

	map<string, Channel *>::iterator it;
	for (it = _channels.begin(); it != _channels.end(); it++) {
		delete it->second;
	}

	map<int, Client *>::iterator it2;
	for (it2 = _clients.begin(); it2 != _clients.end(); it2++) {
		delete it2->second;
	}
};

int Server::getPort() const { return _port; };

string Server::getPassword() const { return _password; };

map<int, Client *> Server::getClients() const { return _clients; };

map<string, Channel *> Server::getChannels() const { return _channels; };

Client *Server::searchClient(string &name) {
	map<int, Client *>::iterator it;

	for (it = _clients.begin(); it != _clients.end(); it++) {
		if (it->second->getNickname() == name)
			return it->second;
	}
	return NULL;
};

Channel *Server::searchChannel(string &name) {
	return _channels[name] ? _channels[name] : NULL;
};

void Server::addChannel(Channel *newChannel) {
	_channels.insert(make_pair(newChannel->getName(), newChannel));
};

void Server::rmChannel(string &chName) {
	_channels.erase(chName);
};

int Server::createServer(int port) {
	// Create a socket, on failure returns -1.
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0)
		throw runtime_error("Error: creating a socket.");
	else
		cout << "socket() is OK." << endl;

	// Connect through local network
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	// Bind the socket
	if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
		close(serverSocket);
		throw runtime_error("Error: binding socket.");
	} else {
		cout << "bind() is OK." << endl;
	}

	// Listen for connections
	if (listen(serverSocket, 5) == -1) {
		close(serverSocket);
		throw runtime_error("Error: listening on socket.");
	} else {
		cout << "listen() is OK, Now I am waiting for connections." << endl;
	}

	return serverSocket;
};

void Server::start(void) {
	pollfd server = {_serverFd, POLLIN, 0};
	_pfds.push_back(server);

	cout << "Server is listening..." << endl;

	while(Server::_listening) {
		if (poll(_pfds.begin().base(), _pfds.size(), -1) < 0 && Server::_listening != 0) {
			throw runtime_error("Error: while polling from fd.");
		} else if (Server::_listening == 0) {
			break;
		}

		for (pfd_iterator it = _pfds.begin(); it != _pfds.end(); it++) {
			if (it->revents == 0)
				continue;

			if ((it->revents & POLLHUP) == POLLHUP) {
				// disconnected
				if (getClients().count(it->fd)) {
					if (getClients().at(it->fd)->getClientState() != DISCONNECTED)
						disconnectClient(it->fd);
				}
				break;
			}

			if ((it->revents & POLLIN) == POLLIN) {
				if (it->fd == _serverFd) {
					// connected
					connectClient();
					break;
				}
				// user input
				handleInput(it->fd);
			}
		}
	}
	for (pfd_iterator it = _pfds.begin(); it != _pfds.end(); it++) {
		close(it->fd);
	}
	close(_serverFd);
	return ;
};

void Server::disconnectClient(int fd) {
	try {
		pfd_iterator itB = _pfds.begin();
		pfd_iterator itE = _pfds.end();

		while (itB != itE) {
			if (itB->fd == fd) {
				_pfds.erase(itB);
				close(fd);
				break;
			}
			itB++;
		}
		if (_clients.count(fd)) {
			Client *client = _clients.at(fd);
			_clients.erase(fd);
			cout << client->getHostname() << " " << fd << " has been disconnected." << endl;
			delete client;
		}
	} catch (const exception &e) {
		cout << "Error: disconnecting a client" << e.what() << endl;
	}
};

void Server::connectClient(void) {
	sockaddr_in clientAddr;
	memset(&clientAddr, 0, sizeof(clientAddr));
	socklen_t clientAddrLen = sizeof(clientAddr);

	// Connect the sockets between client and server
	int clientSocket = accept(_serverFd, (struct sockaddr *)&clientAddr, &clientAddrLen);
	if (clientSocket == -1)
		throw runtime_error("Error: accepting a clint.");

	// Set the socket non-blocking
	if (fcntl(clientSocket, F_SETFL, O_NONBLOCK) == -1)
		throw runtime_error("Error: setting a client socket non-blocking.");

	// Add the socket to pollfd
	pollfd pfd = {clientSocket, POLLIN, 0};
	_pfds.push_back(pfd);

	char hostname[NI_MAXHOST];
	int result = getnameinfo((sockaddr *)&clientAddr, clientAddrLen, hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV);
	if (result != 0) {
		throw runtime_error("Error: getting a hostname on a client.");
	}

	Client *client = new Client(clientSocket, ntohs(clientAddr.sin_port), hostname);
	_clients.insert(make_pair(clientSocket, client));

	cout << client->getHostname() << " " << client->getSockfd() <<\
		" has been connected." << endl;
}

string Server::readInput(int fd) {
	string message;
	size_t len = 0;
	char buffer[1024];

	while (!strstr(buffer, "\n")) {
		memset(buffer, 0, 1024);
		len += recv(fd, buffer, 1023, 0);

		if ((len < 0) && (errno != EWOULDBLOCK))
			throw runtime_error("Error: reading buffer from a client.");

		message.append(buffer);
	}

	return message;
};

void Server::handleInput(int fd) {
	try {
		if (_clients.count(fd)) {
			Client *client = _clients.at(fd);
			string message = readInput(fd);

			_parser->parse(client, message);
		}
	} catch (const exception &e) {
		cerr << e.what() << endl;
	}
};

void Server::signalHandler(int signum) {
	(void)signum;
	cout << endl << "Signal Received." << endl;
	Server::_listening = 0;
};
