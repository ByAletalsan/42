/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:38:39 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/11/29 19:38:11 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserv.hpp"

int	recv_data( Client &client )
{
	char	buffer[BUFFER_SIZE] = {0};
	int		ret;

	ret = recv(client.getFd(), buffer, BUFFER_SIZE - 1, 0);

	if (ret == 0 || ret == -1)
	{
		close(client.getFd());
		if (!ret)
			std::cout << WHITE << "Connection was closed by client." << DEFAULT << std::endl;
		else
			std::cout << WHITE << "Read error, closing connection." << DEFAULT << std::endl;
		return (-1);
	}

	client.addRequest(std::string(buffer));

	size_t	i = client.getRequest().find("\r\n\r\n");
	size_t	j;
	if (i != std::string::npos)
	{
		if (client.getRequest().find("Content-Length: ") == std::string::npos)
			return (0);
		if ((j = client.getRequest().find("Content-Type:")) != std::string::npos && (j = client.getRequest().find("boundary=", j)) != std::string::npos)
		{
			j += 9;
			std::string boundary = client.getRequest().substr(j, client.getRequest().find("\r\n", j) - j) + "--";
			if (client.getRequest().find(boundary) != std::string::npos)
				return (0);
			return (1);
		}
		else
		{	
			size_t	len = atoi(client.getRequest().substr(client.getRequest().find("Content-Length: ") + 16, 10).c_str());
			if (client.getRequest().size() >= len + i + 4)
				return (0);
			else
				return (1);
		}
	}

	return (1);
}
