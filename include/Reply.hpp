/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:46:05 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/13 17:05:03 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Error reply */
#define ERR_NOSUCHNICK(nick)			"401 " + nick + " :No such nick/channel"
#define ERR_NOSUCHCHANNEL(channel)		"403 " + channel + " :No such channel"
#define ERR_CANNOTSENDTOCHAN(channel)	"404 " + channel + " :Cannot send to channel"
#define ERR_NOTEXTTOSEND(cmd)			"412 " + cmd + " :No text to send"
#define ERR_UNKNOWNCOMMAND(cmd)			"421 " + cmd + " :Unknown command"
#define ERR_NONICKNAMEGIVEN()			"431 :No nickname given"
#define ERR_NICKNAMEINUSE(nick)			"433 " + nick + " :Nickname is already in use"
#define ERR_NOTREGISTERED(nick)			"451 " + nick + " :You have not registered"
#define ERR_NEEDMOREPARAMS(nick, cmd)	"461 " + nick + " " + cmd + " :Not enough parameters"
#define ERR_ALREADYREGISTRED(nick)		"462 " + nick + " :You may not reregister"
#define ERR_PASSWDMISMATCH(nick)		"464 " + nick + " :Password incorrect"
#define ERR_BADCHANNELKEY(channel)		"475" + channel + " :Password incorrect"

/* reply */
#define RPL_WELCOMEMSG(names)			"001 :Welcome to the ft_irc Network"
#define RPL_JOIN(nick, chName)			nick + " has joined " + chName