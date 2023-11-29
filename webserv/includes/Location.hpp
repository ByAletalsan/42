/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:49:36 by atalaver          #+#    #+#             */
/*   Updated: 2023/11/16 11:44:02 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "Cgi.hpp"


class Location
{
	private:
	
		std::string				path;
		std::string				root;
		std::string				redirect;
		bool					autoindex;
		std::string				index;
		std::vector<Methods>	methods;
		unsigned int			body_size;
		std::string				mk_saved;
		std::vector<Cgi>		cgis;

	public:

		Location();
		Location( const Location &l );
		~Location();

		Location &operator=( const Location &l );


		// SETTERS

		void	set_path(std::string path);
		void	set_root(std::string root);
		void	set_redirect(std::string redir);
		void	set_autoindex(bool autoin);
		void	set_index(std::string in);
		void	set_methods(std::vector<Methods> &methods);
		void	set_body_size(unsigned int body);
		void	set_cgis(std::vector<Cgi> cgi);
		void	set_mk_saved(std::string mk_saved);

		
		//GETTERS

		std::string				&get_path();
		std::string				&get_root();
		std::string				&get_redirect();
		bool					get_autoindex();
		std::string				&get_index();
		std::vector<Methods>	&get_methods();
		unsigned int			get_body_size();
		std::vector<Cgi> 		&get_cgis();
		std::string				&get_mk_saved();

		void					push_back_method(Methods &method);
		void					push_back_cgi(Cgi &cgi);
		void					print_location_info();

};

#endif
