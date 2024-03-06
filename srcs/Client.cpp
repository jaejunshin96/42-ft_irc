/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:38:00 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/06 17:49:51 by jaeshin          ###   ########.fr       */
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
ClientState Client::getClientState() const { return _clientState; };
vector<Channel> Client::getChannels() const { return _channels; };

/* setters */
void Client::setNickname(string newNick) { _nickname = newNick; };
void Client::setUsername(string newUser) { _username = newUser; };
void Client::setHostname(string newHost) { _hostname = newHost; };
void Client::setRealname(string newReal) { _realname = newReal; };
void Client::setClientState(ClientState newState) { _clientState = newState; };
