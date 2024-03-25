/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:34:04 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/24 21:18:52 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP

#include "Server.hpp"
#include "Command.hpp"

using namespace std;

class Server;
class Client;
class Command;

class Parser {
	private:
		Server *_server;
		map<string, Command *> _cmds;

	public:
		Parser(Server *server);
		~Parser();

		void parse(Client *client, string &input);
};

#endif
