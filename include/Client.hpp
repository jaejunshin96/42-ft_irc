/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:09:24 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/05 14:54:03 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <vector>

#include "Channel.hpp"

using namespace std;

class Channel;

enum ClientState {
	 HANDSHAKE,
	 LOGIN,
	 REGISTERED,
	 DISCONNECTED
};

class Client {
	private:
		int _sockfd;
		int _port;

		string _hostname;
		string _nickname;
		string _username;

		ClientState _clientState;
		vector<Channel> _channels;

		Client();

	public:
		Client(int sockfd, int port, string hostname);
		~Client();

		int getSockfd() const;
		int getPort() const;

		string getHostname() const;
		string getNickname() const;
		string getUsername() const;

		ClientState getClientState() const;
		vector<Channel> getChannels() const;

		void setNickname(string newNick);
		void setClientState(ClientState state);
};

#endif
