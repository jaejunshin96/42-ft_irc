/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:35:13 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/05 19:19:28 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Command.hpp"

Pass::Pass(Server *server, bool auth): Command(server, auth) {};

Pass::~Pass() {};

void Pass::execute(Client *client, vector<string> args) {
	(void)client;
	if (args.size() != 2) {
		throw runtime_error("Error: PASS wrong arguments.");
	}
};
