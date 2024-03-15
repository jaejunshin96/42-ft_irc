/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:36:23 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/15 11:24:02 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Command.hpp"

Command::Command() {};

Command::Command(Server *server, bool auth): _server(server), _auth(auth) {};

Command::~Command() {};

bool Command::authRequired() const {
	return _auth;
}
