/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:00:37 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/22 16:15:23 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Command.hpp"

Topic::Topic(Server *server, bool auth): Command(server, auth) {};

Topic::~Topic() {};

void Topic::execute(Client *client, vector<string> args) {
	size_t argSize = args.size();
	if (argSize < 2) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "TOPIC"));
		return ;
	}
	Channel *channel = client->getChannel();
	if (argSize == 2) {
		if (channel->getName() != args[1]) {
			client->reply(ERR_NOTONCHANNEL(channel->getName()));
			return ;
		}
		// view topic.
	}
	
	if (argSize >= 3) {
		if (channel->getName() != args[1]) {
			client->reply(ERR_NOTONCHANNEL(channel->getName()));
			return ;
		} else if (!channel->searchOperator(client->getNickname())) {
			client->reply(ERR_CHANOPRIVSNEEDED(channel->getName()));
			return ;
		}
		
		// set new topic.
	}
};