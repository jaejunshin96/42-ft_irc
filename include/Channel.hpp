/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:00:21 by jaeshin           #+#    #+#             */
/*   Updated: 2024/02/26 18:19:51 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>

#include "Client.hpp"

using namespace std;

class Client;

class Channel {
	private:
		string _name;
		vector<Client> _clients;

	public:
		Channel();
		Channel(string name);
		~Channel();

		string getName() const;
		vector<Client> getClients() const;

		void setName(string newName);
		void addClient(Client newClient);
		void rmClient(Client client);
};
