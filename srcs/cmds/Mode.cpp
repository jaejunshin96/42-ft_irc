/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 21:10:32 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/19 23:36:24 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Command.hpp"

Mode::Mode(Server *server, bool auth): Command(server, auth) {};

Mode::~Mode() {};

void Mode::execute(Client *client, vector<string> args) {
	Channel *channel = client->getChannel();
	if (args.size() < 2) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"));
		return ;
	} else if (!channel) {
		client->reply(ERR_NOTONCHANNEL);
		return ;
	} else if (!channel->searchOperator(client->getNickname())) {
		client->reply(ERR_CHANOPRIVSNEEDED);
		return ;
	}

	//if (args[1] == "-i") {
	//	if (client)
	//}
};

