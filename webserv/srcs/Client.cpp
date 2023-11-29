/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 23:34:12 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/29 17:39:41 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

Client::Client() : fd(-1), request(""), ip(""), port(0)
{
}

Client::Client( const Client &c ) : fd(c.fd), request(c.request), ip(c.ip), port(c.port)
{
}

Client::Client( int fd, struct sockaddr_in clientAddrs )
{
	this->fd = fd;
	this->request = "";
	char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientAddrs.sin_addr, client_ip, sizeof(client_ip));
    this->port = ntohs(clientAddrs.sin_port);
	this->ip = std::string(client_ip);
}

const Client &Client::operator=( const Client &c )
{
	if (this != &c)
	{
		this->fd = c.getFd();
		this->request = c.getRequest();
		this->ip = c.getIp();
		this->port = c.getPort();
	}
	return *this;
}

Client::~Client()
{
}


//Setters
void	Client::setFd( int fd )
{
	this->fd = fd;
}

void	Client::setRequest( const std::string &request )
{
	this->request = request;
}

void	Client::addRequest( const std::string &add )
{
	this->request += add;
}

void	Client::setIp( const std::string &ip )
{
	this->ip = ip;
}

void	Client::setPort( int port )
{
	this->port = port;
}


//Gettes
int					Client::getFd() const
{
	return this->fd;
}

const std::string	&Client::getRequest() const
{
	return this->request;
}

const std::string	&Client::getIp() const
{
	return this->ip;
}

int					Client::getPort() const
{
	return this->port;
}
