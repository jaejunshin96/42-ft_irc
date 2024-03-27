/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:44:07 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/27 16:08:59 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Command.hpp"

Kick::Kick(Server *server, bool auth): Command(server, auth) {};

Kick::~Kick() {};

void Kick::execute(Client *client, vector<string> args) {
	Channel *channel = client->getChannel();
	if (args.size() < 3) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "KICK"));
		return ;
	} else if (!channel->searchOperator(client->getNickname())) {
		client->reply(ERR_CHANOPRIVSNEEDED(channel->getName()));
		return ;
	} else if (channel->getName() != args[1]) {
		client->reply(ERR_NOTONCHANNEL(channel->getName()));
		return ;
	} else if (!channel->searchClient(args[2])) {
		client->reply(ERR_NOSUCHNICK(args[2]));
		return ;
	}

	if (channel->getClients().count(args[2]) > 0) {
		Client *targetClient = channel->getClients().at(args[2]);
		channel->kickClient(client, targetClient);
	}
};
