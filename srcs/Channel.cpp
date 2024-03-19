/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:38:03 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/19 23:34:20 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Channel.hpp"

Channel::Channel() {};

Channel::Channel(string &name, string &password): _name(name), _password(password),\
				 _inviteOnly(false) {};

Channel::~Channel() {};

/* getters */
string Channel::getName() const { return _name; };

string Channel::getPassword() const { return _password; };

bool Channel::getInviteState() const { return _inviteOnly; };

map<string, Client *> Channel::getClients() const { return _clients; };

vector<string> Channel::getOperators() const { return _ops; };

/* setters */
void Channel::setName(string &newName) { _name = newName; };

void Channel::setInviteStatus(bool toggle) { _inviteOnly = toggle; };

void Channel::addClient(Client *client) {
	_clients.insert(make_pair(client->getNickname(), client));
};

void Channel::rmClient(const string &name) {
	_clients.erase(name);
	rmOperator(name);
};

void Channel::addOperator(const string &nick) {
	_ops.push_back(nick);
};

void Channel::rmOperator(const string &nick) {
	vector<string>::iterator it;
	for (it = _ops.begin(); it != _ops.end(); it++) {
		if (*it == nick)
			_ops.erase(it);
	}
};

bool Channel::searchOperator(const string &nick) {
	vector<string>::iterator it;
	for (it = _ops.begin(); it != _ops.end(); it++) {
		if (*it == nick)
			return true;
	}
	return false;
};

void Channel::broadcast(Client *client, string input, bool isMsg) {
	string broadcastMessage = isMsg ? client->getNickname() + ": " + input :\
										input;
	map<string, Client *>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it) {
		int clientSockfd = it->second->getSockfd();
		send(clientSockfd, broadcastMessage.c_str(), broadcastMessage.length(), 0);
	}
};
