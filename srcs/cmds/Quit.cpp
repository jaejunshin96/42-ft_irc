/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:40:29 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/15 13:27:14 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Command.hpp"

Quit::Quit(Server *server, bool auth): Command(server, auth) {};

Quit::~Quit() {};

void Quit::execute(Client *client, vector<string> args) {
	(void)args;
	Channel *channel = client->getChannel();
	if (channel) {
		cout << "here?" << endl;
		string name = channel->getName();
		client->leave(_server, channel, name);
	}

	// _server->disconnectClient(client->getSockfd());
};
