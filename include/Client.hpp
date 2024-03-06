/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:09:24 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/06 17:49:37 by jaeshin          ###   ########.fr       */
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
	 PWCHECKED,
	 NICKCHECKED,
	 REGISTERED,
	 DISCONNECTED
};

class Client {
	private:
		int _sockfd;
		int _port;

		string _nickname;
		string _username;
		string _hostname;
		string _realname;

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
		string getRealname() const;

		ClientState getClientState() const;
		vector<Channel> getChannels() const;

		void setNickname(string newNick);
		void setUsername(string newUser);
		void setHostname(string newHost);
		void setRealname(string newReal);
		void setClientState(ClientState state);
};

#endif
