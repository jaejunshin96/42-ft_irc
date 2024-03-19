/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:00:21 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/19 23:33:24 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <vector>

#include "Server.hpp"
#include "Client.hpp"

using namespace std;

class Server;
class Client;

class Channel {
	private:
		string _name;
		string _password;

		bool _inviteOnly;

		map<string, Client *> _clients;
		vector<string> _ops;

	public:
		Channel();
		Channel(string &name, string &password);
		~Channel();

		string getName() const;
		string getPassword() const;
		bool getInviteState() const;
		map<string, Client *> getClients() const;
		vector<string> getOperators() const;

		void setName(string &newName);
		void setInviteStatus(bool toggle);

		void addClient(Client *client);
		void rmClient(const string &name);

		void addOperator(const string &nick);
		void rmOperator(const string &nick);
		bool searchOperator(const string &nick);

		void broadcast(Client *client, string input, bool isMsg);
};

#endif
