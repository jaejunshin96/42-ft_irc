/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:19:03 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/06 16:19:50 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Command.hpp"

Nick::Nick(Server *server, bool auth): Command(server, auth) {};

Nick::~Nick() {};

void Nick::execute(Client *client, vector<string> args) {
	if (client->getClientState() == HANDSHAKE)
		throw runtime_error("Error: PASS should come first.");
	else if (args.size() != 2) {
		throw runtime_error("Error: NICK <nickname>");
	} else {
		map<int, Client *> temp = _server->getClients();
		map<int, Client *>::iterator it = temp.begin();
		while (it != temp.end()) {
			if (it->second->getNickname() == args[1]) {
				throw runtime_error("Error: Nick already been taken.");
			}
			it++;
		}
	}
	client->setNickname(args[1]);
	if (client->getClientState() == PWCHECKED)
		client->setClientState(NICKCHECKED);
	cout << args[0] << " " << args[1] << endl;
};