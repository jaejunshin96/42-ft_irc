/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:55:52 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/25 16:31:16 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Command.hpp"

Invite::Invite(Server *server, bool auth): Command(server, auth) {};

Invite::~Invite() {};

void Invite::execute(Client *client, vector<string> args) {
	Channel *channel = client->getChannel();
	if (args.size() < 3) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "INVITE"));
		return ;
	} else if (!channel->searchOperator(client->getNickname())) {
		client->reply(ERR_CHANOPRIVSNEEDED(channel->getName()));
		return ;
	} else if (!_server->searchClient(args[1])) {
		client->reply(ERR_NOSUCHNICK(args[1]));
		return ;
	} else if (channel->searchClient(args[1])) {
		client->reply(ERR_USERONCHANNEL(channel->getName(), args[1]));
		return ;
	}
	Client *target = _server->searchClient(args[1]);
	channel->addInvite(args[1]);
	target->reply(RPL_INVITE(client->getNickname(), args[1], args[2]));
	return ;
};
