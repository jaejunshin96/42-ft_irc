/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:21:41 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/06 18:06:20 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Command.hpp"

User::User(Server *server, bool auth): Command(server, auth) {};

User::~User() {};

void User::execute(Client *client, vector<string> args) {
	size_t argSize = args.size();
	if (client->getClientState() == HANDSHAKE ||\
		 client->getClientState() == PWCHECKED)
		throw runtime_error("Error: PASS and NICK should come first.");
	else if (argSize < 5 || args[4][0] != ':') {
		throw runtime_error("Error: USER <username> <hostname> \
			<servername> :<realname>");
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
	cout << args[0] << " " << client->getUsername() << " " << client->getHostname() \
		<< " " << args[3] << " " << client->getRealname() << endl;
};