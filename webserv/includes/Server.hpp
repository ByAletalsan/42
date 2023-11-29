/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:44:20 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/14 14:52:51 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Location.hpp"
#include "Cgi.hpp"

class Server
{
	private:
	
		std::string				server_name;
		std::string				host;
		int						listen;
		std::string				error_pages;
		std::vector<Location>	locations;

	public:	

		Server();
		Server( const Server &s );
		~Server();
		Server &operator=( const Server &s );
		
		void			set_server_name(std::string name);
		void			set_host(std::string host);
		void			set_listen(int listen);
		void			set_server_error_pages(std::string error_pages);
		void			set_server_name(std::vector<Location>	locations);

		
		std::string				get_server_name();
		std::string				get_host();
		int						get_listen();
		std::string				get_error_pages();
		std::vector<Location>	get_locations();

		void					push_location(Location &location);
		void					print_server_info();
};

#endif
