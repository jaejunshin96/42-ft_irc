/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:38:03 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/22 20:52:19 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Channel.hpp"

Channel::Channel() {};

Channel::Channel(string &name, string &password): _name(name), _password(password),\
				 _topic(""), _inviteOnly(false), _topicRestricted(false),\
				  _pwRequired(false), _clientLimited(false), _limit(5) {};

Channel::~Channel() {};

/* getters */
string Channel::getName() const { return _name; };

string Channel::getPassword() const { return _password; };

map<string, Client *> Channel::getClients() const { return _clients; };

vector<string> Channel::getOperators() const { return _ops; };

vector<string> Channel::getInvites() const { return _invites; };

string Channel::getTopic() const { return _topic; };

bool Channel::getInviteState() const { return _inviteOnly; };

bool Channel::getTopicRestrict() const { return _topicRestricted; };

bool Channel::getPwRequired() const { return _pwRequired; };

bool Channel::getClientLimited() const { return _clientLimited; };

int Channel::getLimit() const { return _limit; };

int Channel::getClientSize() const { return _clients.size(); };

/* setters */
void Channel::setName(string &newName) { _name = newName; };

void Channel::setTopic(string &newTopic) { _topic = newTopic; };

void Channel::setInviteStatus(bool toggle) { _inviteOnly = toggle; };

void Channel::setTopicRestrict(bool toggle) { _topicRestricted = toggle; };

void Channel::setPwRequired(bool toggle) { _pwRequired = toggle; };

void Channel::setClientLimited(bool toggle) { _clientLimited = toggle; };

void Channel::setLimit(int limit) { _limit = limit; };

void Channel::addClient(Client *client) {
	_clients.insert(make_pair(client->getNickname(), client));
};

void Channel::rmClient(const string &name) {
	_clients.erase(name);
	this->rmOperator(name);
};

void Channel::addOperator(const string &nick) {
	_ops.push_back(nick);
};

void Channel::rmOperator(const string &nick) {
	vector<string>::iterator it;
	for (it = _ops.begin(); it != _ops.end(); ++it) {
		if (*it == nick) {
			_ops.erase(it);
			return ;
		}
	}
	return ;
};

void Channel::addInvite(const string &nick) {
	_invites.push_back(nick);
};

bool Channel::searchClient(const string &nick) {
	return _clients.count(nick) > 0;
};

bool Channel::searchOperator(const string &nick) {
	vector<string>::iterator it;
	for (it = _ops.begin(); it != _ops.end(); it++) {
		if (*it == nick)
			return true;
	}
	return false;
};

bool Channel::searchInvite(const string &nick) {
	vector<string>::iterator it;
	for (it = _invites.begin(); it != _invites.end(); it++) {
		if (*it == nick)
			return true;
	}
	return false;
};

void Channel::kickClient(Client *op, Client *target) {
	string opName = op->getNickname();
	string chName = op->getChannel()->getName();
	string tName = target->getNickname();
	this->broadcast(op, RPL_KICK(opName, chName, tName), false);
	target->setChannel(NULL);
	this->rmClient(target->getNickname());
	target->setClientState(REGISTERED);
};

void Channel::broadcast(Client *client, string input, bool isMsg) {
	string broadcastMessage = isMsg ? client->getNickname() + ": " + input :\
									client->getInfo() + ": " + input + "\r\n";
	map<string, Client *>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); ++it) {
		if (it->second == client)
			continue;
		int clientSockfd = it->second->getSockfd();
		send(clientSockfd, broadcastMessage.c_str(), broadcastMessage.length(), 0);
	}
};
