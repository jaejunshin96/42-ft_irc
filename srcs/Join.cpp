/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:07:45 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/12 23:52:10 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Command.hpp"

Join::Join(Server *server, bool auth): Command(server, auth) {};

Join::~Join() {};

void Join::execute(Client *client, vector<string> args) {
	if (args.size() < 2) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "JOIN"));
		return ;
	}

	string name = args[1];
	if (_server->getChannels()[name]) {
		Channel *chToJoin = _server->getChannels()[name];
		client->setChannel(chToJoin);
		chToJoin->addClient(client);
		client->reply(RPL_JOIN(client->getNickname(), name));
		client->setClientState(JOINED);
		return ;
	}
	string password = args.size() > 2 ? args[2] : "";
	Channel *newChannel = new Channel(name, password);

	client->setChannel(newChannel);
	newChannel->addClient(client);
	_server->addChannel(newChannel);
	client->reply(RPL_JOIN(client->getNickname(), name));
	client->setClientState(JOINED);
};
