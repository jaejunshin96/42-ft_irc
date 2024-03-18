/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 22:50:11 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/18 18:18:00 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Command.hpp"

Privmsg::Privmsg(Server *server, bool auth): Command(server, auth) {};

Privmsg::~Privmsg() {};

void Privmsg::execute(Client *client, vector<string> args) {
	Client *targetClient;
	Channel *targetChannel;

	targetClient = _server->searchClient(args[1]);
	if (args[1][0] == '#') {
		string chName = args[1].substr(1);
		targetChannel = _server->searchChannel(chName);
	}

	if (args.size() < 2) {
		client->reply(ERR_NORECIPIENT);
		return ;
	} else if (args[1][0] != '#' && !targetClient) {
		client->reply(ERR_NOSUCHNICK(args[1]));
		return ;
	} else if (args[1][0] == '#' && !targetChannel) {
		client->reply(ERR_NOSUCHCHANNEL(args[1]));
		return ;
	}
	
	client->privmsg(targetClient, targetChannel, args);
};
