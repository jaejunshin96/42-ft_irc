/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:09:24 by jaeshin           #+#    #+#             */
/*   Updated: 2024/02/26 18:20:54 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>

#include "Channel.hpp"

using namespace std;

class Channel;

class Client {
	private:
		string _name;
		vector<Channel> _channels;

	public:
		Client();
		Client(string name);
		~Client();

		string getName() const;
		vector<Channel> getChannels() const;

		void setName(string newName);
		void addChannel(Channel channel);
		void rmChannel(Channel channel);
};
