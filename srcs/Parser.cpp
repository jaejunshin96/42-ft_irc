/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:39:24 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/27 15:06:56 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Parser.hpp"

Parser::Parser(Server *server): _server(server) {
	// server cmds
	_cmds["PASS"] = new Pass(_server, false);
	_cmds["NICK"] = new Nick(_server, false);
	_cmds["USER"] = new User(_server, false);
	_cmds["QUIT"] = new Quit(_server, false);
	_cmds["JOIN"] = new Join(_server, true);
	_cmds["PART"] = new Part(_server, true);
	_cmds["PRIVMSG"] = new Privmsg(_server, true);
	// channel cmds
	_cmds["MODE"] = new Mode(_server, true);
	_cmds["KICK"] = new Kick(_server, true);
	_cmds["INVITE"] = new Invite(_server, true);
	_cmds["TOPIC"] = new Topic(_server, true);
};

Parser::~Parser() {
	map<string, Command *>::iterator it;
	for (it = _cmds.begin(); it != _cmds.begin(); it++) {
		delete it->second;
	}
};

string toUpper(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

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

	string cmd = toUpper(tokens[0]);

	if (_cmds[cmd]) {
		if (!client->isRegistered() && _cmds[cmd]->authRequired()) {
			client->reply(ERR_NOTREGISTERED(client->getNickname()));
			return ;
		}
		_cmds[cmd]->execute(client, tokens);
	} else {
		if (client->getClientState() == JOINED) {
			client->getChannel()->broadcast(client, input, true);
			return ;
		} else {
			client->reply(ERR_UNKNOWNCOMMAND(cmd));
			return ;
		}
	}
};
