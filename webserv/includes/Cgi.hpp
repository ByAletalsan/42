/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:58:50 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/13 18:16:31 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

#include <iostream>
#include <vector>

enum Methods { POST, GET, PUT, DELETE, HEAD, OPTIONS, TRACE, NONE };

class Cgi
{
	private:

		std::string				extension;
		std::string				exec_route;
		
	public:

		Cgi();
		Cgi( const Cgi &c );
		~Cgi();

		Cgi &operator=( const Cgi &c );

		//SETTERS

		void	set_extension(std::string extension);
		void	set_exec_route(std::string exec_route);
		//GETTERS

		std::string	get_extension();
		std::string	get_exec_route();

		void		print_info();

};

#endif
