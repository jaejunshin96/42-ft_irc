/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:09:24 by jaeshin           #+#    #+#             */
/*   Updated: 2024/04/07 20:46:09 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <vector>

#include "Server.hpp"
#include "Channel.hpp"
#include "Reply.hpp"

using namespace std;

class Server;
class Channel;

enum ClientState {
	 HANDSHAKE,
	 PWCHECKED,
	 NICKCHECKED,
	 REGISTERED,
	 JOINED,
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
		Channel *_channel;

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
		string getInfo() const;
		ClientState getClientState() const;
		Channel *getChannel() const;

		void setNickname(string newNick);
		void setUsername(string newUser);
		void setHostname(string newHost);
		void setRealname(string newReal);
		void setClientState(ClientState state);
		void setChannel(Channel *channel);

		bool isRegistered() const;

		void writeMsg(const string &message);
		void reply(const string &message);
		void join(Server *server, Channel *channel, string &name, bool isExisting);
		void leave(Server *server, Channel *channel, string &name);
		void privmsg(Client *tClient, Channel *tChannel, vector<string> input);
};

#endif
