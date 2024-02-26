/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:38:00 by jaeshin           #+#    #+#             */
/*   Updated: 2024/02/26 19:41:49 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Client.hpp"

Client::Client() {};

Client::Client(string name): _name(name) {};

Client::~Client() {};

string Client::getName() const {
	return _name;
};

vector<Channel> Client::getChannels() const {
	return _channels;
};

void Client::setName(string newName) {
	_name = newName;
};
