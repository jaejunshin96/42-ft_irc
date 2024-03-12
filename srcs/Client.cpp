/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:38:00 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/12 19:21:15 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Client.hpp"

Client::Client() {};

Client::Client(int sockfd, int port, string hostname): \
				_sockfd(sockfd), _port(port), _hostname(hostname) {
	setClientState(HANDSHAKE);
};

Client::~Client() {};

/* getters */
int Client::getSockfd() const { return _sockfd; };

int Client::getPort() const { return _port; };

string Client::getHostname() const { return _hostname; };

string Client::getNickname() const { return _nickname; };

string Client::getUsername() const { return _username; };

string Client::getRealname() const { return _realname; };

string Client::getInfo() const {
	string username = _username.empty() ? "" : "!" + _username;
	string hostname = _hostname.empty() ? "" : "@" + _hostname;

	return _nickname + username + hostname;
};

ClientState Client::getClientState() const { return _clientState; };

Channel *Client::getChannel() const { return _channel; };

/* setters */
void Client::setNickname(string newNick) { _nickname = newNick; };

void Client::setUsername(string newUser) { _username = newUser; };

void Client::setHostname(string newHost) { _hostname = newHost; };

void Client::setRealname(string newReal) { _realname = newReal; };

void Client::setClientState(ClientState newState) { _clientState = newState; };

void Client::setChannel(Channel *channel) { _channel = channel; }

/* other funcs */
bool Client::isRegistered() const {
	return _clientState == REGISTERED ? true : false;
};

void Client::write(const string &message) {
	string buffer = message + "\r\n";
	if (send(_sockfd, buffer.c_str(), buffer.length(), 0) < 0) {
		throw runtime_error("Error: sending a message from a client.");
	}
};

void Client::reply(const string &message) {
	this->write(":" + getInfo() + " " + message);
};

void Client::broadcast(string &input) {
	string broadcastMessage = _nickname + ": " + input;
	vector<Client *> clients = _channel->getClients();
	for (vector<Client *>::iterator it = clients.begin(); it != clients.end(); ++it) {
		send((*it)->getSockfd(), broadcastMessage.c_str(), broadcastMessage.length(), 0);
	}
};
