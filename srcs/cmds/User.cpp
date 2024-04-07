/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:21:41 by jaeshin           #+#    #+#             */
/*   Updated: 2024/04/06 20:43:39 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Command.hpp"

User::User(Server *server, bool auth): Command(server, auth) {};

User::~User() {};

void User::execute(Client *client, vector<string> args) {
	size_t argSize = args.size();
	if (client->isRegistered()) {
		client->reply(ERR_ALREADYREGISTRED(client->getNickname()));
		return ;
	}else if (client->getClientState() == HANDSHAKE ||\
		 		client->getClientState() == PWCHECKED) {
		client->reply(client->getNickname() + " :PASS/NICK should come first");
		return ;
	} else if (argSize < 5 || args[4][0] != ':') {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "USER") + \
			"\nUSER <username> <hostname> <servername> :<realname>");
		return ;
	}

	client->setUsername(args[1]);
	client->setHostname(args[2]);
	size_t i = 4;
	string realname;
	while (i < argSize) {
		if ((i + 1) == argSize) {
			realname += args[i];
		} else {
			realname += args[i] + " ";
		}
		i++;
	}
	client->setRealname(realname);
	client->setClientState(REGISTERED);
	client->reply(RPL_WELCOMEMSG);

	cout << args[1] << " has been registred." << endl;
};
