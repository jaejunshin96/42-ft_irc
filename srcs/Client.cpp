/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:38:00 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/03 16:51:39 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Client.hpp"

Client::Client() {};

Client::Client(int sockfd, int port, string hostname): \
	_sockfd(sockfd), _port(port), _hostname(hostname) {};

Client::~Client() {};

/* getters */
int Client::getSockfd() const { return _sockfd; };
int Client::getPort() const { return _port; };
string Client::getHostname() const { return _hostname; };
string Client::getNickname() const { return _nickname; };
string Client::getUsername() const { return _username; };
ClientState Client::getClientState() const { return _clientState; };
vector<Channel> Client::getChannels() const { return _channels; };

/* setters */
void Client::setNickname(string newNick) { _nickname = newNick; };
void Client::setClientState(ClientState newState) { _clientState = newState; };
