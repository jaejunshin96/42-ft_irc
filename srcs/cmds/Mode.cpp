/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 21:10:32 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/25 16:31:23 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Command.hpp"

Mode::Mode(Server *server, bool auth): Command(server, auth) {};

Mode::~Mode() {};

void Mode::execute(Client *client, vector<string> args) {
	/* Handles MODE error */
	Channel *channel = client->getChannel();
	if (args.size() < 2) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"));
		return ;
	} else if (!channel) {
		client->reply(ERR_NOTONCHANNEL(channel->getName()));
		return ;
	} else if (!channel->searchOperator(client->getNickname())) {
		client->reply(ERR_CHANOPRIVSNEEDED(channel->getName()));
		return ;
	}

	/* Handles MODE flags */
	//i - invite, t - topic, k - password, o - operator privilege, l - limit
	if (args[1] == "-i" || args[1] == "+i") {
		args[1] == "-i" ? channel->setInviteStatus(false) :\
							channel->setInviteStatus(true);
		channel->broadcast(client, RPL_MODE(args[1]), false);
		return ;
	} else if (args[1] == "-t" || args[1] == "+t") {
		args[1] == "-t" ? channel->setTopicRestrict(false) :\
							channel->setTopicRestrict(true);
		channel->broadcast(client, RPL_MODE(args[1]), false);
		return ;
	} else if (args[1] == "-k" || args[1] == "+k") {
		args[1] == "-k" ? channel->setPwRequired(false) :\
							channel->setPwRequired(true);
		channel->broadcast(client, RPL_MODE(args[1]), false);
		return ;
	} else if (args[1] == "-o" || args[1] == "+o") {
		if (args.size() < 3) {
			client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), ("MODE " + args[1])));
			return ;
		} else if (!channel->getClients()[args[2]]) {
			client->reply(ERR_NOSUCHNICK(args[2]));
			return ;
		}

		if (args[1] == "-o") {
			if (channel->searchOperator(args[2]))
				channel->rmOperator(args[2]);
		} else if (args[1] == "+o") {
			if (!channel->searchOperator(args[2]))
				channel->addOperator(args[2]);
		}
		channel->broadcast(client, RPL_MODE(args[1]) + " " + args[2], false);
		return ;
	} else if (args[1] == "-l" || args[1] == "+l") {
		if (args[1] == "-l") {
			channel->setClientLimited(false);
			channel->broadcast(client, RPL_MODE(args[1]), false);
		} else if (args[1] == "+l") {
			if (args.size() < 3) {
				client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"));
				return ;
			}
			channel->setClientLimited(true);
			if (args.size() == 3) {
				for (size_t i = 0; i != args[2].length(); ++i) {
					if (!isdigit(args[2][i]))
						return ;
				}
				int limit = atoi(args[2].c_str());
				channel->setLimit(limit);
			}
			channel->broadcast(client, RPL_MODE(args[1]) + " " + args[2], false);
		}
		return ;
	} else {
		client->reply(ERR_UNKNOWNCOMMAND(args[0] + " " + args[1]));
		return ;
	}
};

