/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:38:03 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/12 23:38:22 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Channel.hpp"

Channel::Channel() {};

Channel::Channel(string &name, string &password): _name(name), _password(password) {};

Channel::~Channel() {};

/* getters */
string Channel::getName() const { return _name; };

string Channel::getPassword() const { return _password; };

map<string, Client *> Channel::getClients() const { return _clients; };

/* setters */
void Channel::setName(string &newName) { _name = newName; };

void Channel::addClient(Client *client) {
	_clients.insert(make_pair(client->getNickname(), client));
};
