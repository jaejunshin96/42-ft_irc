/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:54:57 by jaeshin           #+#    #+#             */
/*   Updated: 2024/02/26 19:26:46 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // For inet_addr()

#include "Channel.hpp"
#include "Client.hpp"

using namespace std;

class Channel;
class Client;

class Server {
	private:
		vector<Client> _clients;
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
};
