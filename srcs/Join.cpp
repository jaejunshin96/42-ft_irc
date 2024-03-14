/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:07:45 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/13 22:53:20 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Command.hpp"

Join::Join(Server *server, bool auth): Command(server, auth) {};

Join::~Join() {};

void Join::execute(Client *client, vector<string> args) {
	if (client->getClientState() == JOINED) {
		client->reply(ERR_TOOMANYCHANNELS(client->getNickname(), "JOIN"));
		return ;
	} else if (args.size() < 2) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "JOIN"));
		return ;
	}

	string name = args[1];
	string password = args.size() > 2 ? args[2] : "";
	Channel *chToJoin = _server->getChannels()[name];
	if (chToJoin) {
		if (_server->getChannels()[name]->getPassword() == password) {
			client->join(_server, chToJoin, name, true);
		} else if (_server->getChannels()[name]->getPassword() != password) {
			client->reply(ERR_BADCHANNELKEY(chToJoin->getName()));
		}
		return ;
	}

	Channel *newChannel = new Channel(name, password);
	client->join(_server, newChannel, name, false);
};
