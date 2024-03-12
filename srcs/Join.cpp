/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:07:45 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/11 16:41:49 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Command.hpp"

Join::Join(Server *server, bool auth): Command(server, auth) {};

Join::~Join() {};

void Join::execute(Client *client, vector<string> args) {
	if (args.size() < 2) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "JOIN"));
		return ;
	} else if (authRequired() && (client->getClientState() != REGISTERED)) {
		client->reply(ERR_NOTREGISTERED(client->getNickname()));
		return ;
	} // start to finish join func
};
