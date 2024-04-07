/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:54:57 by jaeshin           #+#    #+#             */
/*   Updated: 2024/04/07 20:45:56 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <fcntl.h>
#include <signal.h>

#include <algorithm>
#include <vector>
#include <map>

#include <sys/socket.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h> // For inet_addr()

#include "Channel.hpp"
#include "Client.hpp"
#include "Parser.hpp"
#include "Command.hpp"

using namespace std;

class Channel;
class Client;
class Parser;
class Command;

typedef vector<pollfd>::iterator pfd_iterator;

class Server {
	private:
		int _port;
		string _password;

		static int _listening;
		int _serverFd;

		vector<pollfd> _pfds;
		map<int, Client *> _clients;
		map<string, Channel *> _channels;
		Parser *_parser;

	public:
		Server(const string &port, const string &password);
		~Server();

		int getPort() const;
		string getPassword() const;
		map<int, Client *> getClients() const;
		map<string, Channel *> getChannels() const;

		Client *searchClient(string &name);
		Channel *searchChannel(string &name);

		void addChannel(Channel *newChannel);
		void rmChannel(string &chName);

		int createServer(int port);
		void startServer(void);

		void disconnectClient(int fd);
		void connectClient(void);

		string readInput(int fd);
		void handleInput(int fd);

		static void signalHandler(int signum);
};

#endif
