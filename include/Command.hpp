/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:59:48 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/05 19:11:31 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Server.hpp"

class Server;
class Client;

/* Abstract Class */
class Command {
	protected:
		Server *_server;
		bool _auth;

		Command();
	public:
		Command(Server *server, bool auth);
		virtual ~Command();

		virtual void execute(Client *client, vector<string> args) = 0;
};

/* Child Class */
class Pass : public Command {
	public:
		Pass(Server *server, bool auth);
		~Pass();

		void execute(Client *client, vector<string> args);
};

#endif

