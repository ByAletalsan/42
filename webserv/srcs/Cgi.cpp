/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:07:27 by delvira-          #+#    #+#             */
/*   Updated: 2023/11/29 17:39:35 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cgi.hpp"

Cgi::Cgi()
{
    this->extension = "";
    this->exec_route = "";
}

Cgi::~Cgi()
{
    
}


Cgi::Cgi( const Cgi &c )
{
    this->extension = c.extension;
    this->exec_route = c.exec_route;
}

Cgi &Cgi::operator=( const Cgi &c )
{
    this->extension = c.extension;
    this->exec_route = c.exec_route;
    return *this;
}

// SETTERS

void	Cgi::set_extension(std::string extension)
{
    this->extension = extension;
}
void	Cgi::set_exec_route(std::string exec_route)
{
    this->exec_route = exec_route;
}
//GETTERS

std::string	Cgi::get_extension()
{
    return (this->extension);
}
std::string	Cgi::get_exec_route()
{
    return (this->exec_route);
}

void		Cgi::print_info()
{
    std::cout << "\033[36;1m" << std::endl;
    std::cout << "-------CGI----------" << std::endl;
    std::cout << "extension: " << this->get_extension() << std::endl;
    std::cout << "exec_route: " << this->get_exec_route() << std::endl;
    std::cout << "\033[0m" << std::endl;
}
