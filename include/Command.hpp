/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:59:48 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/21 13:43:39 by jaeshin          ###   ########.fr       */
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

		bool authRequired() const;

		virtual void execute(Client *client, vector<string> args) = 0;
};

/* Child Class */
class Pass: public Command {
	public:
		Pass(Server *server, bool auth);
		~Pass();

		void execute(Client *client, vector<string> args);
};

class Nick: public Command {
	public:
		Nick(Server *server, bool auth);
		~Nick();

		void execute(Client *client, vector<string> args);
};

class User: public Command {
	public:
		User(Server *server, bool auth);
		~User();

		void execute(Client *client, vector<string> args);
};

class Join: public Command {
	public:
		Join(Server *server, bool auth);
		~Join();

		void execute(Client *client, vector<string> args);
};

class Part: public Command {
	public:
		Part(Server *server, bool auth);
		~Part();

		void execute(Client *client, vector<string> args);
};

class Quit: public Command {
	public:
		Quit(Server *server, bool auth);
		~Quit();

		void execute(Client *client, vector<string> args);
};

class Privmsg: public Command {
	public:
		Privmsg(Server *server, bool auth);
		~Privmsg();

		void execute(Client *client, vector<string> args);
};

class Mode: public Command {
	public:
		Mode(Server *server, bool auth);
		~Mode();

		void execute(Client *client, vector<string> args);
};

class Kick: public Command {
	public:
		Kick(Server *server, bool auth);
		~Kick();

		void execute(Client *client, vector<string> args);
};

#endif
