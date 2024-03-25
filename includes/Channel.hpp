/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:00:21 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/22 16:11:30 by jaeshin          ###   ########.fr       */
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

		map<string, Client *> _clients;
		vector<string> _ops;
		vector<string> _invites;
		string _topic;

		bool _inviteOnly;
		bool _topicRestricted;
		bool _pwRequired;
		bool _clientLimited;
		int _limit;

	public:
		Channel();
		Channel(string &name, string &password);
		~Channel();

		string getName() const;
		string getPassword() const;
		map<string, Client *> getClients() const;
		vector<string> getOperators() const;
		vector<string> getInvites() const;
		string getTopic() const;
		bool getInviteState() const;
		bool getTopicRestrict() const;
		bool getPwRequired() const;
		bool getClientLimited() const;
		int getLimit() const;
		int getClientSize() const;

		void setName(string &newName);
		void setTopic(string &newTopic);
		void setInviteStatus(bool toggle);
		void setTopicRestrict(bool toggle);
		void setPwRequired(bool toggle);
		void setClientLimited(bool toggle);
		void setLimit(int limit);

		void addClient(Client *client);
		void rmClient(const string &name);

		void addOperator(const string &nick);
		void rmOperator(const string &nick);
		
		void addInvite(const string &nick);
		
		bool searchClient(const string &nick);
		bool searchOperator(const string &nick);
		bool searchInvite(const string &nick);
		
		void kickClient(Client *op, Client *target);

		void broadcast(Client *client, string input, bool isMsg);
};

#endif
