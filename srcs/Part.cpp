/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:46:12 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/14 22:48:46 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Command.hpp"

Part::Part(Server *server, bool auth): Command(server, auth) {};

Part::~Part() {};

void Part::execute(Client *client, vector<string> args) {
	if (args.size() < 2) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "PART"));
		return ;
	}

	string chName = args[1];
	Channel *chToLeave = _server->getChannels()[chName];
	if (!chToLeave || !client->getChannel() || chToLeave != client->getChannel()) {
		client->reply(ERR_NOSUCHCHANNEL(chName));
		return ;
	}

	// leave
	client->leave(_server, chToLeave, chName);
};
