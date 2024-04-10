/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:46:05 by jaeshin           #+#    #+#             */
/*   Updated: 2024/04/10 19:51:24 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Error */
#define ERR_NOSUCHNICK(nick)				"401 " + nick + " :No such nick/channel"
#define ERR_NOSUCHCHANNEL(channel)			"403 " + channel + " :No such channel"
#define ERR_CANNOTSENDTOCHAN(channel)		"404 " + channel + " :Cannot send to channel"
#define ERR_TOOMANYCHANNELS(nick, channel)	"405 " + nick + " " + channel + " :You have joined too many channels"
#define ERR_NORECIPIENT						"411 PRIVMSG :No recipient is given"
#define ERR_NOTEXTTOSEND(cmd)				"412 " + cmd + " :No text to send"
#define ERR_UNKNOWNCOMMAND(cmd)				"421 " + cmd + " :Unknown command"
#define ERR_NONICKNAMEGIVEN					"431 :No nickname given"
#define ERR_NICKNAMEINUSE(nick)				"433 " + nick + " :Nickname is already in use"
#define ERR_NOTONCHANNEL(nick)				"442 " + nick + " :You are not on a channel"
#define ERR_USERONCHANNEL(channel, client)	"443 " + channel + " :" + client + " Already on the channel"
#define ERR_NOTREGISTERED(nick)				"451 " + nick + " :You have not registered"
#define ERR_NEEDMOREPARAMS(nick, cmd)		"461 " + nick + " " + cmd + " :Not enough parameters"
#define ERR_ALREADYREGISTRED(nick)			"462 " + nick + " :You may not reregister"
#define ERR_PASSWDMISMATCH(nick)			"464 " + nick + " :Password incorrect"
#define ERR_CHANNELISFULL(channel)			"471 " + channel + " :Cannot join channel (+l)"
#define ERR_INVITEONLYCHAN(channel)			"473 " + channel + " :Cannot join channel (+i)"
#define ERR_BADCHANNELKEY(channel)			"475 " + channel + " :Channel password incorrect"
#define ERR_CHANOPRIVSNEEDED(channel)		"482 " + channel + " :You're not channel operator"

/* reply */
#define RPL_WELCOMEMSG						":Welcome to the ft_irc Network"
#define RPL_JOIN(nick, channel)				nick + " JOIN " + channel
#define RPL_PART(nick, channel)				nick + " PART " + channel
#define RPL_KICK(nick, channel, target)		nick + " KICK " + target + " from " + channel
#define RPL_INVITE(nick, target, channel)	nick + " INVITE " + target + " to " + channel
#define RPL_TOPIC(channel, topic)			channel + " :" + topic
#define RPL_NOTOPIC(channel)				channel + " :No topic"
#define RPL_MODE(flag)						"MODE " + flag
