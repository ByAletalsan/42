/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 23:26:06 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/25 23:33:56 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class Client
{
	private:
		int	fd;
		std::string request;
		std::string ip;
		int port;
		Client();

	public:
		Client( const Client &c );
		Client( int fd, struct sockaddr_in clientAddrs );
		const Client &operator=( const Client &c );
		~Client();

		//Setters
		void	setFd( int fd );
		void	setRequest( const std::string &request );
		void	addRequest( const std::string &add );
		void	setIp( const std::string &ip );
		void	setPort( int port );

		//Gettes
		int					getFd() const;
		const std::string	&getRequest() const;
		const std::string	&getIp() const;
		int					getPort() const;
};

#endif
