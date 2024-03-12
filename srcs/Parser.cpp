/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:39:24 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/11 16:32:00 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Parser.hpp"

Parser::Parser(Server *server): _server(server) {
	_cmds["PASS"] = new Pass(_server, false);
	_cmds["NICK"] = new Nick(_server, false);
	_cmds["USER"] = new User(_server, false);
	_cmds["JOIN"] = new Join(_server, true);
};

Parser::~Parser() {};

void Parser::parse(Client *client, string &input) {
	string trimmedStr;
	size_t start = input.find_first_not_of(" \t\n\r");
	size_t end = input.find_last_not_of(" \t\n\r");
	if (start == string::npos)
		return ;
	trimmedStr = input.substr(start, end + 1);

	vector<string> tokens;
	stringstream ss(trimmedStr);
	string token;
	while (ss >> token) {
		tokens.push_back(token);
	}

	if (_cmds[tokens[0]]) {
		if (!client->isRegistered() && _cmds[tokens[0]]->authRequired()) {
			client->reply(ERR_NOTREGISTERED(client->getNickname()));
			return ;
		}
		_cmds[tokens[0]]->execute(client, tokens);
	} else {
		client->reply(ERR_UNKNOWNCOMMAND(tokens[0]));
		return ;
	}
};
