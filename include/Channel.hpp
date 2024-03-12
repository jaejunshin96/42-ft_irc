/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:00:21 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/11 15:58:09 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <vector>

#include "Server.hpp"
#include "Client.hpp"

using namespace std;

class Client;

class Channel {
	private:
		string _name;
		vector<Client *> _clients;

	public:
		Channel();
		Channel(string name);
		~Channel();

		string getName() const;
		vector<Client *> getClients() const;

		void setName(string &newName);
		Channel *createChannel(string &channelName);
		void addClient(Client *client);
};

#endif
