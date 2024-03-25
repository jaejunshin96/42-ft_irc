/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:35:00 by jaeshin           #+#    #+#             */
/*   Updated: 2024/03/25 16:32:10 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Server.hpp"

int main(int argc, char **argv) {
	if (argc != 3) {
		cerr << "Usage: ./ircserv <PORT> <PASSWORD>" << endl;
		return 1;
	}
	try {
		signal(SIGINT, Server::signalHandler);
		signal(SIGQUIT, Server::signalHandler);
		Server server = Server(argv[1], argv[2]);
	} catch (const exception &e) {
		cerr << e.what() << endl;
	}
	cout << "Server has been closed." << endl;
	return 0;
}
