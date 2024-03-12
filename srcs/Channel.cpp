/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:38:03 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/11 15:45:31 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Channel.hpp"

Channel::Channel() {};

Channel::Channel(string name): _name(name) {};

Channel::~Channel() {};

string Channel::getName() const { return _name; };

vector<Client *> Channel::getClients() const { return _clients; };

void Channel::setName(string &newName) { _name = newName; };

Channel *Channel::createChannel(string &channelName) {
	Channel *newChannel = new Channel(channelName);

	return newChannel;
};

void Channel::addClient(Client *client) {
	_clients.push_back(client);
};
