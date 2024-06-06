/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_authn.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-kouc <mel-kouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:30:20 by mel-kouc          #+#    #+#             */
/*   Updated: 2024/05/17 23:47:54 by mel-kouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"
#include "../include/reply.hpp"


bool	Server::unique_nickname(std::string nickname)
{
	for (std::vector<Client>::iterator it  = clients.begin(); it != clients.end(); it++)
	{
		if (!it->get_nickname().compare(nickname))
			return (false);
	}
	return (true);
}

bool	Server::check_valid_nick_name(std::string nick_name)
{
	if (isdigit(nick_name[0]))
		return false;
	if (size_t test =  nick_name.find_first_of("#: ") != std::string::npos)
		return false;
	if (nick_name.find("#&") != std::string::npos)
		return false;
	if (nick_name.find("&#") != std::string::npos)
		return false;
	return true;
}

void	Server::success_connect(Client *user)
{
	// REPLY_WELCOME(nick, hostname)
	sendToClient(user->get_fd(), REPLY_WELCOME(user->get_nickname(), user->get_hostname()));
	
	//     
	std::time_t currentTime = std::time(NULL);

    // Convert to UTC time
    std::tm* utcTime = std::gmtime(&currentTime);

    // Buffer to hold the formatted date and time string
    char buffer[80];

    // Format the date and time according to the specified format
	std::strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S %Z", utcTime);
    std::string formatted_time = buffer;
	sendToClient(user->get_fd(), REPLY_YOURHOST(user->get_nickname(), user->get_hostname()));
	sendToClient(user->get_fd(), REPLY_CREATED(user->get_nickname(), user->get_hostname(), formatted_time));
}