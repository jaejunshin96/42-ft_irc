/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:35:13 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/06 16:18:32 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Command.hpp"

Pass::Pass(Server *server, bool auth): Command(server, auth) {};

Pass::~Pass() {};

void Pass::execute(Client *client, vector<string> args) {
	if (args.size() != 2) {
		throw runtime_error("Error: PASS <password>");
	} else if (args[1] != _server->getPassword()) {
		throw runtime_error("Error: Wrong password.");
	} else if (client->getClientState() == REGISTERED) {
		throw runtime_error("Error: Already registered.");
	}
	if (client->getClientState() == HANDSHAKE)
		client->setClientState(PWCHECKED);
	cout << args[0] << " " << args[1] << endl;
};
