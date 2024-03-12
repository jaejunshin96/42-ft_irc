/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:00:21 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/12 17:28:15 by jaeshin          ###   ########.fr       */
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
		string _password;
		vector<Client *> _clients;

	public:
		Channel();
		Channel(string &name, string &password);
		~Channel();

		string getName() const;
		string getPassword() const;
		vector<Client *> getClients() const;

		void setName(string &newName);
		
		void addClient(Client *client);
};

#endif
