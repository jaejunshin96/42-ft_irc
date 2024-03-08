/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:19:03 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/07 16:44:26 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Command.hpp"

Nick::Nick(Server *server, bool auth): Command(server, auth) {};

Nick::~Nick() {};

void Nick::execute(Client *client, vector<string> args) {
	if (client->getClientState() == HANDSHAKE) {
		client->reply(client->getNickname() + " :PASS should come first");
		return ;
	} else if (args.size() != 2) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "NICK"));
		return ;
	} else {
		map<int, Client *> temp = _server->getClients();
		map<int, Client *>::iterator it = temp.begin();
		while (it != temp.end()) {
			if (it->second->getNickname() == args[1]) {
				client->reply(ERR_NICKNAMEINUSE(client->getNickname()));
				return ;
			}
			it++;
		}
	}
	client->setNickname(args[1]);
	if (client->getClientState() == PWCHECKED)
		client->setClientState(NICKCHECKED);
	cout << args[0] << " " << args[1] << endl;
};
