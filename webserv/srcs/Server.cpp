/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvasco-m <dvasco-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:04:31 by delvira-          #+#    #+#             */
/*   Updated: 2023/11/29 19:38:14 by dvasco-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

Server::Server()
{
    this->server_name = "";
    this->listen = -1;
    this->host = "";
    this->error_pages = "";
    
}

Server::~Server()
{
    
}

Server::Server( const Server &s )
{
    this->server_name = s.server_name;
    this->locations = s.locations;
    this->error_pages = s.error_pages;
    this->listen = s.listen;
    this->host = s.host;

}
Server & Server::operator=( const Server &s )
{
    this->server_name = s.server_name;
    this->locations = s.locations;
    this->error_pages = s.error_pages;
    this->host = s.host;
    this->listen = s.listen;
    return *this;
}



// SETTERS

void	Server::set_server_name(std::string name)
{
    this->server_name = name;
}
void	Server::set_host(std::string host)
{
    this->host = host;
}
void	Server::set_listen(int listen)
{
        this->listen = listen;

}
void	Server::set_server_error_pages(std::string error_pages)
{
        this->error_pages = error_pages;

}
void	Server::set_server_name(std::vector<Location>	locations)
{
        this->locations = locations;
}


// GETTERS

std::string		Server::get_server_name()
{
    return (this->server_name);
}
std::string     Server::get_host()
{
    return(this->host);
}
int		        Server::get_listen()
{
    return(this->listen);
}
std::string     Server::get_error_pages()
{
    return(this->error_pages);
}
std::vector<Location>	Server::get_locations()
{
    return(this->locations);
}


void	Server::push_location(Location &location)
{
    this->locations.push_back(location);
}

void			Server::print_server_info()
{
    std::cout << "\033[31;1m" << "----------NEW_SERVER-------------" << std::endl;
    std::cout << "server_name: " << this->get_server_name() << std::endl;
    std::cout << "host: " << this->get_host() << std::endl;
    std::cout << "listen: " << this->get_listen() << std::endl;
    std::cout << "error_pages : " << this->get_error_pages() << "\033[0m" << std::endl;
    for (int i = 0; i < (int)this->locations.size(); i++)
    {
        this->locations.at(i).print_location_info();
    }
}

