/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:40:29 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/16 19:22:34 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Command.hpp"

Quit::Quit(Server *server, bool auth): Command(server, auth) {};

Quit::~Quit() {};

void Quit::execute(Client *client, vector<string> args) {
	(void)args;
	Channel *channel = client->getChannel();
	if (channel) {
		string name = channel->getName();
		client->leave(_server, channel, name);
		delete channel;
	}
	_server->disconnectClient(client->getSockfd());
};
