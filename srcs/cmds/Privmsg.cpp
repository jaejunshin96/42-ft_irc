/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 22:50:11 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/18 21:09:47 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Command.hpp"

Privmsg::Privmsg(Server *server, bool auth): Command(server, auth) {};

Privmsg::~Privmsg() {};

void Privmsg::execute(Client *client, vector<string> args) {
	Client *targetClient;
	Channel *targetChannel;

	targetClient = _server->searchClient(args[1]);
	targetChannel = _server->searchChannel(args[1]);

	if (args.size() < 2) {
		client->reply(ERR_NORECIPIENT);
		return ;
	} else if (!targetClient && !targetChannel) {
		client->reply(ERR_NOSUCHNICK(args[1]));
		return ;
	}

	client->privmsg(targetClient, targetChannel, args);
};
