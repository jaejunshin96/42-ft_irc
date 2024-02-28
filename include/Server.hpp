/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:54:57 by jaeshin           #+#    #+#             */
/*   Updated: 2024/02/28 19:24:15 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <unistd.h>
#include <cstring>

#include <algorithm>
#include <vector>
#include <map>

#include <sys/socket.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <arpa/inet.h> // For inet_addr()

#include "Channel.hpp"
#include "Client.hpp"

using namespace std;

class Channel;
class Client;

typedef vector<pollfd>::iterator pfd_iterator;

class Server {
	private:
		int _listening;
		int _serverFd;

		vector<pollfd> _pfds;
		map<int, Client *> _clients;
		vector<Channel> _channels;

	public:
		Server();
		~Server();

		vector<Client> getClients() const;
		vector<Channel> getChannels() const;

		void addClient(string name);
		void rmClient(Client client);
		void addChannel(string name);
		void rmChannel(Channel channel);

		int createServer(int port);

		void start(void);

		void disconnectClient(int fd);
		void connectClient(void);
		void message(int fd);
};
