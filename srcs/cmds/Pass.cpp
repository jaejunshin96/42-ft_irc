/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:35:13 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/25 16:31:46 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Command.hpp"

Pass::Pass(Server *server, bool auth): Command(server, auth) {};

Pass::~Pass() {};

void Pass::execute(Client *client, vector<string> args) {
	if (client->isRegistered()) {
		client->reply(ERR_ALREADYREGISTRED(client->getNickname()));
		return ;
	} else if (args.size() < 2) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "PASS"));
		return ;
	} else if (args[1] != _server->getPassword()) {
		client->reply(ERR_PASSWDMISMATCH(client->getNickname()));
		return ;
	}
	if (client->getClientState() == HANDSHAKE)
		client->setClientState(PWCHECKED);
	cout << args[0] << " " << args[1] << endl;
};
